#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <chrono>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QIODevice>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "dbmanager.h"
#include "editgasto.h"
#include "editconfig.h"
#include "gastomodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbcon() // Esto debería ir en un fichero de configuración
{
    ui->setupUi(this);

    // Abrir JSON
    openJson("/home/igorrecioh/gastos/gastos.json");

    // Recuperar parametros
    getParams();

    // Conexion DB
    dbcon = new DbManager(dbPath);

    // Añadir items de tipo
    populateComboTipo();

    // Obtenemos la fecha actual
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    ui->dateEdit->setDate(QDate(local_tm.tm_year + 1900, local_tm.tm_mon + 1, local_tm.tm_mday));
    ui->fromDate->setDate(QDate(local_tm.tm_year + 1900, local_tm.tm_mon + 1, local_tm.tm_mday));
    ui->toDate->setDate(QDate(local_tm.tm_year + 1900, local_tm.tm_mon + 1, local_tm.tm_mday));

    // Creamos el modelo de gastos para la tabla
    gastosModel = new GastoModel(this);

    // Populate model with data:
    gastosModel->populateData(gastoIds, gastoFechas, gastoPrecios, gastoTipos, gastoDescripciones);

    // Conectamos el modelo con las tablas (añadir y filtrar)
    ui->tableView->setModel(gastosModel);
    ui->tableViewFilter->setModel(gastosModel);

    // Mostramos los títulos de las columnas y la info
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();
    ui->tableViewFilter->horizontalHeader()->setVisible(true);
    ui->tableViewFilter->show();

    // Preparación de la parte de filtros
    ui->filterByCbx->addItem("Seleccione filtro");
    ui->filterByCbx->addItem("Por tipo");
    ui->filterByCbx->addItem("Por fecha");
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->filterByCbx->model());
    QStandardItem *item = model->item(0);
    item->setEnabled(false);
    ui->filterByCbx->show();

    // Preparacion pestaña config
    configModel = new ConfigModel(this);
    configModel->populateData(configKeys, configValues);
    ui->configTable->setModel(configModel);
    ui->configTable->horizontalHeader()->setVisible(true);
    ui->configTable->show();

    // La app comienza con datos actualizados de la DB
    on_refreshBtn_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openJson(QString path)
{
    // Apertura y lectura JSON
    QFile file(path);
    QByteArray bytes;
    if(file.open(QIODevice::ReadOnly)){
        bytes = file.readAll();
        file.close();
    }
    this->jsonBytes = bytes;
}

void MainWindow::getParams()
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson( this->jsonBytes, &jsonError );
    if( jsonError.error != QJsonParseError::NoError )
    {
        std::cout << "fromJson failed: " << jsonError.errorString().toStdString() << std::endl;
        return ;
    }
    QJsonObject jsonObj = document.object();

    // Ejemplo para clave valor sencillo
    dbPath = jsonObj.value("DB_PATH").toString();
    configKeys.append("DB_PATH");
    configValues.append(dbPath);
    qDebug() << dbPath;

    // Ejemplo para clave valor con Array
    QJsonArray jsonArr = jsonObj.value("TYPES").toArray();
    int typeIdx = 0;
    for (QJsonValue item : jsonArr)
    {
        tiposJson.append(item.toString());
        configKeys.append("TYPE_" + QString::number(typeIdx));
        configValues.append(item.toString());
        qDebug() << item.toString();
        typeIdx++;
    }
}

void MainWindow::populateComboTipo()
{
    for(QString item : tiposJson)
    {
        ui->comboBox->addItem(item);
        ui->tipoCbx->addItem(item);
    }
}

void MainWindow::on_saveBtn_clicked()
{
    std::cout << "Save button pressed" << std::endl;
    std::cout << "Date: " << ui->dateEdit->date().toString("dd/MM/yyyy").toStdString() << std::endl;
    std::cout << "Price: " << ui->doubleSpinBox->value() << std::endl;
    std::cout << "Type: " << ui->comboBox->currentText().toStdString() << std::endl;
    std::cout << "Description: " << ui->lineEdit->text().toStdString() << std::endl;

    dbcon->addGasto(ui->dateEdit->date().toString("yyyy-MM-dd"),
                  ui->comboBox->currentText(),
                  ui->doubleSpinBox->value(),
                  ui->lineEdit->text());

    // Borrado tras guardado
    ui->doubleSpinBox->setValue(0.00);
    ui->lineEdit->setText("");

    on_refreshBtn_clicked();
}


void MainWindow::on_exitBtn_clicked()
{
    this->close();
}

void MainWindow::on_deleteBtn_clicked()
{
    dbcon->deleteAll();
    gastoIds.clear();
    gastoFechas.clear();
    gastoPrecios.clear();
    gastoTipos.clear();
    gastoDescripciones.clear();

    gastosModel->populateData(gastoIds, gastoFechas,gastoPrecios, gastoTipos, gastoDescripciones);

    ui->tableView->setModel(gastosModel);
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();
}


void MainWindow::on_refreshBtn_clicked()
{
    dbcon->GetAllDataFromTable();

    gastosModel = new GastoModel(this);
    gastosModel->populateData(dbcon->gastoIds, dbcon->gastoFechas, dbcon->gastoPrecios, dbcon->gastoTipos, dbcon->gastoDescripciones);

    ui->tableView->setModel(gastosModel);
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();
}


void MainWindow::on_deleteCurrentBtn_clicked()
{

    gastosModel->populateData(dbcon->gastoIds, dbcon->gastoFechas, dbcon->gastoPrecios, dbcon->gastoTipos, dbcon->gastoDescripciones);

    int index = ui->tableView->selectionModel()->currentIndex().row();

    if(index < 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Seleccione un gasto");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QString("Desea borrar el gasto con ID: %1 ?").arg(gastosModel->index(index, 0).data().toInt()));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        switch(ret) {
            case QMessageBox::Yes:
                dbcon->deleteGastoById(gastosModel->index(index, 0).data().toInt());
                QMessageBox confirmacionPopup;
                confirmacionPopup.setText("Gasto borrado!");
                confirmacionPopup.exec();
                on_refreshBtn_clicked();
                break;
        }
    }
}


void MainWindow::on_buscarBtn_clicked()
{
    if(ui->filterByCbx->currentIndex() == 1){
        dbcon->getDataByTipo(ui->tipoCbx->currentText());
    }
    else if(ui->filterByCbx->currentIndex() == 2) {
        dbcon->getDataBetweenDates(ui->fromDate->date().toString("yyyy-MM-dd"), ui->toDate->date().toString("yyyy-MM-dd"));
    }

    GastoModel *gastosFilterModel = new GastoModel(this);

    gastosFilterModel->populateData(dbcon->gastoIds, dbcon->gastoFechas, dbcon->gastoPrecios, dbcon->gastoTipos, dbcon->gastoDescripciones);

    ui->tableViewFilter->setModel(gastosFilterModel);
    ui->tableViewFilter->horizontalHeader()->setVisible(true);
    ui->tableViewFilter->show();
}


void MainWindow::on_filterByCbx_currentIndexChanged(int index)
{
    if(index == 1){
        ui->tipoCbx->setEnabled(true);
        ui->fromDate->setEnabled(false);
        ui->toDate->setEnabled(false);
    }
    else if(index == 2) {
        ui->fromDate->setEnabled(true);
        ui->toDate->setEnabled(true);
        ui->tipoCbx->setEnabled(false);
    }
}

void MainWindow::on_editBtn_clicked()
{
    int index = ui->tableView->selectionModel()->currentIndex().row();

    if(index < 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Seleccione un gasto para modificar");
        msgBox.exec();
    }
    else
    {
        EditGasto *editGasto = new EditGasto(this, dbcon);
        editGasto->populateComboTipo(this->tiposJson);
        editGasto->setValuesInPopup(gastosModel->index(index, 0).data().toString(),
                                    gastosModel->index(index, 1).data().toDate(),
                                    gastosModel->index(index, 3).data().toString(),
                                    gastosModel->index(index, 2).data().toFloat(),
                                    gastosModel->index(index, 4).data().toString());

        // SOURCE: How to trigger a method after closing a dialog box
        if(editGasto->exec() == 0){
            on_refreshBtn_clicked();
        }
    }
}

void MainWindow::on_editConfigBtn_clicked()
{
    int index = ui->configTable->selectionModel()->currentIndex().row();

    if(index < 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Seleccione una configuración para modificar");
        msgBox.exec();
    }
    else
    {
        EditConfig *editConfig = new EditConfig(this);
        editConfig->SetKeyValue(configModel->index(index, 0).data().toString(), configModel->index(index, 1).data().toString());
        if(editConfig->exec() == 0){
        }
    }
}


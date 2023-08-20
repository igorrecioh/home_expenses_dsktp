#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <chrono>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QIODevice>
#include <QFile>
#include <QWidget>
#include "dbmanager.h"
#include "addconfig.h"
#include "editgasto.h"
#include "editconfig.h"
#include "gastomodel.h"
#include "setdbpath.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dbcon()
    , settings("GastosApp", "gastosApp")
{
    ui->setupUi(this);

    // Recuperar parametros
    getParams();

    // Añadir items de tipo
    populateComboTipo();

    // Conexion DB
    dbcon = new DbManager(dbPath);

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
    gastosModel->populateData(gastoIds, gastoFechas, gastoPrecios, gastoTipos, gastoDescripciones, gastoPersonas);

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
    populateConfigTable();

    // La app comienza con datos actualizados de la DB
    on_refreshBtn_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getParams()
{
    dbPath = settings.value("DB_PATH").toString();
    if (dbPath == "")
    {
        qDebug() << "Path to DB not found...";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error en base de datos");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ruta a DB no encontrada!!!");
        msgBox.exec();

        auto child = ui->tabWidget->findChild<QWidget *>(QString("config"), Qt::FindChildrenRecursively);
        ui->tabWidget->setCurrentWidget(child);
    }

    dbPath = settings.value("DB_PATH").toString();
    ui->dbPathLine->setText(dbPath);
    qDebug() << dbPath;

    QList<QString> data2 = settings.value("TYPES").value<QList<QString>>();
    for (QString type : data2) {
        configTypes.append(type);
        qDebug() << type;
    };
}

void MainWindow::receiveDbPath(const QString &newValue)
{
    qDebug() << "Guardando path";
    settings.setValue("DB_PATH", QVariant::fromValue(newValue));
    ui->dbPathLine->setText(newValue);
}

void MainWindow::receiveNewType(const QString &newType)
{
    qDebug() << "Guardando tipo nuevo";
    QList<QString> data2 = settings.value("TYPES").value<QList<QString>>();
    data2.append(newType);

    configTypes.clear();
    for (QString type : data2) {
        configTypes.append(type);
        qDebug() << type;
    };

    settings.setValue("TYPES", QVariant::fromValue(configTypes));

    // Refrescamos los combos
    populateComboTipo();
    populateConfigTable();
}

void MainWindow::populateComboTipo()
{
    ui->comboBox->clear();
    ui->tipoCbx->clear();
    ui->comboBox->addItems(configTypes);
    ui->tipoCbx->addItems(configTypes);
    ui->comboBox->setCurrentIndex(0);
    ui->tipoCbx->setCurrentIndex(0);
    ui->comboBox->show();
    ui->tipoCbx->show();
}

void MainWindow::populateConfigTable()
{
    configModel = new ConfigModel(this);
    configModel->populateData(configTypes);
    ui->configTable->setModel(configModel);
    ui->configTable->horizontalHeader()->setVisible(true);
    ui->configTable->show();
}

void MainWindow::on_saveBtn_clicked()
{
    if(ui->lineEdit_nombre->text().toStdString().length() == 0)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Introduzca la persona asociada al gasto");
        msgBox.exec();
    }
    else if(ui->doubleSpinBox->value() == 0 )
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Introduzca el coste asociado al gasto");
        msgBox.exec();
    }
    else
    {
        std::cout << "Save button pressed" << std::endl;
        std::cout << "Date: " << ui->dateEdit->date().toString("dd/MM/yyyy").toStdString() << std::endl;
        std::cout << "Price: " << ui->doubleSpinBox->value() << std::endl;
        std::cout << "Type: " << ui->comboBox->currentText().toStdString() << std::endl;
        std::cout << "Description: " << ui->lineEdit->text().toStdString() << std::endl;
        std::cout << "Name: " << ui->lineEdit_nombre->text().toStdString() << std::endl;

        dbcon->addGasto(ui->dateEdit->date().toString("yyyy-MM-dd"),
                      ui->comboBox->currentText(),
                      ui->doubleSpinBox->value(),
                      ui->lineEdit->text(),
                      ui->lineEdit_nombre->text());

        // Borrado tras guardado
        ui->doubleSpinBox->setValue(0.00);
        ui->lineEdit->setText("");
        ui->lineEdit_nombre->setText("");

        on_refreshBtn_clicked();
    }
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
    gastoPersonas.clear();

    gastosModel->populateData(gastoIds, gastoFechas,gastoPrecios, gastoTipos, gastoDescripciones, gastoPersonas);

    ui->tableView->setModel(gastosModel);
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();
}


void MainWindow::on_refreshBtn_clicked()
{
    dbcon->GetAllDataFromTable();

    gastosModel = new GastoModel(this);
    gastosModel->populateData(dbcon->gastoIds, dbcon->gastoFechas, dbcon->gastoPrecios, dbcon->gastoTipos, dbcon->gastoDescripciones, dbcon->gastoPersonas);

    ui->tableView->setModel(gastosModel);
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();
}


void MainWindow::on_deleteCurrentBtn_clicked()
{

    gastosModel->populateData(dbcon->gastoIds, dbcon->gastoFechas, dbcon->gastoPrecios, dbcon->gastoTipos, dbcon->gastoDescripciones, dbcon->gastoPersonas);

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

    gastosFilterModel->populateData(dbcon->gastoIds, dbcon->gastoFechas, dbcon->gastoPrecios, dbcon->gastoTipos, dbcon->gastoDescripciones, dbcon->gastoPersonas);

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
        editGasto->populateComboTipo(this->configTypes);
        editGasto->setValuesInPopup(gastosModel->index(index, 0).data().toString(),
                                    gastosModel->index(index, 1).data().toDate(),
                                    gastosModel->index(index, 3).data().toString(),
                                    gastosModel->index(index, 2).data().toFloat(),
                                    gastosModel->index(index, 4).data().toString(),
                                    gastosModel->index(index, 5).data().toString());

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
        editConfig->SetValue(configModel->index(index, 0).data().toString());
        if(editConfig->exec() == 0){
        }
    }
}

void MainWindow::receiveEditedConfig(const QString &oldValue, const QString &newValue)
{
    // Se recibe el valor antiguo y el nuevo
    QList<QString> data2 = settings.value("TYPES").value<QList<QString>>();

    // Se busca en la lista el valor antiguo para sustituirlo en ella y en los settings
    int updateIndex = data2.indexOf(oldValue);
    data2[updateIndex] = newValue;
    settings.setValue("TYPES", QVariant::fromValue(data2));

    // Limpiamos y rellenamos la lista de tipos con los nuevos valores
    data2 = settings.value("TYPES").value<QList<QString>>();
    configTypes.clear();
    for (QString type : data2) {
        configTypes.append(type);
        qDebug() << type;
    };

    // Refrescamos los combos
    populateComboTipo();
    populateConfigTable();
}


void MainWindow::on_deleteCurrentConfigBtn_clicked()
{
    int index = ui->configTable->selectionModel()->currentIndex().row();

    if(index < 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Seleccione una configuración para eliminar");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(QString("Desea borrar el tipo de gasto %1 ?").arg(configModel->index(index, 0).data().toString()));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();

        switch(ret) {
            case QMessageBox::Yes:
                QList<QString> data2 = settings.value("TYPES").value<QList<QString>>();
                int eraseIndex = data2.indexOf(configModel->index(index, 0).data().toString());
                data2.removeAt(eraseIndex);
                settings.setValue("TYPES", QVariant::fromValue(data2));

                QMessageBox confirmacionPopup;
                confirmacionPopup.setText("Tipo borrado!");
                confirmacionPopup.exec();
                configTypes.clear();

                data2 = settings.value("TYPES").value<QList<QString>>();
                for (QString type : data2) {
                    configTypes.append(type);
                    qDebug() << type;
                };

                populateComboTipo();
                populateConfigTable();

                break;
        }
    }
}


void MainWindow::on_saveTypeBtn_clicked()
{
    AddConfig *addConfig = new AddConfig(this);
    if(addConfig->exec() == 0){

        configTypes.clear();
        QList<QString> data2 = settings.value("TYPES").value<QList<QString>>();
        for (QString type : data2) {
            configTypes.append(type);
            qDebug() << type;
        };

        populateComboTipo();
        populateConfigTable();
    }
}


void MainWindow::on_setDbPath_clicked()
{
    SetDbPath *setDbPath = new SetDbPath(this);
    if(setDbPath->exec() == 0){
    }
}


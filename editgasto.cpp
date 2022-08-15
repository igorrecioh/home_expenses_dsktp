#include "editgasto.h"
#include "mainwindow.h"
#include "ui_editgasto.h"

EditGasto::EditGasto(QWidget *parent, DbManager *dbcon) :
    QDialog(parent),
    ui(new Ui::EditGasto),
    m_dbcon(*dbcon)
{
    ui->setupUi(this);
}

EditGasto::~EditGasto()
{
    delete ui;
}

void EditGasto::setValuesInPopup(const QString& id, const QDate& fecha, const QString& tipo, float coste, const QString& desc)
{
    m_id = id;
    ui->dateEdit->setDate(fecha);
    ui->doubleSpinBox->setValue(coste);
    int index = ui->comboBox->findText(tipo);
    ui->comboBox->setCurrentIndex(index);
    ui->lineEdit->setText(desc);
}

void EditGasto::on_updateGastoBtn_clicked()
{
    ui->dateEdit->date().toString("yyyy-MM-dd");
    ui->comboBox->currentText();
    ui->doubleSpinBox->value();
    ui->lineEdit->text();
    m_dbcon.updateDataById(m_id, ui->dateEdit->date().toString("yyyy-MM-dd"), ui->comboBox->currentText(), ui->doubleSpinBox->value(), ui->lineEdit->text());
    this->close();
    this->setResult(0);
}

void EditGasto::on_cancelEditBtn_clicked()
{
    this->close();
    this->setResult(1);
}

void EditGasto::populateComboTipo(QList<QString> tiposJson)
{
    for(QString item : tiposJson)
    {
        ui->comboBox->addItem(item);
    }
}

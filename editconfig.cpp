#include "editconfig.h"
#include "mainwindow.h"
#include "ui_editconfig.h"

EditConfig::EditConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditConfig)
{
    ui->setupUi(this);
}

EditConfig::~EditConfig()
{
    delete ui;
}

void EditConfig::SetKeyValue(QString key, QString value)
{
    ui->keyLabel->setText(key);
    ui->valueEdit->setText(value);
}

void EditConfig::on_cancelConfigEditBtn_clicked()
{
    this->close();
    this->setResult(1);
}


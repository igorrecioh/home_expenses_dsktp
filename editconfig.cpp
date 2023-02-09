#include "editconfig.h"
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

void EditConfig::SetValue(QString value)
{
    ui->valueEdit->setText(value);
}

void EditConfig::on_cancelConfigEditBtn_clicked()
{
    this->close();
    this->setResult(1);
}


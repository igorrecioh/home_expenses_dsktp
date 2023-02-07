#include "addconfig.h"
#include "ui_addconfig.h"

AddConfig::AddConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddConfig)
{
    ui->setupUi(this);
}

AddConfig::~AddConfig()
{
    delete ui;
}

void AddConfig::on_cancelConfigAddBtn_clicked()
{
    this->close();
    this->setResult(1);
}


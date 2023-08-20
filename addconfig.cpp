#include "addconfig.h"
#include "ui_addconfig.h"

AddConfig::AddConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddConfig),
    _settings("IgorRecio", "gastosApp")
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendNewType(QString)), parent, SLOT(receiveNewType(QString)));
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


void AddConfig::on_updateConfigBtn_clicked()
{
    emit sendNewType(ui->valueEdit->text());
    this->close();
    this->setResult(0);
}


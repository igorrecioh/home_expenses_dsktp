#include "addconfig.h"
#include "ui_addconfig.h"

AddConfig::AddConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddConfig),
    _settings("IgorRecio", "gastosApp")
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


void AddConfig::on_updateConfigBtn_clicked()
{
    QList<QString> data2 = _settings.value("TYPES").value<QList<QString>>();
    data2.append(ui->valueEdit->text());
    _settings.setValue("TYPES", QVariant::fromValue(data2));
    this->close();
    this->setResult(0);
}


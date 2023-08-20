#include "editconfig.h"
#include "ui_editconfig.h"

EditConfig::EditConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditConfig)
{
    ui->setupUi(this);

    // connect(ui->updateConfigBtn, SIGNAL(clicked(bool)), this, SLOT(on_updateConfigBtn_clicked()));
    connect(this, SIGNAL(sendEditedConfig(QString, QString)), parent, SLOT(receiveEditedConfig(QString, QString)));
}

EditConfig::~EditConfig()
{
    delete ui;
}

void EditConfig::SetValue(QString value)
{
    _oldConfig = value;
    ui->valueEdit->setText(value);
}

void EditConfig::on_cancelConfigEditBtn_clicked()
{
    this->close();
    this->setResult(1);
}


void EditConfig::on_updateConfigBtn_clicked()
{
    emit sendEditedConfig(_oldConfig, ui->valueEdit->text());
    this->close();
    this->setResult(0);
}


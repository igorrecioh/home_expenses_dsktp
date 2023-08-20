#include "setdbpath.h"
#include "ui_setdbpath.h"

SetDbPath::SetDbPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDbPath)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendDbPath(QString)), parent, SLOT(receiveDbPath(QString)));
}

SetDbPath::~SetDbPath()
{
    delete ui;
}

void SetDbPath::on_exitDbApp_clicked()
{
    this->close();
    this->setResult(1);
}


void SetDbPath::on_saveDbPathBtn_clicked()
{
    emit sendDbPath(ui->dbPathEdit->text());
    this->close();
    this->setResult(0);
}


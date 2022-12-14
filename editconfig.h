#ifndef EDITCONFIG_H
#define EDITCONFIG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class EditConfig;
}

class EditConfig : public QDialog
{
    Q_OBJECT

public:
    explicit EditConfig(QWidget *parent = nullptr);
    void SetKeyValue(QString key, QString value);
    ~EditConfig();

private slots:
    void on_cancelConfigEditBtn_clicked();

private:
    Ui::EditConfig *ui;
};

#endif // EDITCONFIG_H

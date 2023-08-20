#ifndef ADDCONFIG_H
#define ADDCONFIG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class AddConfig;
}

class AddConfig : public QDialog
{
    Q_OBJECT

public:
    AddConfig(QWidget *parent = nullptr);
    ~AddConfig();

private slots:
    void on_cancelConfigAddBtn_clicked();

    void on_updateConfigBtn_clicked();

signals:
    void sendNewType(const QString &newValue);

private:
    Ui::AddConfig *ui;
    QSettings _settings;
};

#endif // ADDCONFIG_H

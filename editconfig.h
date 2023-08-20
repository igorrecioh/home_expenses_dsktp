#ifndef EDITCONFIG_H
#define EDITCONFIG_H

#include <QDialog>

namespace Ui {
class EditConfig;
}

class EditConfig : public QDialog
{
    Q_OBJECT

public:
    explicit EditConfig(QWidget *parent = nullptr);
    void SetValue(QString value);
    ~EditConfig();

private slots:
    void on_cancelConfigEditBtn_clicked();

    void on_updateConfigBtn_clicked();

signals:
    void sendEditedConfig(const QString &oldValue, const QString &newValue);

private:
    Ui::EditConfig *ui;
    QString _oldConfig;
};

#endif // EDITCONFIG_H

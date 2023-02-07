#ifndef ADDCONFIG_H
#define ADDCONFIG_H

#include <QDialog>

namespace Ui {
class AddConfig;
}

class AddConfig : public QDialog
{
    Q_OBJECT

public:
    explicit AddConfig(QWidget *parent = nullptr);
    ~AddConfig();

private slots:
    void on_cancelConfigAddBtn_clicked();

private:
    Ui::AddConfig *ui;
};

#endif // ADDCONFIG_H

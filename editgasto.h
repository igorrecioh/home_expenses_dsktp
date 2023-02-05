#ifndef EDITGASTO_H
#define EDITGASTO_H

#include <QDialog>
#include "dbmanager.h"
#include "mainwindow.h"

namespace Ui {
class EditGasto;
}

class EditGasto : public QDialog
{
    Q_OBJECT

public:
    explicit EditGasto(QWidget *parent = nullptr, DbManager *dbcon = nullptr);
    void setValuesInPopup(const QString& id, const QDate& fecha, const QString& tipo, float coste, const QString& desc, const QString& nombre);
    void populateComboTipo(QList<QString> tiposJson);
    ~EditGasto();

private slots:
    void on_updateGastoBtn_clicked();

    void on_cancelEditBtn_clicked();

private:
    Ui::EditGasto *ui;
    DbManager m_dbcon;
    QString m_id;
};

#endif // EDITGASTO_H

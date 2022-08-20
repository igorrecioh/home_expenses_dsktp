#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gastomodel.h"
#include "configmodel.h"
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_saveBtn_clicked();

    void on_exitBtn_clicked();

    void on_deleteBtn_clicked();


    void on_deleteCurrentBtn_clicked();

    void on_buscarBtn_clicked();

    void on_filterByCbx_currentIndexChanged(int index);

    void on_editBtn_clicked();

    void on_editConfigBtn_clicked();

public slots:
    void on_refreshBtn_clicked();

private:
    Ui::MainWindow *ui;
    QList<int> gastoIds;
    QList<QString> gastoFechas;
    QList<float> gastoPrecios;
    QList<QString> gastoTipos;
    QList<QString> gastoDescripciones;
    QList<QString> configKeys;
    QList<QString> configValues;
    DbManager *dbcon;
    GastoModel *gastosModel;
    ConfigModel *configModel;
    QByteArray jsonBytes;
    QList<QString> tiposJson;
    QString dbPath;

    void openJson(QString path);
    void getParams();
    void populateComboTipo();
};
#endif // MAINWINDOW_H

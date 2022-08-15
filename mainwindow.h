#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GastoModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    GastoModel(QObject *parent = 0);

    void populateData(const QList<int> &id, const QList<QString> &fecha,const QList<float> &precio, const QList<QString> &tipo, const QList<QString> &desc);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    QList<int> ids;
    QList<QString> fechas;
    QList<float> precios;
    QList<QString> tipos;
    QList<QString> descripciones;
};

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

public slots:
    void on_refreshBtn_clicked();

private:
    Ui::MainWindow *ui;
    QList<int> gastoIds;
    QList<QString> gastoFechas;
    QList<float> gastoPrecios;
    QList<QString> gastoTipos;
    QList<QString> gastoDescripciones;
    DbManager *dbcon;
    GastoModel *gastosModel;
    QByteArray jsonBytes;
    QList<QString> tiposJson;
    QString dbPath;

    void openJson(QString path);
    void getParams();
    void populateComboTipo();
};
#endif // MAINWINDOW_H

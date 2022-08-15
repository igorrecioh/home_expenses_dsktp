#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DbManager
{
public:
    DbManager(const QString& path);
    bool addGasto(const QString& fecha, const QString& tipo, float coste, const QString& desc);
    bool deleteAll();
    bool GetAllDataFromTable();
    bool deleteGastoById(int id);
    bool getDataByTipo(const QString& tipo);
    bool getDataBetweenDates(const QString& fromFecha, const QString& toFecha);
    bool updateDataById(QString& id, const QString& fecha, const QString& tipo, float coste, const QString& desc);

    QList<int> gastoIds;
    QList<QString> gastoFechas;
    QList<float> gastoPrecios;
    QList<QString> gastoTipos;
    QList<QString> gastoDescripciones;

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

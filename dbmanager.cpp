#include "dbmanager.h"
#include <QDebug>
#include <QSqlRecord>


DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()){
        qDebug() << "Error: Conexión con DB fallida";
    }
    else {
        qDebug() << "DB conectada!";
    }
}

bool DbManager::addGasto(const QString& fecha, const QString& tipo, float coste, const QString& desc)
{
   bool success = false;
   QSqlQuery query;
   query.prepare("INSERT INTO gastosTable (fecha, tipo, coste, descripcion) VALUES (:fecha, :tipo, :coste, :descripcion)");
   query.bindValue(":fecha", fecha);
   query.bindValue(":tipo", tipo);
   query.bindValue(":coste", coste);
   query.bindValue(":descripcion", desc);
   if(query.exec())
   {
       success = true;
   }
   else
   {
        qDebug() << "addGasto error:"
                 << query.lastError();
   }

   return success;
}

bool DbManager::deleteAll()
{
    bool success = false;
    QSqlQuery query;
    query.prepare("DELETE FROM gastosTable");
    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "deleteAll error:"
                  << query.lastError();
    }

    return success;
}

bool DbManager::GetAllDataFromTable()
{
    bool success = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM gastosTable");
    if(query.exec())
    {
        gastoIds.clear();
        gastoFechas.clear();
        gastoTipos.clear();
        gastoPrecios.clear();
        gastoDescripciones.clear();
        int id = query.record().indexOf("id");
        int fecha = query.record().indexOf("fecha");
        int tipo = query.record().indexOf("tipo");
        int coste = query.record().indexOf("coste");
        int descripcion = query.record().indexOf("descripcion");
        while(query.next())
        {
            gastoIds.append(query.value(id).toInt());
            gastoFechas.append(query.value(fecha).toString());
            gastoTipos.append(query.value(tipo).toString());
            gastoPrecios.append(query.value(coste).toFloat());
            gastoDescripciones.append(query.value(descripcion).toString());
        }
        success = true;
    }
    else
    {
         qDebug() << "GetAllDataFromTable error:"
                  << query.lastError();
    }

    return success;
}

bool DbManager::getDataByTipo(const QString& tipo)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM gastosTable WHERE tipo = :tipo");
    query.bindValue(":tipo", tipo);
    if(query.exec())
    {
        gastoIds.clear();
        gastoFechas.clear();
        gastoTipos.clear();
        gastoPrecios.clear();
        gastoDescripciones.clear();
        int id = query.record().indexOf("id");
        int fecha = query.record().indexOf("fecha");
        int tipo = query.record().indexOf("tipo");
        int coste = query.record().indexOf("coste");
        int descripcion = query.record().indexOf("descripcion");
        while(query.next())
        {
            gastoIds.append(query.value(id).toInt());
            gastoFechas.append(query.value(fecha).toString());
            gastoTipos.append(query.value(tipo).toString());
            gastoPrecios.append(query.value(coste).toFloat());
            gastoDescripciones.append(query.value(descripcion).toString());
        }
    }
    else
    {
         qDebug() << "getDataByTipo error:"
                  << query.lastError();
    }
    return success;
}

bool DbManager::getDataBetweenDates(const QString& fromFecha, const QString& toFecha)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM gastosTable WHERE fecha >= :fromFecha AND fecha <= :toFecha");
    query.bindValue(":fromFecha", fromFecha);
    query.bindValue(":toFecha", toFecha);
    if(query.exec())
    {
        gastoIds.clear();
        gastoFechas.clear();
        gastoTipos.clear();
        gastoPrecios.clear();
        gastoDescripciones.clear();
        int id = query.record().indexOf("id");
        int fecha = query.record().indexOf("fecha");
        int tipo = query.record().indexOf("tipo");
        int coste = query.record().indexOf("coste");
        int descripcion = query.record().indexOf("descripcion");
        while(query.next())
        {
            gastoIds.append(query.value(id).toInt());
            gastoFechas.append(query.value(fecha).toString());
            gastoTipos.append(query.value(tipo).toString());
            gastoPrecios.append(query.value(coste).toFloat());
            gastoDescripciones.append(query.value(descripcion).toString());
        }
    }
    else
    {
         qDebug() << "getDataBetweenDates error:"
                  << query.lastError();
    }
    return success;
}
bool DbManager::deleteGastoById(int id)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("DELETE FROM gastosTable WHERE id = :id");
    query.bindValue(":id", id);
    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "deleteGastoById error:"
                  << query.lastError();
    }

    return success;
}

bool DbManager::updateDataById(QString& id, const QString& fecha, const QString& tipo, float coste, const QString& desc)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE gastosTable SET fecha = :fecha, tipo = :tipo, coste = :coste, descripcion = :desc WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":fecha", fecha);
    query.bindValue(":tipo", tipo);
    query.bindValue(":coste", coste);
    query.bindValue(":desc", desc);

    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "updateDataById error:"
                  << query.lastError() << "\n"
                  << fecha << "\n"
                  << tipo << "\n"
                  << coste << "\n"
                  << desc << "\n"
                  << id;
    }

    return success;
}

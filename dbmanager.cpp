#include "dbmanager.h"
#include <QDebug>
#include <QSqlRecord>


DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open() || path == ""){
        qDebug() << "Error: Conexión con DB fallida";
    }
    else {
        qDebug() << "DB conectada!";
    }
}

bool DbManager::addGasto(const QString& fecha, const QString& tipo, float coste, const QString& desc, const QString& persona)
{
   bool success = false;
   QSqlQuery query;
   query.prepare("INSERT INTO gastosTable (fecha, tipo, coste, descripcion, persona) VALUES (:fecha, :tipo, :coste, :descripcion, :persona)");
   query.bindValue(":fecha", fecha);
   query.bindValue(":tipo", tipo);
   query.bindValue(":coste", coste);
   query.bindValue(":descripcion", desc);
   query.bindValue(":persona", persona);
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
        gastoPersonas.clear();
        int id = query.record().indexOf("id");
        int fecha = query.record().indexOf("fecha");
        int tipo = query.record().indexOf("tipo");
        int coste = query.record().indexOf("coste");
        int descripcion = query.record().indexOf("descripcion");
        int persona = query.record().indexOf("persona");
        while(query.next())
        {
            gastoIds.append(query.value(id).toInt());
            gastoFechas.append(query.value(fecha).toString());
            gastoTipos.append(query.value(tipo).toString());
            gastoPrecios.append(query.value(coste).toFloat());
            gastoDescripciones.append(query.value(descripcion).toString());
            gastoPersonas.append(query.value(persona).toString());
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
        int persona = query.record().indexOf("persona");
        while(query.next())
        {
            gastoIds.append(query.value(id).toInt());
            gastoFechas.append(query.value(fecha).toString());
            gastoTipos.append(query.value(tipo).toString());
            gastoPrecios.append(query.value(coste).toFloat());
            gastoDescripciones.append(query.value(descripcion).toString());
            gastoPersonas.append(query.value(persona).toString());
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
        int persona = query.record().indexOf("persona");
        while(query.next())
        {
            gastoIds.append(query.value(id).toInt());
            gastoFechas.append(query.value(fecha).toString());
            gastoTipos.append(query.value(tipo).toString());
            gastoPrecios.append(query.value(coste).toFloat());
            gastoDescripciones.append(query.value(descripcion).toString());
            gastoPersonas.append(query.value(persona).toString());
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

bool DbManager::updateDataById(QString& id, const QString& fecha, const QString& tipo, float coste, const QString& desc, const QString& persona)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE gastosTable SET fecha = :fecha, tipo = :tipo, coste = :coste, descripcion = :desc, persona = :persona WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":fecha", fecha);
    query.bindValue(":tipo", tipo);
    query.bindValue(":coste", coste);
    query.bindValue(":desc", desc);
    query.bindValue(":persona", persona);

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
                  << id << "\n"
                  << persona;
    }

    return success;
}

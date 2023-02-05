#include "gastomodel.h"


// Modelo de gastos para la tabla
GastoModel::GastoModel(QObject *parent) : QAbstractTableModel(parent)
{
}

// Método para rellenar la tabla
void GastoModel::populateData(const QList<int> &id, const QList<QString> &fecha, const QList<float> &precio, const QList<QString> &tipo, const QList<QString> &desc, const QList<QString> &persona)
{
    ids.clear();
    fechas.clear();
    precios.clear();
    tipos.clear();
    descripciones.clear();
    personas.clear();
    ids = id;
    fechas = fecha;
    precios = precio;
    tipos = tipo;
    descripciones = desc;
    personas = persona;
    return;
}

int GastoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return fechas.length();
}

int GastoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}

QVariant GastoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return ids[index.row()];
    } else if (index.column() == 1) {
        return fechas[index.row()];
    } else if (index.column() == 2) {
        return precios[index.row()];
    } else if (index.column() == 3) {
        return tipos[index.row()];
    } else if (index.column() == 4) {
        return descripciones[index.row()];
    } else if (index.column() == 5) {
        return personas[index.row()];
    }
    return QVariant();
}

QVariant GastoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("ID");
        } else if (section == 1) {
            return QString("Fecha");
        } else if (section == 2) {
            return QString("Precio");
        } else if (section == 3) {
            return QString("Tipo");
        } else if (section == 4) {
            return QString("Descripción");
        } else if (section == 5) {
            return QString("Persona");
        }
    }
    return QVariant();
}


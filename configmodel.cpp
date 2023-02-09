#include "configmodel.h"

// Modelo para las configuraciones
ConfigModel::ConfigModel(QObject *parent) : QAbstractTableModel(parent)
{

}

// Método para rellenar la tabla
void ConfigModel::populateData(const QList<QString> &configType)
{
    configTypes.clear();
    configTypes = configType;
    return;
}

int ConfigModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return configTypes.length();
}

int ConfigModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant ConfigModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return configTypes[index.row()];
    }
    return QVariant();
}

QVariant ConfigModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Tipo de gasto");
        }
    }
    return QVariant();
}



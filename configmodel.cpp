#include "configmodel.h"

// Modelo para las configuraciones
ConfigModel::ConfigModel(QObject *parent) : QAbstractTableModel(parent)
{

}

// Método para rellenar la tabla
void ConfigModel::populateData(const QList<QString> &configKey, const QList<QString> &configValue)
{
    configKeys.clear();
    configValues.clear();
    configKeys = configKey;
    configValues = configValue;
    return;
}

int ConfigModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return configKeys.length();
}

int ConfigModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant ConfigModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return configKeys[index.row()];
    } else if (index.column() == 1) {
        return configValues[index.row()];
    }
    return QVariant();
}

QVariant ConfigModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Clave");
        } else if (section == 1) {
            return QString("Valor");
        }
    }
    return QVariant();
}



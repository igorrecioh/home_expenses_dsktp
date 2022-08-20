#ifndef CONFIGMODEL_H
#define CONFIGMODEL_H
#include <QAbstractTableModel>

class ConfigModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ConfigModel(QObject *parent = 0);

    void populateData(const QList<QString> &configKey, const QList<QString> &configValue);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    QList<QString> configKeys;
    QList<QString> configValues;
};

#endif // CONFIGMODEL_H

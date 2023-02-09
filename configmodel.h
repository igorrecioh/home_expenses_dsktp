#ifndef CONFIGMODEL_H
#define CONFIGMODEL_H
#include <QAbstractTableModel>

class ConfigModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ConfigModel(QObject *parent = 0);

    void populateData(const QList<QString> &configType);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    QList<QString> configTypes;
};

#endif // CONFIGMODEL_H

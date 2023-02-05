#ifndef GASTOMODEL_H
#define GASTOMODEL_H
#include <QAbstractTableModel>

class GastoModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    GastoModel(QObject *parent = 0);

    void populateData(const QList<int> &id, const QList<QString> &fecha,const QList<float> &precio, const QList<QString> &tipo, const QList<QString> &desc, const QList<QString> &persona);

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
    QList<QString> personas;
};

#endif // GASTOMODEL_H

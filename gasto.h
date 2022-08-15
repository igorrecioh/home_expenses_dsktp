#ifndef GASTO_H
#define GASTO_H

#include <QString>

class Gasto
{
public:
    Gasto(QString& fecha, QString& tipo, float coste, QString& descripcion);

private:
    QString& m_fecha;
    QString& m_tipo;
    float m_coste;
    QString& m_descripcion;
};

#endif // GASTO_H

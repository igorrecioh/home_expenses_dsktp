#include "gasto.h"

Gasto::Gasto(QString& fecha, QString& tipo, float coste, QString& descripcion) :
    m_fecha(fecha),
    m_tipo(tipo),
    m_coste(coste),
    m_descripcion(descripcion)
{
}

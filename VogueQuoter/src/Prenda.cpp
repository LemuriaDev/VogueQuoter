#include "Prenda.hpp"

#include <typeinfo>

Prenda::Prenda(uint32_t cantidadStock, ECalidad calidad)
	: m_Calidad(calidad), m_PrecioUnitario(), m_CantidadStock(cantidadStock)
{ }

void Prenda::SetPrecioUnitario(double precio)
{
	m_PrecioUnitario = precio;
}

double Prenda::GetPrecioUnitario() const
{
	return m_PrecioUnitario;
}

void Prenda::SetCalidad(ECalidad calidad)
{
	m_Calidad = calidad;
}

ECalidad Prenda::GetCalidad() const
{
	return m_Calidad;
}

uint32_t Prenda::GetCantidadStock() const
{
	return m_CantidadStock;
}

bool Prenda::operator==(const Prenda& other) const
{
	return this == &other|| typeid(*this) == typeid(other) && m_Calidad == other.m_Calidad && Equals(other);
}

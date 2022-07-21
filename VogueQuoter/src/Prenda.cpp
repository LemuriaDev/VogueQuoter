#include "Prenda.hpp"

Prenda::Prenda(uint32_t cantidadStock, ECalidad calidad)
	: Calidad(calidad), PrecioUnitario(), CantidadStock(cantidadStock)
{ }

void Prenda::SetPrecioUnitario(double precio)
{
	PrecioUnitario = precio;
}

double Prenda::GetPrecioUnitario() const
{
	return PrecioUnitario;
}

void Prenda::SetCalidad(ECalidad calidad)
{
	Calidad = calidad;
}

ECalidad Prenda::GetCalidad() const
{
	return Calidad;
}

uint32_t Prenda::GetCantidadStock() const
{
	return CantidadStock;
}
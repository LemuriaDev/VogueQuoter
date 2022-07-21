#include "Vendedor.hpp"

Vendedor::Vendedor(std::string nombre, std::string apellido, std::string codigo)
	: Nombre(nombre), Apellido(apellido), Codigo(codigo) { }

void Vendedor::Cotizar(Prenda const& prenda, uint32_t cantidad)
{
	Cotizaciones.emplace_back(Codigo, prenda, cantidad);
}

std::string const& Vendedor::GetNombre() const
{
	return Nombre;
}

std::string const& Vendedor::GetApellido() const
{
	return Apellido;
}

std::string const& Vendedor::GetCodigo() const
{
	return Codigo;
}

std::vector<Cotizacion> const& Vendedor::GetCotizaciones() const
{
	return Cotizaciones;
}
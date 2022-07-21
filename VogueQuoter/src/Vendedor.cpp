#include "Vendedor.hpp"

Vendedor::Vendedor(std::string nombre, std::string apellido, std::string codigo)
	: m_Nombre(nombre), m_Apellido(apellido), m_Codigo(codigo) { }

void Vendedor::Cotizar(Prenda const& prenda, uint32_t cantidad)
{
	m_Cotizaciones.emplace_back(m_Codigo, prenda, cantidad);
}

std::string const& Vendedor::GetNombre() const
{
	return m_Nombre;
}

std::string const& Vendedor::GetApellido() const
{
	return m_Apellido;
}

std::string const& Vendedor::GetCodigo() const
{
	return m_Codigo;
}

std::vector<Cotizacion> const& Vendedor::GetCotizaciones() const
{
	return m_Cotizaciones;
}
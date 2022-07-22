#include "Pantalon.hpp"

#include <sstream>

#include "magic_enum/magic_enum.hpp"


Pantalon::Pantalon(uint32_t cantidadStock, ETipoPantalon tipo, ECalidad calidad)
	: Prenda(cantidadStock, calidad), m_Tipo(tipo) { }

ETipoPantalon Pantalon::GetTipo() const
{
	return m_Tipo;
}

void Pantalon::SetTipo(ETipoPantalon tipo)
{
	m_Tipo = tipo;
}

double Pantalon::CalcularPrecio() const
{
	double precioCalculado = GetPrecioUnitario();

	switch (m_Tipo)
	{
	case ETipoPantalon::Chupin:
		precioCalculado *= 0.88;
		break;
	default: ;
	}

	switch (GetCalidad())
	{
	case ECalidad::Premium:
		precioCalculado *= 1.30;
		break;
	default: ;
	}

	return precioCalculado;
}

std::string Pantalon::Str() const
{
	using magic_enum::enum_name;
	std::ostringstream out;

	out << "Pantalon" << " | " << enum_name(m_Tipo) << " | " << enum_name(GetCalidad());
	return out.str();
}

bool Pantalon::Equals(Prenda const& other) const
{
	auto const& pantalon = static_cast<Pantalon const&>(other);

	return m_Tipo == pantalon.m_Tipo;
}
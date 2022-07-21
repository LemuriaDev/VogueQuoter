#include "Pantalon.hpp"

#include <sstream>

#include "magic_enum/magic_enum.hpp"


Pantalon::Pantalon(uint32_t cantidadStock, ETipoPantalon tipo, ECalidad calidad)
	: Prenda(cantidadStock, calidad), Tipo(tipo) { }

ETipoPantalon Pantalon::GetTipo() const
{
	return Tipo;
}

void Pantalon::SetTipo(ETipoPantalon tipo)
{
	Tipo = tipo;
}

double Pantalon::CalcularPrecio() const
{
	double precioCalculado = GetPrecioUnitario();

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

	out << "Pantalon" << " | " << enum_name(Tipo) << " | " << enum_name(GetCalidad());
	return out.str();
}
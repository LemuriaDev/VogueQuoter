#include "Camisa.hpp"

#include <sstream>

#include "magic_enum/magic_enum.hpp"


Camisa::Camisa(uint32_t cantidadStock, ETipoManga tipoManga, ETipoCuello tipoCuello, ECalidad calidad)
	: Prenda(cantidadStock, calidad), m_TipoManga(tipoManga), m_TipoCuello(tipoCuello) { }

ETipoManga Camisa::GetTipoManga() const
{
	return m_TipoManga;
}

void Camisa::SetTipoManga(ETipoManga tipo)
{
	m_TipoManga = tipo;
}

ETipoCuello Camisa::GetTipoCuello() const
{
	return m_TipoCuello;
}

void Camisa::SetTipoCuello(ETipoCuello tipo)
{
	m_TipoCuello = tipo;
}

double Camisa::CalcularPrecio() const
{
	auto precioCalculado = GetPrecioUnitario();

	switch (m_TipoManga)
	{
	case ETipoManga::Corta:
		precioCalculado *= 0.9;
	}

	switch (m_TipoCuello)
	{
	case ETipoCuello::Mao:
		precioCalculado *= 1.03;
		break;
	}

	switch (GetCalidad())
	{
	case ECalidad::Premium:
		precioCalculado *= 1.30;
		break;
	}

	return precioCalculado;
}

std::string Camisa::Str() const
{
	using magic_enum::enum_name;
	std::ostringstream out;

	out << "Camisa" << " | " << enum_name(m_TipoManga) << " | "
	<< enum_name(m_TipoCuello) << " | " << enum_name(GetCalidad());

	return out.str();
}
#include "Cotizacion.hpp"

// C++ Dates with STD: Have fun't!
// https://en.cppreference.com/w/cpp/chrono/current_zone
// https://en.cppreference.com/w/cpp/chrono/time_zone
// https://en.cppreference.com/w/cpp/utility/format/format
// https://en.cppreference.com/w/cpp/utility/format/formatter

UUIDv4::UUIDGenerator<std::mt19937_64> Cotizacion::UUIDGenerator;

Cotizacion::Cotizacion(std::string codigoVendedor, ::Prenda const& prenda, uint32_t cantidad)
	: m_Id(UUIDGenerator.getUUID().str()),
	m_FechaYHora(std::chrono::current_zone()->to_local(std::chrono::system_clock::now())),
	m_CodigoVendedor(std::move(codigoVendedor)),
	m_Prenda(prenda.Str()),
	m_Cantidad(cantidad),
	m_Total(prenda.CalcularPrecio() * m_Cantidad) { }
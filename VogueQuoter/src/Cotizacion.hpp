#pragma once
#include <chrono>

#include "Prenda.hpp"
#include "uuid_v4/uuid_v4.h"


using DateTime = std::chrono::local_time<std::chrono::system_clock::duration>;

class Cotizacion
{
public:
	Cotizacion(std::string codigoVendedor, Prenda const& prenda, uint32_t cantidad);

	/*
	 * Getters | Setters
	 */

	std::string const& GetId() const;
	DateTime const& GetFechaHora() const;
	std::string const& GetCodigoVendedor() const;
	std::string const& GetPrenda() const;
	double GetPrecioPrenda() const;
	uint32_t GetCantidad() const;
	double GetTotal() const;

private:
	static UUIDv4::UUIDGenerator<std::mt19937_64> UUIDGenerator;
	
	std::string m_Id;
	DateTime m_FechaYHora;
	std::string m_CodigoVendedor;
	std::string m_Prenda;
	double m_PrecioPrenda;
	uint32_t m_Cantidad;
	double m_Total;
};

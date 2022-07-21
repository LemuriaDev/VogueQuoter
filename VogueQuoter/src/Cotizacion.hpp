#pragma once
#include <chrono>

#include "Prenda.hpp"
#include "uuid_v4/uuid_v4.h"


using DateTime = std::chrono::local_time<std::chrono::system_clock::duration>;

class Cotizacion
{
public:
	Cotizacion(std::string codigoVendedor, Prenda const& prenda, uint32_t cantidad);

private:
	static UUIDv4::UUIDGenerator<std::mt19937_64> UUIDGenerator;
	
	std::string m_Id;
	DateTime m_FechaYHora;
	std::string m_CodigoVendedor;
	std::string m_Prenda;
	uint32_t m_Cantidad;
	double m_Total;
};

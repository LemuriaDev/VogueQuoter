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
	
	std::string Id;
	DateTime FechaYHora;
	std::string CodigoVendedor;
	std::string Prenda;
	uint32_t Cantidad;
	double Total;
};

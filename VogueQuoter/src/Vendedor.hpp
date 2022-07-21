#pragma once
#include <string>
#include <vector>

#include "Cotizacion.hpp"
#include "Prenda.hpp"


class Vendedor
{
public:
	Vendedor(std::string nombre, std::string apellido, std::string codigo);

	void Cotizar(Prenda const& prenda, uint32_t cantidad);

	/*
	 * Getters | Setters
	 */

	std::string const& GetNombre() const;
	std::string const& GetApellido() const;
	std::string const& GetCodigo() const;
	std::vector<Cotizacion> const& GetCotizaciones() const;
	
private:
	std::string m_Nombre;
	std::string m_Apellido;
	std::string m_Codigo;

	std::vector<Cotizacion> m_Cotizaciones;
};


#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Prenda.hpp"
#include "Vendedor.hpp"

class Tienda
{
public:
	Tienda(std::string nombre, std::string direccion, Vendedor const& vendedor);

	/*
	 * Getters | Setters
	 */

	std::string const& GetNombre() const;
	std::string const& GetDireccion() const;
	Vendedor const& GetVendedor() const;	

	/*
	 * Operaciones
	 */

	uint32_t GetStockDePrenda(Prenda const& prenda) const;
	void AgregarPrenda(std::unique_ptr<Prenda> prenda);
	void Cotizar(Prenda const& prenda, uint32_t cantidad);

private:
	std::string m_Nombre;
	std::string m_Direccion;
	Vendedor m_Vendedor;
	std::vector<std::unique_ptr<Prenda>> m_Prendas;
};


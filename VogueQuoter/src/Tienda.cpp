#include "Tienda.hpp"

Tienda::Tienda(std::string nombre, std::string direccion, Vendedor const& vendedor)
	: m_Nombre(nombre), m_Direccion(direccion), m_Vendedor(vendedor)
{ }

std::string const& Tienda::GetNombre() const
{
	return m_Nombre;
}

std::string const& Tienda::GetDireccion() const
{
	return m_Direccion;
}

Vendedor const& Tienda:: GetVendedor() const
{
	return m_Vendedor;
}

void Tienda::AgregarPrenda(std::unique_ptr<Prenda> prenda)
{
	m_Prendas.emplace_back(std::move(prenda));
}

uint32_t Tienda::GetStockDePrenda(Prenda const& prenda) const
{
	auto const& found = std::ranges::find_if(m_Prendas,
		[&prenda](std::unique_ptr<Prenda> const& other)
		{
			return prenda == *other.get();
		}
	);

	if (found == m_Prendas.end())
	{
		return 0;
	}

	return found->get()->GetCantidadStock();
}

void Tienda::Cotizar(Prenda const& prenda, uint32_t cantidad)
{
	m_Vendedor.Cotizar(prenda, cantidad);
}
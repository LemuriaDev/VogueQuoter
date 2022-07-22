#pragma once
#include "IRenderable.hpp"
#include "Tienda.hpp"


class HistorialCotizaciones : public IRenderable
{
public:
	explicit HistorialCotizaciones(Vendedor const& vendedor);

	void Render(bool* isOpen) override;

private:
	Vendedor const& m_Vendedor;
};


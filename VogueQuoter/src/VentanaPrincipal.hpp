#pragma once
#include <memory>

#include "ETipoCuello.hpp"
#include "ETipoManga.hpp"
#include "ETipoPantalon.hpp"
#include "IRenderable.hpp"
#include "Prenda.hpp"
#include "Tienda.hpp"
#include "HistorialCotizaciones.hpp"
#include "ETipoPrenda.hpp"


struct InputModel
{
	ETipoPrenda tipoPrenda;
	ETipoManga tipoManga;
	ETipoCuello tipoCuello;
	ETipoPantalon tipoPantalon;
	ECalidad calidad;
	double precioUnitario;
	uint32_t cantidad;

	InputModel(ETipoPrenda tipo_prenda, ETipoManga tipo_manga, ETipoCuello tipo_cuello, ETipoPantalon tipo_pantalon,
		ECalidad calidad, double precio_unitario, uint32_t cantidad)
		: tipoPrenda(tipo_prenda),
		tipoManga(tipo_manga),
		tipoCuello(tipo_cuello),
		tipoPantalon(tipo_pantalon),
		calidad(calidad),
		precioUnitario(precio_unitario),
		cantidad(cantidad)
	{ }
};

class VentanaPrincipal final :
    public IRenderable
{
public:
	VentanaPrincipal(std::unique_ptr<Tienda> tienda);

	void Render(bool* isOpen) override;

private:
	std::unique_ptr<Prenda> m_PrendaPtr;
	std::unique_ptr<Tienda> m_TiendaPtr;
	HistorialCotizaciones m_Historial;
	bool m_ShowHistory;
	InputModel m_InputModel;

	/**
	 * Actualiza los datos de la prenda usando los datos actuales del InputModel.
	 * Se llama cada frame que cambia un input.
	 */
	void UpdatePrenda();

};

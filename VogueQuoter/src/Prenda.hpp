#pragma once
#include "ECalidad.hpp"
#include <cstdint>
#include <string>


class Prenda
{
public:
	virtual ~Prenda() = default;

	/*
	 * Getters | Setters
	 */

	void SetPrecioUnitario(double precio);
	double GetPrecioUnitario() const;

	void SetCalidad(ECalidad calidad);
	ECalidad GetCalidad() const;

	uint32_t GetCantidadStock() const;

	/*
	 * Operaciones
	 */

	virtual double CalcularPrecio() const = 0;

	/*
	 * Operadores | Conversiones
	 */

	bool operator==(const Prenda&) const = default;

	/**
	 * <summary>Representacion de la prenda en formato string.</summary>
	 */
	virtual std::string Str() const = 0;

protected:
	Prenda() = default;
	Prenda(uint32_t cantidadStock, ECalidad calidad);

private:
	ECalidad Calidad;
	double PrecioUnitario;
	uint32_t CantidadStock;
};



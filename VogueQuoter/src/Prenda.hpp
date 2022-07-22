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
	
	/**
	 * \brief Calcula el precio final de una prenda aplicando operaciones sobre su precio base.
	 * \return El precio calculado.
	 */
	virtual double CalcularPrecio() const = 0;

	/*
	 * Operadores | Conversiones
	 */

	bool operator==(const Prenda&) const;

	/**
	 * \brief Crea una representacion de la prenda en formato string.
	 */
	virtual std::string Str() const = 0;

protected:
	Prenda() = default;
	Prenda(uint32_t cantidadStock, ECalidad calidad);

private:
	ECalidad m_Calidad;
	double m_PrecioUnitario;
	uint32_t m_CantidadStock;

	
	/**
	 * \pre Solo se llama si \a other es del mismo tipo.
	 * \brief Compara una prenda con otra.
	 * \param other La otra prenda.
	 * \return \a true solamente si son iguales.
	 */
	virtual bool Equals(Prenda const& other) const = 0;
};



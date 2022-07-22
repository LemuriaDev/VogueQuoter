#pragma once
#include "ETipoPantalon.hpp"
#include "Prenda.hpp"

class Pantalon final :
    public Prenda
{
public:
    Pantalon() = default;
    virtual ~Pantalon() = default;
    Pantalon(uint32_t cantidadStock, ETipoPantalon tipo, ECalidad calidad);

    /*
     * Getters | Setters
     */

    ETipoPantalon GetTipo() const;
    void SetTipo(ETipoPantalon tipo);

    /*
     * Operaciones
     */

    double CalcularPrecio() const override;

    /*
     * Conversiones
     */

    std::string Str() const override;

private:
    ETipoPantalon m_Tipo;

    bool Equals(Prenda const& other) const override;
};


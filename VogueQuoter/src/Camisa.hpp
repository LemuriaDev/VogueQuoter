#pragma once
#include "ETipoCuello.hpp"
#include "ETipoManga.hpp"
#include "Prenda.hpp"

class Camisa final :
    public Prenda
{
public:
    Camisa() = default;
    virtual ~Camisa() = default;
    Camisa(uint32_t cantidadStock, ETipoManga tipoManga, ETipoCuello tipoCuello, ECalidad calidad);

    /*
     * Getters | Setters
     */

    ETipoManga GetTipoManga() const;
    void SetTipoManga(ETipoManga tipo);

    ETipoCuello GetTipoCuello() const;
    void SetTipoCuello(ETipoCuello tipo);

    /*
     * Operaciones
     */

    double CalcularPrecio() const override;

    /*
     * Conversiones
     */

    std::string Str() const override;

private:
    ETipoManga m_TipoManga;
    ETipoCuello m_TipoCuello;

    bool Equals(Prenda const& other) const override;
};


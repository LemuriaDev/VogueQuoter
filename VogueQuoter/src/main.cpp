#if defined _WIN32
#define NOMINMAX
#endif

#include "ImGuiWrapper.hpp"
#include "VentanaPrincipal.hpp"
#include "Camisa.hpp"
#include "Pantalon.hpp"

std::unique_ptr<Tienda> CargarDatosDePrueba()
{
    auto tienda = std::make_unique<Tienda>("Ropenmeister", "Calle Alemania 515",
        Vendedor{ "Juan", "Chito", "QR007" });

    tienda->AgregarPrenda(std::make_unique<Camisa>(100, ETipoManga::Corta, ETipoCuello::Mao, ECalidad::Standard));
    tienda->AgregarPrenda(std::make_unique<Camisa>(100, ETipoManga::Corta, ETipoCuello::Mao, ECalidad::Premium));

    tienda->AgregarPrenda(std::make_unique<Camisa>(150, ETipoManga::Corta, ETipoCuello::Comun, ECalidad::Standard));
    tienda->AgregarPrenda(std::make_unique<Camisa>(150, ETipoManga::Corta, ETipoCuello::Comun, ECalidad::Premium));

    tienda->AgregarPrenda(std::make_unique<Camisa>(75, ETipoManga::Larga, ETipoCuello::Mao, ECalidad::Standard));
    tienda->AgregarPrenda(std::make_unique<Camisa>(75, ETipoManga::Larga, ETipoCuello::Mao, ECalidad::Premium));

    tienda->AgregarPrenda(std::make_unique<Camisa>(175, ETipoManga::Larga, ETipoCuello::Comun, ECalidad::Standard));
    tienda->AgregarPrenda(std::make_unique<Camisa>(175, ETipoManga::Larga, ETipoCuello::Comun, ECalidad::Premium));

    tienda->AgregarPrenda(std::make_unique<Pantalon>(750, ETipoPantalon::Chupin, ECalidad::Standard));
    tienda->AgregarPrenda(std::make_unique<Pantalon>(750, ETipoPantalon::Chupin, ECalidad::Premium));

    tienda->AgregarPrenda(std::make_unique<Pantalon>(250, ETipoPantalon::Comun, ECalidad::Standard));
    tienda->AgregarPrenda(std::make_unique<Pantalon>(250, ETipoPantalon::Comun, ECalidad::Premium));

    return tienda;
}

int main()
{
	ImGuiWrapper::AddWindow(std::make_unique<VentanaPrincipal>(std::move(CargarDatosDePrueba())));
	ImGuiWrapper::StartImGui();
	return 0;
}
#include "VentanaPrincipal.hpp"

#include "Camisa.hpp"
#include "imgui_extensions.hpp"
#include "Pantalon.hpp"
#include "imgui/imgui.h"


static const char* tiposDeManga[] = { "Manga Corta", "Manga Larga" };
static const char* tiposDeCuello[] = { "Cuello Comun", "Cuello Mao" };
static const char* tiposDePantalon[] = { "Pantalon Comun", "Chupin" };

VentanaPrincipal::VentanaPrincipal(std::unique_ptr<Tienda> tienda)
    : m_PrendaPtr(std::make_unique<Camisa>(0, ETipoManga::Corta, ETipoCuello::Comun, ECalidad::Standard)),
    m_TiendaPtr(std::move(tienda)),
    m_Historial(m_TiendaPtr->GetVendedor()),
    m_ShowHistory(false),
    m_InputModel(ETipoPrenda::Camisa, ETipoManga::Corta, ETipoCuello::Comun, ETipoPantalon::Comun, ECalidad::Standard, 0, 0)
{ }

void VentanaPrincipal::UpdatePrenda()
{
    m_PrendaPtr->SetPrecioUnitario(m_InputModel.precioUnitario);
    m_PrendaPtr->SetCalidad(m_InputModel.calidad);

    switch (m_InputModel.tipoPrenda)
    {
    case ETipoPrenda::Camisa:
        if (auto camisa = dynamic_cast<Camisa*>(m_PrendaPtr.get()))
        {
            camisa->SetTipoCuello(m_InputModel.tipoCuello);
            camisa->SetTipoManga(m_InputModel.tipoManga);
        }
        else
            m_PrendaPtr = std::make_unique<Camisa>(0, m_InputModel.tipoManga, m_InputModel.tipoCuello, m_InputModel.calidad);
        break;

    case ETipoPrenda::Pantalon:
        if (auto pantalon = dynamic_cast<Pantalon*>(m_PrendaPtr.get()))
            pantalon->SetTipo(m_InputModel.tipoPantalon);
        else
            m_PrendaPtr = std::make_unique<Pantalon>(0, m_InputModel.tipoPantalon, m_InputModel.calidad);
        break;
    }
}

void VentanaPrincipal::Render(bool* isOpen)
{
    bool anyValueChanged = false;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 400, 301 });

    {
        ImGui::Begin("Vogue - Cotizador Express");
        ImGui::Text(m_TiendaPtr->GetNombre().c_str());
        float const textWidth = ImGui::CalcTextSize(m_TiendaPtr->GetDireccion().c_str()).x;
        ImGui::SameLine(0, ImGui::GetContentRegionAvail().x - ImGui::GetItemRectSize().x - textWidth - ImGui::GetStyle().ItemSpacing.x);
        ImGui::Text(m_TiendaPtr->GetDireccion().c_str());
    }

    ImGui::Separator();

    {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s %s | %s", m_TiendaPtr->GetVendedor().GetNombre().c_str(), m_TiendaPtr->GetVendedor().GetApellido().c_str(), m_TiendaPtr->GetVendedor().GetCodigo().c_str());
        float const textWidth = ImGui::CalcTextSize("Historial de Cotizaciones").x;
        ImGui::SameLine(0, ImGui::GetContentRegionAvail().x - ImGui::GetItemRectSize().x - textWidth - ImGui::GetStyle().ItemSpacing.x);
        if (ImGui::Button("Historial de Cotizaciones", { -1, 0 }))
        {
            m_ShowHistory = true;
        }
    }

    ImGui::Separator();

    {
        float constexpr radioWidth = 100.f;
        ImGui::BeginGroupPanel("Prenda", { 0, 0 });
        float const totalWidth = ImGui::GetContentRegionAvail().x;
        ImGui::SetNextItemWidth(radioWidth);
        anyValueChanged |= ImGui::RadioButton("Camisa", reinterpret_cast<int*>(&m_InputModel.tipoPrenda), (int)ETipoPrenda::Camisa);

        ImGui::PushItemWidth((totalWidth - radioWidth) / 2 - ImGui::GetStyle().ItemSpacing.x);
        ImGui::SameLine(radioWidth);
        anyValueChanged |= ImGui::Combo("##manga", reinterpret_cast<int*>(&m_InputModel.tipoManga), tiposDeManga, 2);
        ImGui::SameLine();
        anyValueChanged |= ImGui::Combo("##cuello", reinterpret_cast<int*>(&m_InputModel.tipoCuello), tiposDeCuello, 2);
        ImGui::PopItemWidth();

        ImGui::SeparatorH(totalWidth - ImGui::GetStyle().ItemSpacing.x);

        ImGui::SetNextItemWidth(radioWidth);
        anyValueChanged |= ImGui::RadioButton("Pantalon", reinterpret_cast<int*>(&m_InputModel.tipoPrenda), (int)ETipoPrenda::Pantalon);
        ImGui::SameLine(radioWidth);
        ImGui::SetNextItemWidth((totalWidth - radioWidth) / 2 - ImGui::GetStyle().ItemSpacing.x);
        anyValueChanged |= ImGui::Combo("##pantalon", reinterpret_cast<int*>(&m_InputModel.tipoPantalon), tiposDePantalon, 2);
        ImGui::EndGroupPanel();
    }

    {
        ImGui::BeginGroupPanel("Stock");
        ImGui::Text("Unidades disponibles: %u", m_TiendaPtr->GetStockDePrenda(*m_PrendaPtr));
        ImGui::EndGroupPanel();
    }

    {
        ImGui::BeginGroupPanel("Calidad");
        anyValueChanged |= ImGui::RadioButton("Standard", reinterpret_cast<int*>(&m_InputModel.calidad), (int)ECalidad::Standard);
        ImGui::SameLine();
        anyValueChanged |= ImGui::RadioButton("Premium", reinterpret_cast<int*>(&m_InputModel.calidad), (int)ECalidad::Premium);
        ImGui::EndGroupPanel();

        ImGui::SameLine();

        ImGui::BeginGroupPanel("Precio y Cantidad");
        auto w = ImGui::GetContentRegionAvail().x;
        ImGui::PushItemWidth(w / 2 - ImGui::GetStyle().ItemSpacing.x);
        anyValueChanged |= ImGui::InputDouble("##PrecioUnitario", &m_InputModel.precioUnitario, 0, 0, "$%.2f");
        ImGui::SameLine();
        anyValueChanged |= ImGui::InputScalar("##Cantidad", ImGuiDataType_U32, &m_InputModel.cantidad);
        m_InputModel.cantidad = std::max(1u, m_InputModel.cantidad);
        ImGui::PopItemWidth();
        ImGui::EndGroupPanel();
    }

    if (anyValueChanged)
    {
	    UpdatePrenda();
    }

	{
		auto const& cotizaciones = m_TiendaPtr->GetVendedor().GetCotizaciones();
    	double total = cotizaciones.empty() ? 0.0 : cotizaciones.back().GetTotal();
    	ImGui::BeginGroupPanel("Cotizacion");
    	ImGui::Text(std::format("${:.2f}", total).c_str());
    	ImGui::EndGroupPanel();
	}

    uint32_t stock = m_TiendaPtr->GetStockDePrenda(*m_PrendaPtr);
    
    if (ImGui::ButtonAlignedOnLine("Cotizar", {0,0}, 0.5))
    {
        if (m_InputModel.cantidad <= stock)
            m_TiendaPtr->Cotizar(*m_PrendaPtr, m_InputModel.cantidad);
        else
            ImGui::OpenPopup("Info.");
    }

    ImVec2 const center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Info.", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("No hay suficiente stock!");
        if (ImGui::ButtonAlignedOnLine("Ok", { 75, 0 }))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    if (m_ShowHistory)
    {
        m_Historial.Render(&m_ShowHistory);
    }

    ImGui::End();

    ImGui::PopStyleVar();
}


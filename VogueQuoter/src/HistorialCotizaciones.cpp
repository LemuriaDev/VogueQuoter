#include "HistorialCotizaciones.hpp"

#include "imgui/imgui.h"


HistorialCotizaciones::HistorialCotizaciones(Vendedor const& vendedor)
	: m_Vendedor(vendedor)
{ }

void HistorialCotizaciones::Render(bool* isOpen)
{
    using namespace ImGui;
    PushStyleVar(ImGuiStyleVar_WindowMinSize, { 1110,310 });

    if (!Begin("Historial", isOpen))
    {
        End();
        PopStyleVar();
        return;
    }

    ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingStretchProp;
    if (!BeginTable("Table", 7, flags))
    {
        End();
        PopStyleVar();
        return;
    }

    TableSetupColumn("Id", ImGuiTableColumnFlags_None, 1.7160f);
    TableSetupColumn("Fecha y Hora", ImGuiTableColumnFlags_None, 0.9056f);
    TableSetupColumn("Codigo del Vendedor", ImGuiTableColumnFlags_None, 0.9056f);
    TableSetupColumn("Prenda", ImGuiTableColumnFlags_None, 1.5730f);
    TableSetupColumn("Precio Unitario", ImGuiTableColumnFlags_None, 0.7150f);
    TableSetupColumn("Cantidad", ImGuiTableColumnFlags_None, 0.4903f);
    TableSetupColumn("Total", ImGuiTableColumnFlags_None, 0.6946f);
    TableSetupScrollFreeze(0, 1);
    TableHeadersRow();
    for (const auto& cotizacion : m_Vendedor.GetCotizaciones())
    {
        TableNextRow();
        TableNextColumn();

        Selectable(cotizacion.GetId().c_str(), false, ImGuiSelectableFlags_SpanAllColumns);
        TableNextColumn();
        Text(std::format("{:%Y/%m/%d %X}", cotizacion.GetFechaHora()).c_str());
        TableNextColumn();
        Text(cotizacion.GetCodigoVendedor().c_str());
        TableNextColumn();
        Text(cotizacion.GetPrenda().c_str());
        TableNextColumn();
        Text(std::format("${:.2f}", cotizacion.GetPrecioPrenda()).c_str());
        TableNextColumn();
        Text("%u", cotizacion.GetCantidad());
        TableNextColumn();
        Text(std::format("${:.2f}", cotizacion.GetTotal()).c_str());
    }
    EndTable();

    End();
    PopStyleVar();
}
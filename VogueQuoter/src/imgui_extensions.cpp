#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_extensions.hpp"

#include <algorithm>

#include "imgui/imgui_internal.h"


static ImVector<ImRect> s_GroupPanelLabelStack;

void ImGui::BeginGroupPanel(const char* name, const ImVec2& size)
{
    BeginGroup();

    auto cursorPos = GetCursorScreenPos();
    auto itemSpacing = GetStyle().ItemSpacing;
    PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

    auto frameHeight = GetFrameHeight();
    BeginGroup();

    ImVec2 effectiveSize = size;
    if (size.x < 0.0f)
        effectiveSize.x = GetContentRegionAvail().x;
    else
        effectiveSize.x = size.x;
    Dummy(ImVec2(effectiveSize.x, 0.0f));

    Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
    SameLine(0.0f, 0.0f);
    BeginGroup();
    Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
    SameLine(0.0f, 0.0f);
    if (name)
        TextUnformatted(name);
    auto labelMin = name ? GetItemRectMin() : ImVec2{ 0,0 };
    auto labelMax = name ? GetItemRectMax() : ImVec2{ 0, 0 };
    SameLine(0.0f, 0.0f);
    Dummy(ImVec2(0.0, frameHeight + itemSpacing.y));
    BeginGroup();

    //ImGui::GetWindowDrawList()->AddRect(labelMin, labelMax, IM_COL32(255, 0, 255, 255));

    PopStyleVar(2);

#if IMGUI_VERSION_NUM >= 17301
    GetCurrentWindow()->ContentRegionRect.Max.x -= frameHeight * 0.5f;
    GetCurrentWindow()->WorkRect.Max.x -= frameHeight * 0.5f;
    GetCurrentWindow()->InnerRect.Max.x -= frameHeight * 0.5f;
#else
    ImGui::GetCurrentWindow()->ContentsRegionRect.Max.x -= frameHeight * 0.5f;
#endif
    GetCurrentWindow()->Size.x -= frameHeight;

    auto itemWidth = CalcItemWidth();
    PushItemWidth(ImMax(0.0f, itemWidth - frameHeight));

    s_GroupPanelLabelStack.push_back(ImRect(labelMin, labelMax));
}

void ImGui::EndGroupPanel()
{
    PopItemWidth();

    auto itemSpacing = GetStyle().ItemSpacing;

    PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

    auto frameHeight = GetFrameHeight();

    EndGroup();

    //ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(0, 255, 0, 64), 4.0f);

    EndGroup();

    SameLine(0.0f, 0.0f);
    Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
    //ImGui::Dummy(ImVec2(0.0, frameHeight - frameHeight * 0.5f - itemSpacing.y));
    Dummy(ImVec2(0.0, frameHeight * 0.5f));

    EndGroup();

    auto itemMin = GetItemRectMin();
    auto itemMax = GetItemRectMax();
    //ImGui::GetWindowDrawList()->AddRectFilled(itemMin, itemMax, IM_COL32(255, 0, 0, 64), 4.0f);

    auto labelRect = s_GroupPanelLabelStack.back();
    s_GroupPanelLabelStack.pop_back();

    ImVec2 halfFrame = ImVec2(frameHeight * 0.25f, frameHeight) * 0.5f;
    ImRect frameRect = ImRect(itemMin + halfFrame, itemMax - ImVec2(halfFrame.x, 0.0f));
    labelRect.Min.x -= itemSpacing.x;
    labelRect.Max.x += itemSpacing.x;
    for (int i = 0; i < 4; ++i)
    {
        switch (i)
        {
            // left half-plane
        case 0: PushClipRect(ImVec2(-FLT_MAX, -FLT_MAX), ImVec2(labelRect.Min.x, FLT_MAX), true); break;
            // right half-plane
        case 1: PushClipRect(ImVec2(labelRect.Max.x, -FLT_MAX), ImVec2(FLT_MAX, FLT_MAX), true); break;
            // top
        case 2: PushClipRect(ImVec2(labelRect.Min.x, -FLT_MAX), ImVec2(labelRect.Max.x, labelRect.Min.y), true); break;
            // bottom
        case 3: PushClipRect(ImVec2(labelRect.Min.x, labelRect.Max.y), ImVec2(labelRect.Max.x, FLT_MAX), true); break;
        }

        GetWindowDrawList()->AddRect(
            frameRect.Min, frameRect.Max,
            ImColor(GetStyleColorVec4(ImGuiCol_Border)),
            halfFrame.x);

        PopClipRect();
    }

    PopStyleVar(2);

#if IMGUI_VERSION_NUM >= 17301
    GetCurrentWindow()->ContentRegionRect.Max.x += frameHeight * 0.5f;
    GetCurrentWindow()->WorkRect.Max.x += frameHeight * 0.5f;
    GetCurrentWindow()->InnerRect.Max.x += frameHeight * 0.5f;
#else
    ImGui::GetCurrentWindow()->ContentsRegionRect.Max.x += frameHeight * 0.5f;
#endif
    GetCurrentWindow()->Size.x += frameHeight;

    Dummy(ImVec2(0.0f, 0.0f));

    EndGroup();
}

void ImGui::SeparatorH(float width)
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return;

    ImGuiContext& g = *GImGui;

    float thickness_draw = 1.0f;
    float thickness_layout = 0.0f;

    // Horizontal Separator
    float x1 = window->Pos.x;
    float x2;

    // FIXME-WORKRECT: old hack (#205) until we decide of consistent behavior with WorkRect/Indent and Separator
    if (g.GroupStack.Size > 0 && g.GroupStack.back().WindowID == window->ID)
        x1 += window->DC.Indent.x;

    // FIXME-WORKRECT: In theory we should simply be using WorkRect.Min.x/Max.x everywhere but it isn't aesthetically what we want,
    // need to introduce a variant of WorkRect for that purpose. (#4787)
    if (ImGuiTable* table = g.CurrentTable)
        x1 = table->Columns[table->CurrentColumn].MinX;

    x2 = x1 + width;

    // We don't provide our width to the layout so that it doesn't get feed back into AutoFit
    // FIXME: This prevents ->CursorMaxPos based bounding box evaluation from working (e.g. TableEndCell)
    const ImRect bb(ImVec2(x1, window->DC.CursorPos.y), ImVec2(x2, window->DC.CursorPos.y + thickness_draw));
    ItemSize(ImVec2(0.0f, thickness_layout));
    const bool item_visible = ItemAdd(bb, 0);
    if (item_visible)
    {
        // Draw
        window->DrawList->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), GetColorU32(ImGuiCol_Separator));
        if (g.LogEnabled)
            LogRenderedText(&bb.Min, "--------------------------------\n");
    }
}

bool ImGui::ButtonAlignedOnLine(const char* label, ImVec2 const& v2, float alignment)
{
    ImGuiStyle& style = GetStyle();

    float size = std::max(CalcTextSize(label).x + style.FramePadding.x * 2.0f, v2.x);
    float avail = GetContentRegionAvail().x;

    float off = (avail - size) * alignment;
    if (off > 0.0f)
        SetCursorPosX(GetCursorPosX() + off);

    return Button(label, v2);
}
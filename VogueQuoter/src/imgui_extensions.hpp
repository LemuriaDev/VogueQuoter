#pragma once
#include "imgui/imgui.h"

namespace ImGui
{
	void BeginGroupPanel(const char* name = nullptr, const ImVec2& size = ImVec2(0.0f, 0.0f));
	void EndGroupPanel();
	void SeparatorH(float width);
	bool ButtonAlignedOnLine(const char* label, ImVec2 const& size = ImVec2{ 0,0 }, float alignment = 0.5f);
}

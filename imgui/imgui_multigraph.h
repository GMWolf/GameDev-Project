#pragma once
#include "imgui.h"

namespace ImGui
{
	void PlotMultiHistogram(const char* label, float (*values_getter)(void* data, int idg, int idx), void* data,
	                        int values_count, int data_count, ImColor* colors,
		int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
}

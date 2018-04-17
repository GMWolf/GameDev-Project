#include "imgui_multigraph.h"
#include "imgui_internal.h"

const ImVec2 operator+(const ImVec2& a, const ImVec2& b)
{
	return ImVec2(a.x + b.x, a.y + b.y);
}

const ImVec2 operator-(const ImVec2& a, const ImVec2& b)
{
	return ImVec2(a.x - b.x, a.y - b.y);
}

void ImGui::PlotMultiHistogram(const char* label, float(* values_getter)(void* data, int idg, int idx), void* data,
	int values_count, int data_count, ImColor* colors, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	if(graph_size.x == 0.0f)
		graph_size.x = CalcItemWidth();
	if (graph_size.y == 0.0f)
		graph_size.y = label_size.y + (style.FramePadding.y * 2);

	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(graph_size.x, graph_size.y));
	const ImRect inner_bb(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding);
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0));
	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, 0, &frame_bb))
		return;

	// Determine scale from values if not specified
	if (scale_min == FLT_MAX || scale_max == FLT_MAX)
	{
		float v_min = FLT_MAX;
		float v_max = -FLT_MAX;
		for (int i = 0; i < data_count; i++) {
			for (int j = 0; j < values_count; j++)
			{
				const float v = values_getter(data, i, j);
				v_min = ImMin(v_min, v);
				v_max = ImMax(v_max, v);
			}
			if (scale_min == FLT_MAX)
				scale_min = v_min;
			if (scale_max == FLT_MAX)
				scale_max = v_max;
		}
	}

	RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

	int res_w = ImMin((int)graph_size.x, values_count);
	int item_count = values_count;
	
	
	float t = 1.0f / res_w;

	for(int idx = 0; idx < res_w; idx++)
	{
		float t0 = t * idx;
		float t1 = t0 + t;

		

		for(int idg = 0; idg < data_count; idg++)
		{
			const ImU32 col = colors[idg];
			const float value = values_getter(data, idg, idx);

			const ImVec2 tp0 = ImVec2(t0, 1.0f - ImSaturate((value - scale_min) / (scale_max - scale_min)));
			const ImVec2 tp1 = ImVec2(t1, 1.0f);

			const ImVec2 pos0 = ImLerp(inner_bb.Min, inner_bb.Max, tp0);
			ImVec2 pos1 = ImLerp(inner_bb.Min, inner_bb.Max, tp1);

			if (pos1.x >= pos0.x + 2.0f)
				pos1.x -= 1.0f;

			window->DrawList->AddRectFilled(pos0, pos1, col);
		}
	}
		
	RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, inner_bb.Min.y), label);
}

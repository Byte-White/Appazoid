#include "Gui.h"

namespace ImGui
{
	void Image(const az::Image& img, const glm::ivec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col)
	{
		ImGui::Image((void*)(img.GetTextureID()), { (float)size.x,(float)size.y },uv0,uv1,tint_col,border_col);
	}
	bool ImageButton(const az::Image& img, const glm::ivec2& size, const ImVec2& uv0, const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)
	{
		return	ImGui::ImageButton((void*)(img.GetTextureID()), { (float)size.x,(float)size.y }, uv0, uv1, frame_padding,bg_col,tint_col);
	}
}
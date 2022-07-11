#pragma
#include "imgui.h"
#include "glm/glm.hpp"
#include "../../Appazoid/include/Appazoid/UI/Image.h"
#include "Core/Base.h"

//Custom Gui functions +
namespace ImGui
{
	template<typename size_type /* = glm::ivec2 */>
	void Image(
		const az::Ref<az::Image> img, 
		const size_type& size, 
		const ImVec2& uv0 = ImVec2(0, 0), 
		const ImVec2& uv1 = ImVec2(1, 1), 
		const ImVec4& tint_col = ImVec4(1, 1, 1, 1), 
		const ImVec4& border_col = ImVec4(0, 0, 0, 0));

	bool ImageButton(
		const az::Ref<az::Image> img,
		const glm::ivec2& size, 
		const ImVec2& uv0 = ImVec2(0, 0),
		const ImVec2& uv1 = ImVec2(1, 1), 
		int frame_padding = -1, 
		const ImVec4& bg_col = ImVec4(0, 0, 0, 0), 
		const ImVec4& tint_col = ImVec4(1, 1, 1, 1));

}

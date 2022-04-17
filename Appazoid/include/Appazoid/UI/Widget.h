#pragma once

namespace az
{
	class Widget
	{
	public:
		bool visible = true;
		virtual ~Widget() = default;
		virtual void OnRender(){};
		virtual void OnConstruction(){};
		virtual void OnDestruction(){};
	};

}
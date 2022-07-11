#pragma once
#include "LayerStack.h"
#include <vector>
#include <string>
#include <memory>
#include "../../include/Appazoid/UI/Layer.h"
#include "Core/Base.h"

namespace az
{
	class LayerStack
	{
	public:
		using Layer_T = az::Layer;
		using Layer_Ptr = az::Ref<Layer_T>;
		using Layer_Container_Data_T = std::pair<std::string, Layer_Ptr>;
		using Layer_Container_T = std::vector<Layer_Container_Data_T>;
	private:
		Layer_Container_T m_Layers;
		unsigned int m_InsertIndex = 0;
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(std::string name, const Layer_Ptr& layer);//pushes the layer in front of the index
		void PushOverlay(std::string name, const Layer_Ptr& layer);//pushes the layer to the back of the stack

		void PopLayer(const Layer_Ptr& layer);
		void PopLayer(const std::string& layer_name);
		void PopOverlay(const Layer_Ptr& overlay);
		void PopOverlay(const std::string& overlay_name);

		//Iterators

		Layer_Container_T::iterator begin() { return m_Layers.begin(); }
		Layer_Container_T::iterator end() { return m_Layers.end(); }
		Layer_Container_T::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		Layer_Container_T::reverse_iterator rend() { return m_Layers.rend(); }

		Layer_Container_T::const_iterator begin() const { return m_Layers.begin(); }
		Layer_Container_T::const_iterator end()	const { return m_Layers.end(); }
		Layer_Container_T::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		Layer_Container_T::const_reverse_iterator rend() const { return m_Layers.rend(); }
		
		// Find layers
		Layer_Container_T::iterator find(std::string layer_name);
		Layer_Container_T::iterator find(Layer_Ptr layer);
		
	};


	bool operator==(LayerStack::Layer_Container_Data_T base, LayerStack::Layer_Ptr compare);
	bool operator==(LayerStack::Layer_Container_Data_T base, std::string compare);
}
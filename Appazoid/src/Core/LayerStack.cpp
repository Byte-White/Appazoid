#include "LayerStack.h"

namespace az
{
	LayerStack::LayerStack()
	{
		//Doesnt call layer.OnConstruction
	}
	LayerStack::~LayerStack()
	{
		//Doesnt call layer.OnDestruction
	}
	

	void LayerStack::PushLayer(std::string name, const Layer_Ptr& layer)
	{
		m_Layers.emplace(m_Layers.begin() + this->m_InsertIndex, std::make_pair(name, layer));
		this->m_InsertIndex++;
	}

	void LayerStack::PushOverlay(std::string name, const Layer_Ptr& layer)
	{
		m_Layers.emplace_back(std::make_pair(name,layer));
	}


	void LayerStack::PopLayer(const Layer_Ptr& layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer);
		if (it != m_Layers.begin() + m_InsertIndex)
		{
			layer->OnDestruction();
			m_Layers.erase(it);
			m_InsertIndex--;
		}
	}
	void LayerStack::PopLayer(const std::string& layer_name)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer_name);
		if (it != m_Layers.begin() + m_InsertIndex)
		{
			it->second->OnDestruction();
			m_Layers.erase(it);
			m_InsertIndex--;
		}
	}

	void LayerStack::PopOverlay(const Layer_Ptr& overlay)
	{
		auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDestruction();
			m_Layers.erase(it);
		}
	}

	void LayerStack::PopOverlay(const std::string& overlay_name)
	{
		auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay_name);
		if (it != m_Layers.end())
		{
			it->second->OnDestruction();
			m_Layers.erase(it);
		}
	}

	LayerStack::Layer_Container_T::iterator LayerStack::find(std::string layer_name)
	{
		return std::find(m_Layers.begin(), m_Layers.end(), layer_name);
	}

	LayerStack::Layer_Container_T::iterator LayerStack::find(Layer_Ptr layer)
	{
		return std::find(m_Layers.begin(), m_Layers.end(), layer);
	}


	bool operator==(LayerStack::Layer_Container_Data_T base, LayerStack::Layer_Ptr compare)
	{
		return base.second == compare;
	}
	bool operator==(LayerStack::Layer_Container_Data_T base, std::string compare)
	{
		return base.first == compare;
	}
}
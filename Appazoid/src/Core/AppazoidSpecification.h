#pragma once

#include "Logging/Log.h"

//#if AZ_RENDER_API == AZ_RENDER_API_OPENGL
#include "glad/glad.h"
//#endif 
#include "PlatformDetection.h"


namespace az {
	namespace RenderAPI
	{
		enum class API
		{
			None = 0,
			OpenGL,
			Vulkan
			//DirectX
		};
	}
	#define AZ_RENDER_API_NONE	 0
	#define AZ_RENDER_API_OPENGL 1
	#define AZ_RENDER_API_VULKAN 2

	#ifndef AZ_RENDER_API
	#define AZ_RENDER_API AZ_RENDER_API_OPENGL
	#endif
	
	class AppazoidSpecification
	{
	private:
		//static AppazoidSpecification* m_inst;
	public:
		AppazoidSpecification operator=(const AppazoidSpecification&) = delete;
		AppazoidSpecification(const AppazoidSpecification&) = delete;//removes copy constructor

		static AppazoidSpecification& GetInst()
		{
			static AppazoidSpecification m_inst;
			return m_inst;
		}
		static void Print()
		{
			GetInst().m_Print();
		}
		

		//Get the type of the values in indices
		//*Its set to GL_UNSIGNED_INT by default
		static unsigned int& GetTypeOfIndices()
		{
			static unsigned int type_of_indices = GL_UNSIGNED_INT;
			return type_of_indices;
		}
		//Specifies the type of the values in indices. Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.
		//*Its set to GL_UNSIGNED_INT by default
		static void SetTypeOfIndices(const unsigned int& to)
		{
			GetTypeOfIndices() = to;
		}


		//Get the the format of the pixel data
		//*Its set to GL_RGBA by default
		static unsigned int& GetFormatOfPixelData() 
		{
			static unsigned int format_of_pixel_data = GL_RGBA;
			return format_of_pixel_data;
		}
		//Specifies the format of the pixel data. The following symbolic values are accepted: GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL. 
		//*Its set to GL_RGBA by default
		static void SetFormatOfPixelData(const unsigned int& to)
		{
			GetFormatOfPixelData() = to;
		}

		//Get the data type of the pixel data
		//*Its set to GL_UNSIGNED_BYTE by default
		static unsigned int& GetTypeOfPixelData()
		{
			static unsigned int format_of_pixel_data = GL_UNSIGNED_BYTE;
			return format_of_pixel_data;
		}
		//Specifies the data type of the pixel data. The following symbolic values are accepted: GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV.
		//*Its set to GL_UNSIGNED_BYTE by default
		static void SetTypeOfPixelData(const unsigned int& to)
		{
			GetFormatOfPixelData() = to;
		}

		static size_t GetSizeOfDataType(unsigned int type)
		{
			switch (type)
			{
			case GL_UNSIGNED_INT:
				return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE:
				return sizeof(unsigned char);
			case GL_UNSIGNED_SHORT:
				return sizeof(unsigned short);
			case GL_FLOAT:
				return sizeof(float);
			default:
				APPAZOID_CORE_ERROR("AppazoidSpecification::GetSizeOfDataType returned a 0!");
				return 0;//ERROR!
			}
		}
		static inline RenderAPI::API GetAPI() 
		{
			return (RenderAPI::API)AZ_RENDER_API;
		}

	private:
		AppazoidSpecification()
		{

		}
		void m_Print()
		{
			APPAZOID_CORE_INFO
			(	
				"Specification:\n\t\t"
				"GetTypeOfIndices()\t=\t{0}\n\t\t"
				"GetTypeOfPixelData()\t=\t{1}\n\t\t"
				"GetFormatOfPixelData()\t=\t{2}\n\t\t"
				"GetAPI()\t\t=\t{3}"
				,GetTypeOfIndices(),GetTypeOfPixelData(),GetFormatOfPixelData(),(int)GetAPI()
			);
		}
	};
	//unsigned int AppazoidSpecification::type_of_indices = GL_UNSIGNED_INT;

	//#ifndef APPAZOIDSPECIFICATION_INST_DEFINED
	//#define APPAZOIDSPECIFICATION_INST_DEFINED
	//AppazoidSpecification* AppazoidSpecification::m_inst;
	//#endif
}

//TODO: Rewrite all "Graphics/" files to use AppazoidSpecification
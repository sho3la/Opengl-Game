#pragma once
#include "Texture.h"
#include <memory>
#include "Shader.h"
namespace GXProject{
	enum DRAW_MODE{
		COLOR,TEXTURED,COLOR_TEXTURED,NONE
	};
	class Material
	{
	public:
		Material()
		{
			diffuse = nullptr;
			normal = nullptr;
			shader = nullptr;
			mode = TEXTURED;
		}

		~Material()
		{
			diffuse = nullptr;
			normal = nullptr;
			shader = nullptr;
		}

	public:
		TexturePtr diffuse;
		TexturePtr normal;
		ShaderPtr shader;
		DRAW_MODE mode;
	};
	typedef std::shared_ptr<Material> MaterialPtr;
}
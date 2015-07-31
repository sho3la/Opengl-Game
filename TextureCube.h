#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>

namespace GXProject{
	class TextureCube{
	public:
		int width, height;
		int numComponents;
		unsigned char* data;
		int texUnit;
		void bind(int tu = -1);
		TextureCube(const std::vector<std::string> fileName, int txu);
		virtual ~TextureCube();

	private:
		TextureCube(const TextureCube& txt){}
		void operator=(const TextureCube& tex){}
		GLuint m_texture;
	};

}
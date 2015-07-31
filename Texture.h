#pragma once
#include <string>
#include <gl/glew.h>
#include <memory>
namespace GXProject{
	class Texture{
	public:
		int width,height,numComponents;
		unsigned char* data;
		int texUnit;
		void bind(int unit = -1);
		Texture(const std::string& file,int tu);
		virtual ~Texture();
	private:
		Texture(const Texture& texture){}
		void operator=(const Texture& texture){}
	protected:
		GLuint _texture;
	};
	typedef std::shared_ptr<Texture> TexturePtr;
}
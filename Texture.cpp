#include "Texture.h"
#include "stb_image.h"
#include <iostream>
using namespace std;
using namespace GXProject;

Texture::Texture(const std::string& file,int tu){
	texUnit = tu;

	unsigned char* data = stbi_load((file).c_str(), &width, &height, &numComponents, 4);
	if(data == NULL)
		cout<< "Unable to load texture: " << file << endl;

	glActiveTexture(texUnit);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0); 

	stbi_image_free(data);
}

Texture::~Texture(){
	glDeleteTextures(1,&_texture);
}

void Texture::bind(int unit /* = -1 */){
	if(unit > -1)
	{
		glActiveTexture(GL_TEXTURE0+unit);
		glBindTexture(GL_TEXTURE_2D,_texture);
	}else
	{

		glActiveTexture(GL_TEXTURE0+texUnit);
		glBindTexture(GL_TEXTURE_2D,_texture);
	}
}
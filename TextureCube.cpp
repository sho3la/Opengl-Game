#include "TextureCube.h"
#include "stb_image.h"
#include <iostream>
using namespace GXProject;
using namespace std;

TextureCube::TextureCube(const vector<string> fileName, int texUnit_)
{
	texUnit = texUnit_;
	glGenTextures(1,&m_texture);
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP,m_texture);

	for(int i=0;i<fileName.size();i++){
		unsigned char* data = stbi_load((fileName[i]).c_str(), &width, &height, &numComponents, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
		if(data == NULL)
			cout<< "Unable to load texture: " << fileName[i] << endl;
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); 
}


TextureCube::~TextureCube()
{
	glDeleteTextures(1, &m_texture);
}

void TextureCube::bind(int tu /* = -1 */)
{
	if(tu==-1){
		glActiveTexture(GL_TEXTURE0+texUnit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	}else{
		glActiveTexture(GL_TEXTURE0+tu);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	}
}

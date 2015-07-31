#pragma once
#include <string>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <memory>
namespace GXProject{
	class Shader{
	public:
		Shader(std::string vertex,std::string fragment);
		~Shader();
		void bind();
		void setUniform(std::string,int);
		void setUniform(std::string,float);
		void setUniform(std::string,glm::vec2);
		void setUniform(std::string,glm::vec3);
		void setUniform(std::string,glm::vec4);
		void setUniform(std::string,glm::mat3);
		void setUniform(std::string,glm::mat4);

		unsigned int _program;
	protected:
		

	};
	typedef std::shared_ptr<Shader> ShaderPtr;
}



GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
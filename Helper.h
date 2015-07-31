#pragma once
#include "Mesh.h"
#include <string>
namespace GXProject{
	class Helper{
	public:
		static std::string getDirectory(std::string path);
		static MeshPtr loadMesh(std::string path);
	};
}
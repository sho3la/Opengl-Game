#pragma once
#include "Mesh.h"
#include "GameObject.h"

namespace GXProject
{
	class Ground : public GameObject
	{
		//std::vector<GameObjectPtr> _cubes;
		GameObjectPtr _cube;
		std::vector<glm::vec3> _offsets;
		//maze representation
		char **maze;
		int x,y;
	public:
		Ground(int _x, int _y);
		~Ground();

		bool Collide(glm::vec3 pos);
		static Ground* loadFile(std::string);

		void draw(glm::mat4 vp,int is_Instancing = -1) override;
	};
}
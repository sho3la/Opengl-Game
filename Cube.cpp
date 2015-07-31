#include "Cube.h"
#include "Geometry.h"
#include "Material.h"
using namespace std;
using namespace glm;
using namespace GXProject;

Cube::Cube(){
	float length;
	GeometryPtr g = GeometryPtr(new Geometry());
	g->pushVertex(Vertex(vec3(-1,-1,-1),vec3(1)));
	g->pushVertex(Vertex(vec3(-1,-1,1),vec3(1)));
	g->pushVertex(Vertex(vec3(-1,1,1),vec3(1)));

	g->pushVertex(Vertex(vec3(1,1,-1),vec3(1)));
	g->pushVertex(Vertex(vec3(-1,1,-1),vec3(1)));
	g->pushVertex(Vertex(vec3(1,-1,1),vec3(1)));

	g->pushVertex(Vertex(vec3(1,-1,-1),vec3(1)));
	g->pushVertex(Vertex(vec3(1,1,1),vec3(1)));

	g->pushFace(0,1,2);
	g->pushFace(3,4,0);

	g->pushFace(5,0,6);
	g->pushFace(3,0,6);

	g->pushFace(4,2,0);
	g->pushFace(5,1,0);

	g->pushFace(2,1,5);
	g->pushFace(7,6,3);

	g->pushFace(6,7,5);
	g->pushFace(7,3,4);

	g->pushFace(7,4,2);
	g->pushFace(5,2,7);

	MaterialPtr m = MaterialPtr(new Material());
	m->mode = NONE;

	_cube = GameObjectPtr(new GameObject(MeshPtr(new Mesh(g,m))));
}
Cube::~Cube(){
	_cube = nullptr;
}
void Cube::walk(glm::vec3 dir,float ama){
	_cube->position += dir*ama;
}

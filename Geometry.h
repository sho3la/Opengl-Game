#pragma once
#include <memory>
#include <vector>
#include "Vertex.h"
namespace GXProject{
	class Geometry{
	public:
		Geometry(std::vector<Vertex>& verts,std::vector<unsigned short>& indi){
			vertices = verts;
			indices = indi;
		}
		Geometry(){
		}
		~Geometry(){
			vertices.clear();
			indices.clear();
		}
		std::vector<Vertex> getVertices(){
			return vertices;
		}
		std::vector<unsigned short> getIndices(){
			return indices;
		}
		void pushVertex(Vertex v){
			vertices.push_back(v);
		}
		void pushIndex(int v){
			indices.push_back(v);
		}
		void pushFace(int a, int b, int c){
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);
		}
		int getVerticesCount(){
			return vertices.size();
		}
		int getIndicesCount(){
			return indices.size();
		}
	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned short> indices;
	};
	typedef std::shared_ptr<Geometry> GeometryPtr;
}
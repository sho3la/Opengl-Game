#ifndef vertexBufferObject_h__
#define vertexBufferObject_h__

#include "gl/glew.h"
#include <vector>
/********************************

Class:		CVertexBufferObject

Purpose:	Wraps OpenGL vertex buffer
			object.

********************************/
typedef GLuint UINT;
typedef unsigned char BYTE;
using namespace std;
class CVertexBufferObject
{
public:
	void CreateVBO(int a_iSize = 0);
	void DeleteVBO();

	void* MapBufferToMemory(int iUsageHint);
	void* MapSubBufferToMemory(int iUsageHint, UINT uiOffset, UINT uiLength);
	void UnmapBuffer();

	void BindVBO(int a_iBufferType = GL_ARRAY_BUFFER);
	void UploadDataToGPU(int iUsageHint);
	
	void AddData(void* ptrData, UINT uiDataSize);

	void* GetDataPointer();
	UINT GetBufferID();

	int GetCurrentSize();

	CVertexBufferObject();

private:
	UINT uiBuffer;
	int iSize;
	int iCurrentSize;
	int iBufferType;
	vector<BYTE> data;

	bool bDataUploaded;
};
#endif // vertexBufferObject_h__
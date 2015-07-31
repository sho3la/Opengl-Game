#pragma once
#include<memory>
#include "GameObject.h"
#include "Shader.h"
#include<GLFW/glfw3.h>
#include"EulerCamera.h"
#include <glm/glm.hpp>
#include <map>
#include <string>
#include "Skybox.h"
#include "PointLight.h"
#include "Ground.h"
#include "md2model.h"

namespace GXProject{
	class Game{
	private:
		enum Direction{SOUTH,NORTH,EAST,WEST};
		std::map<std::string, GameObjectPtr> scene;
		ShaderPtr _genericShader;
		Skybox sky;
		Ground* _ground;
		Ground* _walls;


		//
		CMD2Model mymodel;
		animState_t model_anim_state;
		KeyFrameAnimationShader animatedModelShader;

		glm::mat4 model_m;
		glm::vec3 monsterPosition;
		Direction monsterDirection;
		glm::vec3 monsterPosTarget;
		glm::vec3 monsterRotate;
		//


		PointLight playerLight, Monsterlight;
		glm::vec2 mousePosition;
		bool _turnOnMouseCamera;
		bool _debugMode;
	public:
		EulerCamera camera;
		Game();
		~Game();

		void MonsterAI();
		void setupGround(int x, int y,ShaderPtr shdr,MeshPtr msh);
		void setupShaderUniforms(ShaderPtr shdr);
		void update(double delta);
		void render();
		void cameraMouseMovement(int x, int y);
		//for handling the keyboard events
		void handleKeyboard(GLFWwindow* window,int key, int scancode,int action,int mods);
		//for handling the mouse buttons events
		void handleMouseButtons(GLFWwindow* window,int button,int action,int mods);
		//for handling mouse motion
		void handleMouseMotion(GLFWwindow* window,int x, int y);
	};
	typedef std::shared_ptr<Game> GamePtr;
}
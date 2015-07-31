#include"Game.h"
#include "Geometry.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <iostream>
#include "Helper.h"
using namespace GXProject;
using namespace std;
using namespace glm;

MeshPtr _mesh;
Game::Game(){
	auto windowpos = Application::get()->getWindowSize();
	Application::get()->setMousePosition(windowpos.x/2,windowpos.y/2);
	_turnOnMouseCamera = false;
	

	_genericShader = std::make_shared<Shader>("Model.vertexshader", "Model.fragmentshader");


	auto _skyboxShader = std::make_shared<Shader>("Skybox.vertexshader", "Skybox.fragmentshader");

	sky.setShader(_skyboxShader);

	
	//setupGround(10,10,nullptr,nullptr);
	_ground = new Ground(20,20);
	_walls = Ground::loadFile("res/defaultMaze.txt");


	playerLight.position = camera.getPosition();
	Monsterlight.intensity = 1;
	Monsterlight.color = vec3(1,0,0);
	Monsterlight.position = vec3(0,3,0);
	playerLight.intensity = 1;
	playerLight.color = vec3(1,1,1);

	monsterPosition = vec3(2.25,1.6,15.4);
	monsterPosTarget = monsterPosition;
	monsterRotate = vec3(-90,0,180);
	model_m = glm::translate(monsterPosition) * glm::rotate(-90.0f,vec3(1.0f,0.0f,0.0f)) *glm::rotate(180.0f,vec3(0.0f,0.0f,1.0f)) * glm::scale(vec3(0.025f,0.025f,0.025f));

	//load model file..
    mymodel.LoadModel("res/drfreak/drfreak.md2");

	//set curent animation to play..
	model_anim_state = mymodel.StartAnimation(animType_t::CROUCH_WALK);

	//load animation shader.
	animatedModelShader.LoadProgram();

	_debugMode = false;
	//camera.Reset(vec3(0),vec3(-0.2,4.8,15.6),vec3(0,1,0));
	camera.setPosition(vec3(0.5,1.76,0.5));
}

Game::~Game(){
	delete _ground;
	delete _walls;
}
//here for test purposes
void Game::setupGround(int x, int y, ShaderPtr shdr, MeshPtr msh)
{
	auto meshTest = Helper::loadMesh("res/cube/cube.obj");
	auto _genericShader = std::make_shared<Shader>("Model.vertexshader", "Model.fragmentshader");
	meshTest->setShader(_genericShader);
	string id = "ground_";
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			auto c = std::make_shared<GameObject>(meshTest);
			c->position.x = i;
			c->position.z = j;
			c->scale = glm::vec3(0.5);
			scene[id+std::to_string(i)+"_"+std::to_string(j)]=c;
		}
	}
}

void Game::setupShaderUniforms(ShaderPtr shdr)
{
		shdr->setUniform("TxSampler",0);
		shdr->setUniform("NrmSampler",1);

		shdr->setUniform("ViewMatrix",camera.getViewMatrix());
		//do the lights here
		shdr->setUniform("eyePos",camera.getPosition());

		shdr->setUniform("playerLightPosition",playerLight.position);
		shdr->setUniform("playerLightColor",playerLight.color);
		shdr->setUniform("playerLightIntensity",playerLight.intensity);

		shdr->setUniform("monsterLightPosition",Monsterlight.position);
		shdr->setUniform("monsterLightColor",Monsterlight.color);
		shdr->setUniform("monsterLightIntensity",Monsterlight.intensity);

}

void Game::update(double delta){
	//cout<<"update"<<endl;
	cameraMouseMovement(0,0);
	//moving the light with the camera.

	Monsterlight.position = monsterPosition;
	playerLight.position = camera.getPosition();
	cout<<playerLight.position.x<<" | "<<playerLight.position.y<<" | "<< playerLight.position.z<<endl;
	//cout<<_walls->Collide(playerLight.position)<<endl;


	mymodel.UpdateAnimation(&model_anim_state,delta / 1000);
	MonsterAI();
	auto mmx = glm::rotate(monsterRotate.x,vec3(1,0,0));
	auto mmy = glm::rotate(monsterRotate.y,vec3(0,1,0));
	auto mmz = glm::rotate(monsterRotate.z,vec3(0,0,1));
	auto mmr = mmx*mmy*mmz;
	model_m = glm::translate(monsterPosition) * mmr * glm::scale(vec3(0.025f,0.025f,0.025f));
}

void Game::render(){
	//cout<<"render"<<endl;
	glm::mat4 VP = camera.getProjectionMatrix()*camera.getViewMatrix();
	sky.draw(VP);
	for (auto obj : scene){
		auto objShader = obj.second->mesh->getMaterial()->shader;
		objShader->bind();
		objShader->setUniform("TxSampler",0);
		objShader->setUniform("NrmSampler",1);

		objShader->setUniform("ViewMatrix",camera.getViewMatrix());
		//do the lights here
		objShader->setUniform("eyePos",camera.getPosition());

		objShader->setUniform("playerLightPosition",playerLight.position);
		objShader->setUniform("playerLightColor",playerLight.color);
		objShader->setUniform("playerLightIntensity",playerLight.intensity);

		objShader->setUniform("monsterLightPosition",Monsterlight.position);
		objShader->setUniform("monsterLightColor",Monsterlight.color);
		objShader->setUniform("monsterLightIntensity",Monsterlight.intensity);

		//probably we can do it once for all objects but who cares it's a college project anyway.
		//end of the lights
		obj.second->draw(VP);
	}
	_ground->draw(VP);
	_walls->draw(VP);


	//
		animatedModelShader.UseProgram();
	animatedModelShader.BindVPMatrix(&VP[0][0]); //need vp matrix to render model in..

	animatedModelShader.BindModelMatrix(&model_m[0][0]); //need model matrix itself..

	mymodel.RenderModel(&model_anim_state,&animatedModelShader);



}
void Game::MonsterAI(){
	int rnd = rand()%4;
	vec3 bpos = monsterPosition;
	if(monsterPosTarget == monsterPosition){
		if(rnd == 1){
			monsterPosTarget.x += 1;
			monsterDirection = Direction::NORTH;
			monsterRotate.z = 0;
		}else if(rnd==2){
			monsterPosTarget.x -= 1;
			monsterDirection = Direction::SOUTH;
			monsterRotate.z = 180;
		}else if(rnd==3){
			monsterPosTarget.z += 1;
			monsterDirection = Direction::EAST;
			monsterRotate.z = 270;
		}else if(rnd==0){
			monsterPosTarget.z -= 1;
			monsterDirection = Direction::WEST;
			monsterRotate.z = 90;
		}
		if(_walls->Collide(monsterPosTarget))
			monsterPosTarget = monsterPosition;
		//bpos = monsterPosTarget;
	}else{
		if(monsterDirection == Direction::NORTH){
			bpos.x += 0.05;
		}else if(monsterDirection == Direction::SOUTH){
			bpos.x -= 0.05;
		}else if(monsterDirection == Direction::EAST){
			bpos.z += 0.05;
		}else if(monsterDirection == Direction::WEST){
			bpos.z -= 0.05;
		}
	}

	monsterPosition = bpos;
	if(_walls->Collide(bpos)){
		monsterPosTarget = monsterPosition;

		if(monsterDirection == Direction::NORTH){
			monsterPosTarget.x -= 0.5;
		}else if(monsterDirection == Direction::SOUTH){
			monsterPosTarget.x += 0.5;
		}else if(monsterDirection == Direction::EAST){
			monsterPosTarget.z -= 0.5;
		}else if(monsterDirection == Direction::WEST){
			monsterPosTarget.z += 0.5;
		}
		monsterPosition = monsterPosTarget;
	}else{
		
	}

	//cout<<"Direction = "<<monsterDirection<<endl;
}
void Game::handleKeyboard(GLFWwindow* window,int key, int scancode,int action,int mods){
	//std::cout<<"Key Event"<<std::endl;
	vec3 bpos;
	switch (key)
	{
	case GLFW_KEY_W:
		bpos = camera.getPosition();
		camera.Walk(0.1);
		if(_walls->Collide(camera.getPosition())&& !_debugMode)
			camera.Walk(-0.1);
		break;
	case GLFW_KEY_S:
		bpos = camera.getPosition();
		camera.Walk(-0.1);
		if(_walls->Collide(camera.getPosition()) && !_debugMode)
			camera.Walk(0.1);
		break;
	case GLFW_KEY_A:
		bpos = camera.getPosition();
		camera.Strafe(-0.1);
		if(_walls->Collide(camera.getPosition())&& !_debugMode)
			camera.Strafe(0.1);
		break;
	case GLFW_KEY_D:
		bpos = camera.getPosition();
		camera.Strafe(0.1);
		if(_walls->Collide(camera.getPosition())&& !_debugMode)
			camera.Strafe(-0.1);
		break;
	case GLFW_KEY_ESCAPE:
		Application::get()->shutdown();
		break;
	case GLFW_KEY_UP:
		Monsterlight.position.y++;
		break;
	case GLFW_KEY_DOWN:
		Monsterlight.position.y--;
		break;
	case GLFW_KEY_HOME:
		if(action == GLFW_PRESS)
			_debugMode = !_debugMode;
		break;
	}
	if(!_debugMode){
		auto y = camera.getPosition();
		y.y = 1.76;
		camera.setPosition(y);
	}
	camera.updateViewMatrix();
	
}

void Game::handleMouseButtons(GLFWwindow* window,int button,int action,int mods){
	//std::cout<<"mouse button Event"<<std::endl;
}

void Game::handleMouseMotion(GLFWwindow* window,int x, int y){
	mousePosition = vec2(x,y);
}

void Game::cameraMouseMovement(int x, int y){
	auto windowSize = Application::get()->getWindowSize();
	if (mousePosition.x != windowSize.x/2
		|| mousePosition.y != windowSize.y/2)
	{
		//cout<<"MOUSE MOVED"<<endl;
		double mouseSpeed = 0.005; //it is just there to speed up or slow down the movements.
		double movedDistanceX;
		double movedDistanceY;

		//  the distance (old position - new position)
		// in other words:  how far is the mouse from the center of the window ? The bigger this value, the more we want to turn.
		// note that the old position (x_old, y_old) is fixed in this application (x_old = WindoSizeWidth/2, y_old = WindowSizeHeight/2)
		movedDistanceX = double(windowSize.x/2 - mousePosition.x)*mouseSpeed;
		movedDistanceY = double(windowSize.y/2 - mousePosition.y)*mouseSpeed;

		// Pass the two distances to the Renderer (our drawings)
		
			camera.Yaw(movedDistanceX);
			camera.Pitch(movedDistanceY);
			camera.updateViewMatrix();
		

		//Force the new position of the mouse to be in the middle of the window
		mousePosition.x = windowSize.x/2;
		mousePosition.y = windowSize.y/2;
		Application::get()->setMousePosition(mousePosition.x,mousePosition.y);
	}
}

#include "Application.h"
#include <exception>
#include <iostream>
using namespace GXProject;
using namespace std;

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"assimp.lib")

ApplicationPtr Application::_instance = nullptr;

Application::Application(int GLMAJOR /* = 2 */, int GLMINOR /* = 1 */){
	_versionMajor = GLMAJOR;
	_versionMinor = GLMINOR;
	_time = 0;
	_shutdown = false;
}
Application::~Application(){
	if(_window)
		glfwDestroyWindow(_window);

	glfwTerminate();
}

ApplicationPtr Application::get(int GLMajor,int GLMinor){
	if(_instance == nullptr){
		_instance = ApplicationPtr(new Application(GLMajor,GLMinor));
	}
	return _instance;
}

GamePtr Application::getGame(){
	return Application::get()->_game;
}

glm::vec2 Application::getMousePosition(){
	return _mousePos;
}

void Application::setMousePosition(float x, float y){
	glfwSetCursorPos(_window,x,y);
	_mousePos = glm::vec2(x,y);
}

bool Application::init(unsigned int width /* = 800 */, unsigned int height /* = 600 */, std::string title /* = "Window" */){
	_width = width;
	_height = height;
	_title = title;
	try{
		initWindow();
		return true;
	}catch(exception e){
		cerr<<e.what()<<endl;
		return false;
	}
}

void Application::initWindow(){
	if(!glfwInit())
		throw exception("Cannot initialise GLFW");

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _versionMajor); //OpenGL version 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _versionMinor); // 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE); //If requesting an OpenGL version below 3.2, GLFW_OPENGL_ANY_PROFILE

	_window = glfwCreateWindow(_width,_height,_title.c_str(),NULL,NULL);
	if(_window == nullptr)
		throw exception("Cannot create GLFW Window");

	glfwMakeContextCurrent(_window);

	if(glewInit() != GLEW_OK)
		throw exception("Cannot initialise GLEW");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Application::start(GamePtr game){
	_game = game;
	glfwSetWindowSizeCallback(_window,&Application::windowResized);
	glfwSetKeyCallback(_window,&Application::KeyboardKeys);
	glfwSetMouseButtonCallback(_window,&Application::MouseButtons);
	glfwSetCursorPosCallback(_window,&Application::mouseMotion);
	startLoop();
}
void Application::startLoop(){
	while(!glfwWindowShouldClose(_window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update();
		render();
		glfwSwapBuffers(_window);
		glfwPollEvents();
		//if shutdown then break the loop
		if(_shutdown)
			break;
	}
}

void Application::windowResized(GLFWwindow* window, int width, int height){
	ApplicationPtr app = Application::get();
	app->_width = width;
	app->_height = height;
	glViewport(0,0,width,height);
}

void Application::KeyboardKeys(GLFWwindow* window,int key, int scancode,int action,int mods){
	_instance->_game->handleKeyboard(window,key,scancode,action,mods);
}
void Application::MouseButtons(GLFWwindow* window,int button,int action,int mods){
	_instance->_game->handleMouseButtons(window,button,action,mods);
}
void Application::mouseMotion(GLFWwindow* window,double x, double y){
	_instance->_game->handleMouseMotion(window,x,y);
}

void Application::update(){
	double currentTime = glfwGetTime();
	double deltaTime = (currentTime - _time)*1000;
	_time = currentTime;

	_game->update(deltaTime);
}

void Application::render(){
	_game->render();
}

glm::vec2 Application::getWindowSize(){
	return glm::vec2(_width,_height);
}

void Application::shutdown(){
	_shutdown = true;
}
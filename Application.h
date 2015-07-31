#pragma once
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Game.h"
#include <glm/glm.hpp>
namespace GXProject{
	class Application{
	private:
		//opengl version to use
		int _versionMajor,_versionMinor;
		//pointer to window handle
		GLFWwindow* _window;
		//window properties
		unsigned int _width, _height;
		std::string _title;
		//game that the application will run
		GamePtr _game;
		//time 
		double _time;
		//the only extisting instance of the application
		static std::shared_ptr<Application> _instance;
		//mouse position vector 2
		glm::vec2 _mousePos;
		//boolean for shutdown
		bool _shutdown;
		/*!
		 * \function bool initWindow()
		 *
		 * \brief initialises the GLFW window with the right context
		 *
		 * \author Moustapha Saad
		 */
		void initWindow();
		/*!
		 * \function void start()
		 *
		 * \brief starts the window loop
		 *
		 * \author Moustapha Saad
		 */
		void startLoop();

		void update();
		void render();
		/*!
		 * \function void windowResized(GLFWwindow*,int,int)
		 *
		 * \brief adjusting the viewport when the window changes in size
		 *
		 * \author Moustapha Saad
		 */
		static void windowResized(GLFWwindow* window, int width, int height);
		//static function to handle the mouse motion callback
		static void mouseMotion(GLFWwindow* window,double x, double y);
		//for handling the keyboard events
		static void KeyboardKeys(GLFWwindow* window,int key, int scancode,int action,int mods);
		//for handling the mouse buttons events
		static void MouseButtons(GLFWwindow* window,int button,int action,int mods);
		//constructor with the default values
		Application(int GLMAJOR = 2, int GLMINOR = 1);
	public:
		static std::shared_ptr<Application> get(int GLMajor=2,int GLMinor = 1);
		//returns a pointer to the game instance
		static GamePtr getGame();
		//mouse position getter
		glm::vec2 getMousePosition();
		//mouse position setter
		void setMousePosition(float x, float y);
		//destructor
		~Application();

		/*!
		 * \function void init(uint,uint,string)
		 *
		 * \brief signals the init process 
		 *
		 * \author Moustapha Saad
		 */
		bool init(unsigned int width = 800, unsigned int height = 600, std::string title = "Window");
		/*!
		 * \function void start()
		 *
		 * \brief signals the start function
		 *
		 * \author Moustapha Saad
		 */
		void start(GamePtr game);
		//returns window dimension
		glm::vec2 getWindowSize();
		//handle shutdown
		void shutdown();
	};
	typedef std::shared_ptr<Application> ApplicationPtr;
}
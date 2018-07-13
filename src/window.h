#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "input.h"

namespace engine {

	class Window {

	private:
		GLFWwindow* m_window;
		int m_width, m_height;
		const char* m_title;

		static const char* m_droppedPath;

		bool init();

	public:
		Window(int width, int height, const char* title);
		~Window();
		
		void update();

		bool isOpen() const;

		int getWidth();
		int getHeight();

		float getAspectRatio();

		GLFWwindow* getWindow() const;

		void setMinVersion(GLuint major, GLuint minor);
		void setWindowSize(int width, int height);
		void clearDroppedPath();

		const char* getDroppedPath();
		
		static void handleDroppedFile(const char* path);
	};
}
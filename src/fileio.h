#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>

#include "stb/stb_image.h"

namespace engine {
	namespace File {

		static GLuint loadImage(std::string path, int* width, int* height) {
			int n;
			unsigned char* data = stbi_load(path.c_str(), width, height, &n, 0);

			GLuint textureID;
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);

			GLuint type = GL_RGBA;

			switch (n) {
				case 1:
					type = GL_RED;
					break;
				case 2:
					type = GL_RG;
					break;
				case 3:
					type = GL_RGB;
					break;
			}

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, type, *width, *height, 0, type, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			return textureID;
		}

		static std::string loadFileToString(const char* path) {
			std::string line, content = "";
			std::ifstream file(path);

			if (file.is_open()) {
				while (std::getline(file, line))
					content += line + "\n";
			}

			file.close();

			return content;
		}

		static void appendToFile(const char* path, const char* str) {
			std::ofstream file(path, std::ios_base::app);

			if (file.is_open())
				file << str;

			file.close();
		}

		static void clearFile(const char* path) {
			std::ofstream file(path, std::ofstream::out | std::ofstream::trunc);
			file.close();
		}
	}
}

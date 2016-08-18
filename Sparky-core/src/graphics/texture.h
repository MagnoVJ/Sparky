#pragma once

#include "../utils/imageload.h"

#include <FreeImage.h>
#include <GL\glew.h>
#include <string>

namespace sparky{

	namespace graphics{

		class Texture{

		//Attributes
		private:
			std::string m_Filename;
			GLuint m_TextureID;
			GLsizei m_Width, m_Height;

		//Methods
		private:
			GLuint load();

		public:
			Texture(const std::string& filename);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const GLuint getTextureID() const {return m_TextureID;}  
			inline const GLuint getWidth() const {return m_Width;}
			inline const GLuint getHeight() const {return m_Height;}

		};

	}

}
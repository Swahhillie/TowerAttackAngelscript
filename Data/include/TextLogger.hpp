#ifndef TEXTLOGGER_H
#define TEXTLOGGER_H

#include "Component.hpp"
#include <sfml/graphics.hpp>
#include <sfml/window.hpp>
#include <iostream>
#include "Transform.hpp"
#include <fstream>
#include <glm/glm.hpp>

class TextLogger
{
	public:
		static TextLogger & instance(){
			static TextLogger INSTANCE;
			return INSTANCE;
		}
		virtual ~TextLogger();

		void addToLog(std::string );
		void addToLog(glm::vec3);
	protected:
	private:
		TextLogger();
		std::ofstream checkpointPositions;

};

#endif // TEXTLOGGER_H

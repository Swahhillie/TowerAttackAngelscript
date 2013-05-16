#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "Component.hpp"
#include <vector>
class Texture;

class Skybox : public Component
{
	public:
		enum Side{
			UP = 0,
			DOWN = 1,
			LEFT = 2,
			RIGHT = 3,
			BACK = 4,
			FORWARD = 5
		};

		Skybox();
		virtual ~Skybox();
		Skybox(const Skybox& other);
		Skybox& operator=(const Skybox& other);

		void draw();
		void setTexture(Skybox::Side side, Texture * tex);
		const static int SIDECOUNT = 6;


		std::vector<Texture*> textures;

	protected:
	private:
		std::vector<bool> sidesSet;
		bool checkComplete();

};

#endif // SKYBOX_HPP

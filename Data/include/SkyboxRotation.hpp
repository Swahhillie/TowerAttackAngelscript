#ifndef SKYBOXROTATION_H
#define SKYBOXROTATION_H

#include "Component.hpp"
#include "Transform.hpp"
#include "Time.hpp"


class SkyboxRotation : public Component
{
	public:
		SkyboxRotation(Transform * tr);
		virtual ~SkyboxRotation();
		void update();
		virtual const std::string getName(){return "SkyboxRotation";}
	protected:
	private:
		Transform *  tr;
};

#endif // SKYBOXROTATION_H

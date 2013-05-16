#ifndef DEFENDER_H
#define DEFENDER_H

#include "Component.hpp"
#include "Destructable.hpp"


class Defender : public Component, public Destructable
{
	public:
		Defender();
		virtual ~Defender();

		bool powered;
		bool requirePower;
		enum DefenderType{
            Turret,
            Powernode,
            Lasergrid
		};
		virtual DefenderType getDefenderType()const = 0;
		virtual const std::string getName(){return "Defender";}

	protected:
		virtual void onDestroy();
		virtual void onConnect();
		virtual void initializeHealth(float mh);
	private:
};

#endif // DEFENDER_H

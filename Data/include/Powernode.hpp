#ifndef POWERNODE_HPP
#define POWERNODE_HPP

#include "Defender.hpp"
#include <vector>

class Powernode : public Defender
{
	public:
		enum PowernodeType{
			Turret,
			Laser,
			Main
		};


		explicit Powernode(PowernodeType type);
		virtual ~Powernode();


		virtual const std::string getName(){return "Powernode";}
        virtual DefenderType getDefenderType()const;

        float getPowerRange(){return powerRange;}

        PowernodeType powernodeType;

    protected:
        virtual void onDestroy();

	private:

        float powerRange;
};

#endif // POWERNODE_HPP

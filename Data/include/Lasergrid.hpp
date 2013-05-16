#ifndef LASERGRID_H
#define LASERGRID_H

#include "Defender.hpp"


class Lasergrid : public Defender
{
    public:
        Lasergrid();
        virtual ~Lasergrid();

        virtual void update();
        virtual const std::string getName(){return "Lasergrid";}
        virtual Defender::DefenderType getDefenderType()const;



    protected:
    private:
        bool initialized;
        bool lastState;
        void onPowerUp();
        void onPowerDown();
};

#endif // LASERGRID_H

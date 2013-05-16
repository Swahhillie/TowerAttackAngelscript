#ifndef DESTRUCTABLE_H
#define DESTRUCTABLE_H

#include <string>

class Destructable
{
	public:
		Destructable();
		virtual ~Destructable();

		float getCurrentHealth()const;
		float getMaxHealth()const;
		void setMaxHealth(float amount);
		void setCurrentHealth(float amount);
		void changeHealth(float amount);

		float getHealthPercentRemaining()const;
		std::string getHealthRepresentation()const;

        bool attackable;
	protected:
		virtual void onDestroy() =0;
		virtual void initializeHealth(float mh) = 0;

	private:

		float maxHealth;
		float currentHealth;

};

#endif // DESTRUCTABLE_H

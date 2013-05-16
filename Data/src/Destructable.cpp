#include "Destructable.hpp"
#include <iostream>
#include <sstream>
#include <assert.h>

Destructable::Destructable():attackable(true),maxHealth(0), currentHealth(0)
{
	//ctor

}

Destructable::~Destructable()
{

}
void Destructable::changeHealth(float amount){
	assert(currentHealth + amount < maxHealth);
	currentHealth += amount;
	if(currentHealth <= 0){
		onDestroy();
	}
}
void Destructable::setCurrentHealth(float amount){
	assert(amount <= maxHealth && amount > 0); //cannot change to below 0;

	currentHealth = amount;
}
void Destructable::setMaxHealth(float amount){


	maxHealth = amount;
	currentHealth = maxHealth < currentHealth? maxHealth : currentHealth;
	assert(maxHealth > 0);
}
float Destructable::getHealthPercentRemaining()const{
	return currentHealth / maxHealth;
}
float Destructable::getCurrentHealth()const{
	return currentHealth;
}
float Destructable::getMaxHealth()const{
	return maxHealth;
}
std::string Destructable::getHealthRepresentation()const{
    std::stringstream ss;
    ss << (int)currentHealth << "/" << (int)getMaxHealth();
    return ss.str();
}
//void Destructable::onDestroy(){
//	std::cout << "default destroy code. need to be overwritten for an actual destruction to takes place" << std::endl;
//}

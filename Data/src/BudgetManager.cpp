#include "BudgetManager.hpp"

#include <iostream>
#include <sstream>

BudgetManager::BudgetManager():budget_(0), money_(0)
{
    //ctor
}

BudgetManager::~BudgetManager()
{
    //dtor
}
bool BudgetManager::useMoney(int amount){
    std::cout << "tried using " << amount << " money, available money = " << money_ << std::endl;
    if(money_ >= amount){
        money_ -= amount;
        return true;
    }
    else{
        return false;
    }
}

void BudgetManager::setBudget(int amount){
    std::cout << "budget set to " << amount << std::endl;
    budget_ = amount;
    money_ = amount;
}
int BudgetManager::getBudget()const{
    return budget_;
}

int BudgetManager::getMoney()const{
    return money_;
}
std::string BudgetManager::getMoneyString()const{

	std::stringstream sstream;
	sstream <<"$ " << money_ << " / " << budget_;
	return sstream.str();
}

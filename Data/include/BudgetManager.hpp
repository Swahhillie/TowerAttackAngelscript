#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <string>

class BudgetManager
{
    public:
        static BudgetManager & instance(){
            static BudgetManager budgetManager;
            return budgetManager;
        }

        virtual ~BudgetManager();

        bool useMoney(int amount);

        void setBudget(int amount);
        int getBudget()const;

        int getMoney()const;

        std::string getMoneyString()const;

    protected:
    private:
        BudgetManager();
        int budget_;
        int money_;

};

#endif // BUDGETMANAGER_H

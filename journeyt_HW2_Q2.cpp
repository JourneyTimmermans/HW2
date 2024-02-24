#include <iostream>
#include <cstdlib>
using namespace std;

/*************************************************************************
** Author : Journey Timmermans
** Program : hw2, q2
** Date Created : February 22, 2024
** Date Last Modified : February 23, 2024
** Usage : No command line arguments
**
** Problem:
Write a program based on HW2 that allows for a checks to be written
*************************************************************************/


// Defining Structure for a check
struct Check : public error_code {
    int CheckNum;
    string CheckMemo;
    float CheckAmount;

    //Compares CheckAmount to a float
    bool operator>(float amount) const {
        return CheckAmount > amount;
    }
};

class CheckBook {
public:
    //Constructors
    CheckBook(): balance(0), lastDeposit(0), numOfChecks(0), checkBookSize(4), chkPtr(new Check[4]) {}
    CheckBook(float initialBalance) : balance(initialBalance), numOfChecks(0), checkBookSize(2) {
        chkPtr = new Check[checkBookSize];
    }

    //Destructor
    ~CheckBook() {
        delete[] chkPtr;
    }

    //Copy constructor
    CheckBook(const CheckBook& other) {
        balance = other.balance;
        lastDeposit = other.lastDeposit;
        numOfChecks = other.numOfChecks;
        checkBookSize = other.checkBookSize;
        chkPtr = new Check[checkBookSize];
        for (int i=0; i < numOfChecks; ++i) {
            chkPtr[i] = other.chkPtr[i];
        }
    }

    //Overloaded = operator
    CheckBook& operator =(const CheckBook& other) {
        if (this != &other) {
            delete[] chkPtr;
            balance = other.balance;
            lastDeposit = other.lastDeposit;
            numOfChecks = other.numOfChecks;
            checkBookSize = other.checkBookSize;
            chkPtr = new Check[checkBookSize];
            for (int i = 0; i < numOfChecks; ++i) {
                chkPtr[i] = other.chkPtr[i];
            }
        }

    }

    //Depositing money
    void deposit(float amount) {
        balance += amount;
        lastDeposit = amount;
    }

    //Writing a check
    bool writeCheck(Check c_amount) {
        if (c_amount > balance) {
            return false;
        }
        cout << "Enter memo for this check: ";
        string memo[] = {"wedding", "baby shower", "pizza", "children hospital", "barber shop", "plumber", "hobbit", "trudo"};
        int memoIndex = rand() % (sizeof(memo) / sizeof(memo[0]));
        c_amount.CheckMemo = memo[memoIndex];
        c_amount.CheckNum = ++numOfChecks;
        chkPtr[numOfChecks - 1] = c_amount;
        balance -= c_amount.CheckAmount;

        if (numOfChecks >= checkBookSize / 2) {
            checkBookSize *= 2;
            cout << "Warning: New check book has been ordered. Check book size doubled to " << checkBookSize << endl;
        }
        return true;
    }

    //Getter functions
    float getBalance() const {return balance;}
    float getLastDeposit() const {return lastDeposit;}
    int getNumOfChecks() const {return numOfChecks;}
    int getCheckBookSize() const {return checkBookSize;}

    //Setter functions
    void setBalance(float newBalance) {balance = newBalance;}
    void setLastDeposit(float newLastDeposit) {lastDeposit = newLastDeposit;}
    void setNumOfChecks(int newNumOfChecks) {numOfChecks = newNumOfChecks;}
    void setCheckBookSize(int newCheckBookSize) {checkBookSize = newCheckBookSize;}

    //Function to display all checks
    void displayChecks() const {
        for (int i = numOfChecks - 1; i >= 0; --i) {
            cout << chkPtr[i] << endl;}
    }

private:
    //Variable dictionary
    float balance;
    Check* chkPtr;
    float lastDeposit;
    int numOfChecks;
    int checkBookSize;
};

void checkTest (CheckBook& checkBook, float balance) {
    while (checkBook.getBalance() > 0) {
        float amount = rand() % 100 + 1;
        Check check;
        check.CheckAmount = amount;
        checkBook.writeCheck(check);
    }
    checkBook.displayChecks();
}

int main() {
    CheckBook checkBook(1000);
    checkTest(checkBook, 1000);
    return 0;
}

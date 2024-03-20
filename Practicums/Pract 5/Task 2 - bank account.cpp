#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t HOLDER_NAME_LENGTH = 50;
constexpr size_t IBAN_LENGTH = 34;
constexpr size_t BANK_NAME_LENGTH = 20;
constexpr size_t MAX_ACCOUNTS_COUNT = 1000;
struct BankAccount
{
private:
	char holderName[HOLDER_NAME_LENGTH + 1];
	char iban[IBAN_LENGTH + 1];
	bool isLocked;
	float balance;
	float savingsBalance;
	bool deposit(float amount, float& dest)
	{
		if (amount <= 0)
		{
			return false;
		}

		dest += amount;
		return true;
	}
	bool withdraw(float amount, float& src)
	{
		if (this->isLocked || amount <= 0 || src - amount < 0)
		{
			return false;
		}

		src -= amount;
		return true;
	}
	void init()
	{
		this->close();
		this->unlock();
	}
public:
	BankAccount()
	{
		this->init();
	}
	BankAccount(const char* holderName, const char* iban, float balance, float savingsBalance) : BankAccount()
	{
		this->setHolderName(holderName);
		this->setIBAN(iban);
		this->deposit(balance);
		this->depositSavings(savingsBalance);
	}
	const char* getHolderName() const
	{
		return this->holderName;
	}
	void setHolderName(const char* value)
	{
		if (!value)
		{
			return;
		}

		if (strlen(value) > HOLDER_NAME_LENGTH)
		{
			return;
		}
		strcpy(this->holderName, value);
	}
	const char* getIBAN() const
	{
		return this->iban;
	}
	void setIBAN(const char* value)
	{
		if (!value)
		{
			return;
		}

		if (strlen(value) > IBAN_LENGTH)
		{
			return;
		}
		strcpy(this->iban, value);
	}
	float getBalance() const
	{
		return this->balance;
	}
	bool deposit(float amount)
	{
		return deposit(amount, this->balance);
	}
	bool withdraw(float amount)
	{
		return withdraw(amount, this->balance);
	}
	float getSavingsBalance() const
	{
		return this->savingsBalance;
	}
	bool depositSavings(float amount)
	{
		return deposit(amount, this->savingsBalance);
	}
	bool withdrawSavings(float amount)
	{
		return withdraw(amount, this->savingsBalance);
	}
	float getIsLocked() const
	{
		return this->isLocked;
	}
	void lock()
	{
		this->isLocked = true;
	}
	void unlock()
	{
		this->isLocked = false;
	}
	void close()
	{
		strcpy(this->holderName, "");
		strcpy(this->iban, "");
		this->balance = 0;
		this->savingsBalance = 0;
		this->lock();
	}
	void print() const
	{
		std::cout << this->holderName << ", " << this->iban << ": " << "Balance: " << this->balance << ", Savings balance: " << this->savingsBalance << ", Is account locked: " << std::boolalpha << this->isLocked << std::endl;
	}
};
struct Bank
{
private:
	char name[BANK_NAME_LENGTH + 1];
	BankAccount accounts[MAX_ACCOUNTS_COUNT];
	size_t accountsCount;
	int indexofByIban(const char* iban) const
	{
		if (!iban)
		{
			return -1;
		}

		for (size_t i = 0; i < this->accountsCount; i++)
		{
			if (strcmp(iban, this->accounts[i].getIBAN()) == 0)
			{
				return i;
			}
		}
		return -1;
	}
	bool containsByIban(const char* iban)
	{
		return iban && indexofByIban(iban) != -1;
	}
public:
	Bank() : name(""), accountsCount(0)
	{

	}
	Bank(const char* name, const BankAccount* accounts, size_t size) : Bank()
	{
		if (!accounts)
		{
			return;
		}

		this->setName(name);

		for (size_t i = 0; i < size; i++)
		{
			this->addBankAccount(accounts[i]);
		}
	}
	void setName(const char* name)
	{
		if (!name)
		{
			return;
		}

		if (strlen(name) > BANK_NAME_LENGTH)
		{
			return;
		}
		strcpy(this->name, name);
	}
	bool addBankAccount(const BankAccount& account)
	{
		if (containsByIban(account.getIBAN()))
		{
			return false;
		}
		this->accounts[this->accountsCount++] = account;
		return true;
	}
	bool removeBankAccountByIBAN(const char* iban)
	{
		int index = indexofByIban(iban);
		if (index == -1)
		{
			return false;
		}

		for (size_t i = index; i < this->accountsCount - 1; i++)
		{
			this->accounts[i] = this->accounts[i + 1];
		}
		this->accounts[--this->accountsCount].close();
		return true;
	}
	float getTotalDeposits() const
	{
		float sum = 0;
		for (size_t i = 0; i < this->accountsCount; i++)
		{
			sum += this->accounts[i].getBalance() + this->accounts[i].getSavingsBalance();
		}
		return sum;
	}
	bool sendFunds(const char* senderIBAN, const char* receiverIBAN, float amount)
	{
		if (!senderIBAN || !receiverIBAN || amount < 0)
		{
			return false;
		}
		int senderIndex = this->indexofByIban(senderIBAN);
		int receiverIndex = this->indexofByIban(receiverIBAN);
		if (senderIndex == -1 || receiverIndex == -1)
		{
			return false;
		}

		if (this->accounts[senderIndex].getIsLocked() || this->accounts[senderIndex].getBalance() - amount < 0)
		{
			return false;
		}

		return this->accounts[senderIndex].withdraw(amount) && this->accounts[receiverIndex].deposit(amount);
	}
	void lockAccountByIBAN(const char* iban)
	{
		int index = indexofByIban(iban);
		if (index == -1)
		{
			return;
		}

		this->accounts[index].lock();
	}
	void unlockAccountByIBAN(const char* iban)
	{
		int index = indexofByIban(iban);
		if (index == -1)
		{
			return;
		}

		this->accounts[index].unlock();
	}
	void print() const
	{
		std::cout << this->name << ": " << this->accountsCount << std::endl;
		for (size_t i = 0; i < this->accountsCount; i++)
		{
			this->accounts[i].print();
		}
	}
};
int main()
{
	BankAccount accounts[3] = { {"Ivan", "LC14BOSL123456789012345678901234", 100, 200}, {"Petur", "SC74MCBL01031234567890123456USD", 1000, 132}, {"Yordan", "JO71CBJO0000000000001234567890", 2000, 543} };
	Bank bank("DSK", accounts, 3);
	bank.print();
	std::cout << std::endl << std::endl;

	std::cout << bank.getTotalDeposits() << std::endl;
	bank.addBankAccount({ "Georgi", "LC14BOSL123456789012345678901234", 100, 200 }); //won't add
	bank.addBankAccount({ "Georgi ", "SV43ACAT00000000000000123123", 123123, 4334 }); //will add
	bank.print();
	std::cout << std::endl << std::endl;
	std::cout << bank.getTotalDeposits() << std::endl;

	bank.removeBankAccountByIBAN("asdasdas"); //won't remove
	bank.removeBankAccountByIBAN("SV43ACAT00000000000000123123"); //will remove
	bank.print();
	std::cout << std::endl << std::endl;
	std::cout << bank.getTotalDeposits() << std::endl;

	bank.sendFunds("LC14BOSL123456789012345678901234", "SC74MCBL01031234567890123456USD", 10); //will send
	bank.print();
	std::cout << std::endl << std::endl;
	bank.lockAccountByIBAN("LC14BOSL123456789012345678901234");
	bank.sendFunds("LC14BOSL123456789012345678901234", "SC74MCBL01031234567890123456USD", 10); //won't send: sender is locked
	bank.print();
}
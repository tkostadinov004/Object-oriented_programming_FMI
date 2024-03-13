#include <iostream>
using namespace std;
constexpr size_t CURRENCY_LENGTH = 4;

enum class StatusCode
{
	OK,
	NotEnoughFunds,
	InvalidCurrency
};
enum class AccountType
{
	Checking,
	Collection,
	Deposit
};
struct BankAccount
{
	double balance;
	int id;
	AccountType accountType;
	char currency[CURRENCY_LENGTH];
};

StatusCode deposit(BankAccount& account, double amount)
{
	account.balance += amount;
	return StatusCode::OK;
}
StatusCode withdraw(BankAccount& account, double amount)
{
	if (account.balance < amount)
	{
		return StatusCode::NotEnoughFunds;
	}

	account.balance -= amount;
	return StatusCode::OK;
}
StatusCode changeCurrency(BankAccount& account, const char* currency)
{
	if (!currency || !(*currency) || strlen(currency) >= CURRENCY_LENGTH)
	{
		return StatusCode::InvalidCurrency;
	}
	strcpy_s(account.currency, currency);

	return StatusCode::OK;
}

void handleStatus(StatusCode code)
{
	switch (code)
	{
		case StatusCode::NotEnoughFunds:
			cout << "Not enough funds!" << endl;
			break;
		case StatusCode::InvalidCurrency:
			cout << "Invalid currency!" << endl;
			break;
	}
}
int main()
{
	BankAccount b{ 100, 1, AccountType::Collection, "BGN" };
	{
		StatusCode res = withdraw(b, 100);
		handleStatus(res);
	}
	{
		StatusCode res = withdraw(b, 100);
		handleStatus(res);
	}
	{
		StatusCode res = deposit(b, 200);
		handleStatus(res);
	}
	{
		StatusCode res = changeCurrency(b, "GBPA");
		handleStatus(res);
	}
	{
		StatusCode res = changeCurrency(b, "USD");
		handleStatus(res);
	}

	cout << b.balance << " " << b.currency << endl;
}


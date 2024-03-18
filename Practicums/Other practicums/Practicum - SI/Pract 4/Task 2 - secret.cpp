#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

class Secret
{
	char* taskDescription;
	char* password;
	unsigned unsuccessfulLoginAttempts;
	void replaceString(char*& str, const char* replacement)
	{
		if (!str || !replacement)
		{
			return;
		}

		delete[] str;
		str = new char[strlen(replacement) + 1];
		strcpy(str, replacement);
	}
public:
	Secret()
	{
		taskDescription = nullptr;
		password = nullptr;
		unsuccessfulLoginAttempts = 0;
	}
	Secret(const char* taskDescription, const char* password) : Secret()
	{
		if (!taskDescription || !password)
		{
			return;
		}

		this->taskDescription = new char[strlen(taskDescription) + 1];
		strcpy(this->taskDescription, taskDescription);
		this->password = new char[strlen(password) + 1];
		strcpy(this->password, password);
	}
	~Secret()
	{
		delete[] this->taskDescription;
		delete[] this->password;
	}
	const char* getTask(const char* pwd)
	{
		if (!pwd)
		{
			return "";
		}

		if (strcmp(pwd, this->password) == 0)
		{
			this->unsuccessfulLoginAttempts = 0;
			return this->taskDescription;
		}
		this->unsuccessfulLoginAttempts++;
		return "";
	}
	void setPassword(const char* newPassword, const char* oldPassword)
	{
		if (!newPassword || !oldPassword)
		{
			return;
		}

		if (strcmp(oldPassword, this->password) != 0)
		{
			this->unsuccessfulLoginAttempts++;
			return;
		}
		this->replaceString(this->password, newPassword);
	}
	void setTask(const char* newTask, const char* passwd)
	{
		if (!newTask || !passwd)
		{
			return;
		}

		if (strcmp(passwd, this->password) != 0)
		{
			this->unsuccessfulLoginAttempts++;
			return;
		}
		this->replaceString(this->taskDescription, newTask);
	}
	unsigned getLoginFails() const
	{
		return this->unsuccessfulLoginAttempts;
	}
};
int main()
{
	Secret secret("Task", "pass");
	std::cout << secret.getTask("pas3s");
	std::cout << secret.getTask("pass") << std::endl;
	std::cout << secret.getTask("pas2s");
	
	std::cout << secret.getLoginFails() << std::endl;
	secret.setTask("New task", "pas3s");
	secret.setTask("New task again", "pass");

	std::cout << secret.getTask("pass");
}
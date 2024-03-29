#pragma once

class SoftwareEngineer
{
	char* name = nullptr;;
	char* position = nullptr;
	unsigned salary = 0;
	void copyFrom(const SoftwareEngineer& other);
	void free();
public:
	SoftwareEngineer();
	SoftwareEngineer(const char* name, const char* position, unsigned salary);
	SoftwareEngineer(const SoftwareEngineer& other);
	~SoftwareEngineer();
	SoftwareEngineer& operator=(const SoftwareEngineer& other);

	const char* getName() const;
	const char* getPosition() const;
	unsigned getSalary() const;

	void setName(const char* name);
	void setPosition(const char* position);
	void setSalary(unsigned salary);
};
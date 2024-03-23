#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t MAX_NAME_LENGTH = 127;
constexpr size_t MAX_POSITION_LENGTH = 127;
constexpr size_t MAX_EMPLOYEE_COUNT = 15;
constexpr size_t MAX_DEPARTMENTS_COUNT = 10;

enum class ErrorCode 
{
    OK,
    NotFound,
    Duplicate,
    InvalidInput,
    SizeExceeded,
    Nullptr
};
class Employee
{
    char name[MAX_NAME_LENGTH + 1];
    char position[MAX_POSITION_LENGTH + 1];
    unsigned id;
    double salary;
public:
    Employee() : id(0), name("undefined"), position("undefined"), salary(0) {}
    Employee(unsigned id, const char* name, const char* position, double salary) : Employee()
    {
        this->id = id;
        setName(name);
        setPosition(position);
        updateSalary(salary);
    }
    unsigned getId() const
    {
        return id;
    }
    const char* getName() const
    {
        return name;
    }
    void setName(const char* name)
    {
        if (!name)
        {
            return;
        }

        if (strlen(name) > MAX_NAME_LENGTH)
        {
            return;
        }
        strcpy(this->name, name);
    }
    const char* getPosition() const
    {
        return position;
    }
    void setPosition(const char* position)
    {
        if (!position)
        {
            return;
        }

        if (strlen(position) > MAX_POSITION_LENGTH)
        {
            return;
        }
        strcpy(this->position, position);
    }
    double getSalary() const
    {
        return salary;
    }
    ErrorCode updateSalary(double amount)
    {
        if (amount < 0)
        {
            return ErrorCode::InvalidInput;
        }

        this->salary = amount;
        return ErrorCode::OK;
    }
};
class Department
{
    char name[MAX_NAME_LENGTH + 1];
    Employee employees[MAX_EMPLOYEE_COUNT];
    unsigned countOfEmployees;
    int indexof(unsigned employeeId)
    {
        for (size_t i = 0; i < countOfEmployees; i++)
        {
            if (employees[i].getId() == employeeId)
            {
                return i;
            }
        }
        return -1;
    }
public:
    Department() : name("undefined"), countOfEmployees(0) {}
    Department(const char* name) : Department()
    {
        setName(name);
    }
    const char* getName() const
    {
        return name;
    }
    void setName(const char* name)
    {
        if (!name)
        {
            return;
        }

        if (strlen(name) > MAX_NAME_LENGTH)
        {
            return;
        }
        strcpy(this->name, name);
    }
    unsigned getEmployeesCount() const
    {
        return countOfEmployees;
    }
    ErrorCode addEmployee(const Employee& employee)
    {
        if (countOfEmployees + 1 > MAX_EMPLOYEE_COUNT)
        {
            return ErrorCode::SizeExceeded;
        }
        if (containsEmployee(employee.getId()))
        {
            return ErrorCode::Duplicate;
        }

        employees[countOfEmployees++] = employee;
        return ErrorCode::OK;
    }
    ErrorCode addEmployees(const Employee* employees, size_t size)
    {
        if (!employees)
        {
            return ErrorCode::Nullptr;
        }

        for (size_t i = 0; i < size; i++)
        {
            ErrorCode status = addEmployee(employees[i]);
            if (status == ErrorCode::SizeExceeded)
            {
                break;
            }
        }
        return ErrorCode::OK;
    }
    ErrorCode removeEmployee(unsigned id)
    {
        int index = indexof(id);
        if (index == -1)
        {
            return ErrorCode::NotFound;
        }

        for (size_t i = index; i < countOfEmployees - 1; i++)
        {
            employees[i] = employees[i + 1];
        }
        countOfEmployees--;
    }
    bool containsEmployee(unsigned employeeId)
    {
        return indexof(employeeId) != -1;
    }
};
class Company
{
    Department departments[MAX_DEPARTMENTS_COUNT];
    unsigned countOfDepartments;
    int indexof(const char* name)
    {
        if (!name)
        {
            return -1;
        }
        for (size_t i = 0; i < countOfDepartments; i++)
        {
            if (strcmp(name, departments[i].getName()) == 0)
            {
                return i;
            }
        }
        return -1;
    }
public:
    Company() : countOfDepartments(0) {}
    ErrorCode addDepartment(const char* name)
    {
        if (countOfDepartments + 1> MAX_DEPARTMENTS_COUNT)
        {
            return ErrorCode::SizeExceeded;
        }

        Department dept(name);
        departments[countOfDepartments++] = dept;
        return ErrorCode::OK;
    }
    ErrorCode removeDepartment(const char* name)
    {
        int index = indexof(name);
        if (index == -1)
        {
            return ErrorCode::NotFound;
        }

        for (size_t i = index; i < countOfDepartments - 1; i++)
        {
            departments[i] = departments[i + 1];
        }
        countOfDepartments--;
    }
    ErrorCode addEmployeeToDepartment(const char* departmentName, const Employee& employee)
    {
        int index = indexof(departmentName);
        if (index == -1)
        {
            return ErrorCode::NotFound;
        }

        return departments[index].addEmployee(employee);
    }
    ErrorCode removeEmployeeFromDepartment(const char* departmentName, unsigned id)
    {
        int index = indexof(departmentName);
        if (index == -1)
        {
            return ErrorCode::NotFound;
        }

        return departments[index].removeEmployee(id);
    }
};
int main()
{
    Employee e1(1, "Ivan", "Junior Software Engineer", 3000);
    Employee e2(2, "Georgi", "DevOps Engineer", 6000);
    Employee e3(3, "Petur", "Tech Support", 2000);
    Employee e4(4, "Hristo", "Tech Support", 2000);

    e1.updateSalary(-100); // shouldn't update
    std::cout << e1.getSalary();

    Department dept1("Engineering");
    dept1.addEmployee(e1);
    dept1.addEmployee(e2);

    Company company;
    company.addDepartment("Tech Support");
    company.addEmployeeToDepartment("Tech Support", e3);
    company.addEmployeeToDepartment("Tech Support", e4);
}
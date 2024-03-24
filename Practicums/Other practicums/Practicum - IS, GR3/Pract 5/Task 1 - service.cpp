#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

constexpr size_t MAX_NAME_LENGTH = 32;
constexpr size_t PIN_LENGTH = 10;
constexpr size_t MAX_TECHNICIANS_COUNT = 30;

enum class ApplianceCategory
{
    Undefined,
    Smartphones,
    Laptops,
    TV,
    WashingMachines,
    Projectors,
    Cameras,
    AC
};
class BrokenAppliance
{
    ApplianceCategory category;
    float repairPrice;
    bool isInWarranty;
public:
    BrokenAppliance() : category(ApplianceCategory::Undefined), repairPrice(0), isInWarranty(false) {}
    ApplianceCategory getApplianceCategory() const
    {
        return category;
    }
    void setApplianceCategory(ApplianceCategory category)
    {
        this->category = category;
    }
    float getRepairPrice() const
    {
        return repairPrice;
    }
    void setRepairPrice(float repairPrice)
    {
        if (repairPrice < 0)
        {
            return;
        }

        this->repairPrice = repairPrice;
    }
    bool getIsInWarranty() const
    {
        return isInWarranty;
    }
    void setIsInWarranty(bool isInWarranty)
    {
        this->isInWarranty = isInWarranty;
    }
};
class Technic
{
    char name[MAX_NAME_LENGTH + 1];
    char pin[PIN_LENGTH + 1];
    ApplianceCategory applianceCategory;
    float profit;
    unsigned serviceCount;
public:
    Technic() : name("undefined"), pin("undefined"), applianceCategory(ApplianceCategory::Undefined), profit(0), serviceCount(0) {}
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
    const char* getPIN() const
    {
        return pin;
    }
    void setPIN(const char* pin)
    {
        if (!pin)
        {
            return;
        }

        if (strlen(pin) != PIN_LENGTH)
        {
            return;
        }
        strcpy(this->pin, pin);
    }
    ApplianceCategory getApplianceCategory() const
    {
        return applianceCategory;
    }
    void setApplianceCategory(ApplianceCategory applianceCategory)
    {
        this->applianceCategory = applianceCategory;
    }
    float getProfit() const
    {
        return profit;
    }
    unsigned getServiceCount() const
    {
        return serviceCount;
    }
    bool canRepairAppliance(const BrokenAppliance& appliance) const
    {
        return appliance.getApplianceCategory() == this->applianceCategory;
    }
    void serialize(std::ofstream& ofs)
    {
        ofs << name << "," << pin << "," << (profit / serviceCount);
    }
};
class Client
{
    char name[MAX_NAME_LENGTH + 1];
    BrokenAppliance appliance;
public:
    Client() : name("undefined"), appliance() {}
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
    const BrokenAppliance& getBrokenAppliance() const
    {
        return appliance;
    }
    void setBrokenAppliance(const BrokenAppliance& appliance)
    {
        this->appliance = appliance;
    }
};
class Service
{
    Technic technicians[MAX_TECHNICIANS_COUNT];
    size_t techniciansCount;
    int indexof(const char* pin)
    {
        if (!pin)
        {
            return -1;
        }

        for (size_t i = 0; i < techniciansCount; i++)
        {
            if (strcmp(pin, technicians[i].getPIN()) == 0)
            {
                return i;
            }
        }
        return -1;
    }
    bool serializeTechnicians(std::ofstream& ofs)
    {
        for (size_t i = 0; i < techniciansCount; i++)
        {
            technicians[i].serialize(ofs);
            if (i < techniciansCount - 1)
            {
                ofs << std::endl;
            }
        }
    }
public:
    Service() : techniciansCount(0) {}
    const Technic& getSuitableTechnic(const Client& client) const
    {
        for (size_t i = 0; i < techniciansCount; i++)
        {
            if (technicians[i].canRepairAppliance(client.getBrokenAppliance()))
            {
                return technicians[i];
            }
        }
        return {};
    }
    bool hireTechnic(const Technic& technic)
    {
        if (techniciansCount + 1 > MAX_TECHNICIANS_COUNT)
        {
            return false;
        }
        technicians[techniciansCount++] = technic;
        return true;
    }
    bool fireTechnic(const char* pin)
    {
        if (!pin)
        {
            return false;
        }

        int index = indexof(pin);
        if (index == -1)
        {
            return false;
        }
        for (size_t i = index; i < techniciansCount - 1; i++)
        {
            technicians[i] = technicians[i + 1];
        }
        techniciansCount--;
        return true;
    }
    bool serializeTechnicians(const char* filename)
    {
        if (!filename)
        {
            return false;
        }

        std::ofstream ofs(filename);
        if (!ofs.is_open())
        {
            return false;
        }

        return serializeTechnicians(ofs);
    }
};
int main()
{
    
}
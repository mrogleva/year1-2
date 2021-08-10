//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Практически изпит
//
// Име: Цветелин Костадинов Цецков
// ФН: 82130
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на изпита: 07.07.2021 г.
// Начален час на изпита: 8
// Кой компилатор използвате: Visual C++
//
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

class Property
{
public:
    Property(const std::string& name, int quantity, double priceCoeficient)
        : name(name), quantity(quantity), priceCoeficient(priceCoeficient)
    {
    }

    inline const std::string getName() const { return name; }
    inline int getQuantity() const { return quantity; }
    inline double getPriceCoef() const { return priceCoeficient; }

    inline const double getTotalPrice() const
    {
        return quantity * priceCoeficient;
    }

    friend std::ostream& operator<<(std::ostream&, const Property&);

private:
    const std::string name;
    const int quantity;
    const double priceCoeficient;
};

std::ostream& operator<<(std::ostream& os, const Property& prop)
{
    os << prop.name << ' ' << prop.quantity << ' ' << prop.priceCoeficient;
    return os;
}

class Component
{
public:
    virtual ~Component() = default;

    /// @brief Transfers ownership of the property. Can be done with unique ptr,
    /// but chose to do it with raw
    /// @param
    void insertProp(Property propPtr) { properties.push_back(propPtr); }

    /// @brief Gets the quantity of a property by name
    /// @param name
    /// @return the index of the property if it exists, -1 otherwise
    int getPropByName(const std::string& name) const
    {
        for (std::size_t i = 0; i < properties.size(); ++i)
        {
            if (name == properties[i].getName())
            {
                return i;
            }
        }
        return -1;
    }

    double getTotalPrice() const
    {
        double sum = 0.0;
        for (std::size_t i = 0; i < properties.size(); ++i)
        {
            sum += properties[i].getTotalPrice();
        }
        return sum;
    }

    bool isBetterThan(const Component& other) const
    {
        for (std::size_t i = 0; i < properties.size(); ++i)
        {
            for (std::size_t j = 0; j < other.properties.size(); ++j)
            {
                if (properties[i].getName() == other.properties[j].getName())
                {
                    if (other.properties[j].getQuantity() >
                        properties[i].getQuantity())
                    {
                        return false;
                    }
                    break;
                }
            }
        }
        return true;
    }
    bool operator>=(const Component& other) const
    {
        return isBetterThan(other);
    }

    friend std::ostream& operator<<(std::ostream&, const Component&);

protected:
    std::vector<Property> properties;
};

std::ostream& operator<<(std::ostream& os, const Component& cmp)
{
    for (std::size_t i = 0; i < cmp.properties.size(); ++i)
    {
        os << cmp.properties[i] << std::endl;
    }
    return os;
}

// we can have cases like VRAM, where it is both ram and video card related. So
// we extend virtually

class CPU : public virtual Component
{
public:
    CPU(int numberOfCores,
        double pricePerCore,
        double frequencyInMHz,
        double pricePerMHz)
        : numberOfCores(numberOfCores),
          pricePerCore(pricePerCore),
          frequencyInMHz(frequencyInMHz),
          pricePerMHz(pricePerMHz)
    {
        insertProp(Property("Number of cores", numberOfCores, pricePerCore));
        insertProp(Property("Freaquency(KHz)",
                            static_cast<int>(frequencyInMHz *
                                             1000),  // casts should be explicit
                            pricePerMHz / 1000.0));
    }

protected:
    const int numberOfCores;
    const double pricePerCore;
    const double frequencyInMHz;
    const double pricePerMHz;
};

class RAM : public virtual Component
{
public:
    RAM(int gigabites,
        double pricePerGB,
        int chipCount,
        double pricePerChip,
        int colorCount,
        double pricePerColor)
        : gigabites(gigabites),
          pricePerGB(pricePerGB),
          chipCount(chipCount),
          pricePerChip(pricePerChip),
          colorCount(colorCount),
          pricePerColor(pricePerColor)
    {
        insertProp(Property("Storage(MB)", gigabites, pricePerGB));
        insertProp(Property("Chips", chipCount, pricePerChip));
        insertProp(Property("Color count", colorCount, pricePerColor));
    }

protected:
    const int gigabites;
    const double pricePerGB;
    const int chipCount;
    const double pricePerChip;
    const int colorCount;
    const double pricePerColor;
};

class HDD : public virtual Component
{
public:
    HDD(int terabyteCount,
        double pricePerTerabyte,
        int readingSpeedInMB,
        double pricePerReadingSpeedMB,
        int writingSpeedMB,
        double pricePerWritingSpeedMB)
        : terabyteCount(terabyteCount),
          pricePerTerabyte(pricePerTerabyte),
          readingSpeedInMB(readingSpeedInMB),
          pricePerReadingSpeedMB(pricePerReadingSpeedMB),
          writingSpeedMB(writingSpeedMB),
          pricePerWritingSpeedMB(pricePerWritingSpeedMB)
    {
        insertProp(Property("Storage(TB)", terabyteCount, pricePerTerabyte));
        insertProp(Property("Reading speed(MB)", readingSpeedInMB,
                            pricePerReadingSpeedMB));
        insertProp(Property("Writing speed(MB)", writingSpeedMB,
                            pricePerWritingSpeedMB));
    }

protected:
    const int terabyteCount;
    const double pricePerTerabyte;
    const int readingSpeedInMB;
    const double pricePerReadingSpeedMB;
    const int writingSpeedMB;
    const double pricePerWritingSpeedMB;
};

CPU readFromStreamCPU(std::istream& is)
{
    int numberOfCores;
    double pricePerCore;
    double frequencyInMHz;
    double pricePerMHz;

    is >> numberOfCores >> pricePerCore >> frequencyInMHz >> pricePerMHz;
    return CPU(numberOfCores, pricePerCore, frequencyInMHz, pricePerMHz);
}

RAM readFromStreamRAM(std::istream& is)
{
    int gigabites;
    double pricePerGB;
    int chipCount;
    double pricePerChip;
    int colorCount;
    double pricePerColor;

    is >> gigabites >> pricePerGB >> chipCount >> pricePerChip >> colorCount >>
        pricePerColor;

    return RAM(gigabites, pricePerGB, chipCount, pricePerChip, colorCount,
               pricePerColor);
}

HDD readFromStreamHDD(std::istream& is)
{
    int terabyteCount;
    double pricePerTerabyte;
    int readingSpeedInMB;
    double pricePerReadingSpeedMB;
    int writingSpeedMB;
    double pricePerWritingSpeedMB;

    is >> terabyteCount >> pricePerTerabyte >> readingSpeedInMB >>
        pricePerReadingSpeedMB >> writingSpeedMB >> pricePerWritingSpeedMB;

    return HDD(terabyteCount, pricePerTerabyte, readingSpeedInMB,
               pricePerReadingSpeedMB, writingSpeedMB, pricePerWritingSpeedMB);
}

class Shop
{
public:
    Shop() {}

    Shop(const Shop& other)
    {
        for (std::size_t i = 0; i < other.componentCount(); ++i)
        {
            // this does not have to be component, this breaks a check later in
            // the code!!!
            insertComponent(new Component(*other.components[i]));
        }
    }

    Shop& operator=(const Shop& other)
    {
        if (this != &other)
        {
            for (std::size_t i = 0; i < other.componentCount(); ++i)
            {
                // this does not have to be component, this breaks a check later
                // in the code!!!
                insertComponent(new Component(*other.components[i]));
            }
        }
        return *this;
    }

    ~Shop()
    {
        for (std::size_t i = 0; i < components.size(); ++i)
        {
            delete components[i];
        }
    }

    void insertComponent(Component* component)
    {
        components.push_back(component);
        component = nullptr;
    }

    void removeAt(std::size_t idx)
    {
        components.erase(components.begin() + idx);
    }

    std::size_t componentCount() const { return components.size(); }

    const Component& operator[](std::size_t idx) const
    {
        assert(idx < components.size());
        return *components[idx];
    }

    Component& operator[](std::size_t idx)
    {
        assert(idx < components.size());
        return *components[idx];
    }

    Component* getAtAsPrt(std::size_t idx)
    {
        assert(idx < components.size());
        return components[idx];
    }

    friend class ShopBuilder;

private:
    std::vector<Component*> components;
};

class ShopBuilder
{
public:
    static Shop readFromFile(const std::string& filepath)
    {
        Shop res;
        std::ifstream file(filepath);
        if (!file.good())
        {
            throw std::runtime_error("Could not open file!");
        }
        while (!file.eof())
        {
            std::string currLine;
            std::getline(file, currLine);
            std::stringstream ss(currLine);
            std::string keyword;
            ss >> keyword;
            if (keyword == "CPU")
            {
                CPU parsed = readFromStreamCPU(ss);
                res.components.push_back(new CPU(parsed));
            }
            else if (keyword == "RAM")
            {
                RAM parsed = readFromStreamRAM(ss);
                res.components.push_back(new RAM(parsed));
            }
            else if (keyword == "HDD")
            {
                HDD parsed = readFromStreamHDD(ss);
                res.components.push_back(new HDD(parsed));
            }
            else
            {
                throw std::runtime_error("Unrecognised keyword! " + keyword);
            }
        }
        file.close();  // the destructor will close it, but nevertheless
        return res;
    }
};

/// @brief Holds components, but does not allow duplicate types of components
class UniqueComponentContainer
{
public:
    UniqueComponentContainer() {}

    UniqueComponentContainer(const UniqueComponentContainer& other)
    {
        for (std::size_t i = 0; i < other.componentCount(); ++i)
        {
            insert(new Component(*other.components[i]));
        }
    }

    UniqueComponentContainer& operator=(const UniqueComponentContainer& other)
    {
        if (this != &other)
        {
            for (std::size_t i = 0; i < other.componentCount(); ++i)
            {
                insert(new Component(*other.components[i]));
            }
        }
        return *this;
    }

    virtual ~UniqueComponentContainer()
    {
        for (std::size_t i = 0; i < components.size(); ++i)
        {
            delete components[i];
        }
    }

    std::size_t componentCount() const { return components.size(); }

    void insert(Component* component)
    {
        if (isSameTypeAlreadyInConfiguration(component))
        {
            throw std::runtime_error(
                "The same type of component is already in the configuration!");
        }
        components.push_back(component);
        component = nullptr;
    }

    const Component& operator[](std::size_t i) const
    {
        assert(i < components.size());
        return *components[i];
    }

    Component& operator[](std::size_t i)
    {
        assert(i < components.size());
        return *components[i];
    }

    double getTotalPrice() const
    {
        const double forZimbu = 7 / 100;
        double total = 0.0;
        for (std::size_t i = 0; i < components.size(); ++i)
        {
            total = components[i]->getTotalPrice();
        }
        return total + total * forZimbu;
    }

protected:
    std::vector<Component*> components;

    bool isSameTypeAlreadyInConfiguration(Component* component) const
    {
        for (std::size_t i = 0; i < components.size(); ++i)
        {
            if (typeid(*components[i]).name() == typeid(*component).name())
            {
                return true;
            }
        }
        return false;
    }
};

class Configuration : public virtual UniqueComponentContainer
{
    friend std::ostream& operator<<(std::ostream&, const Configuration&);
};

std::ostream& operator<<(std::ostream& os, const Configuration& cfg)
{
    for (std::size_t i = 0; i < cfg.componentCount(); ++i)
    {
        os << "\t" << cfg[i] << std::endl;
    }
    return os;
}

class Requirement : public virtual UniqueComponentContainer
{
    bool satisfiesRequirement(const Configuration& configuration) const
    {
        for (std::size_t i = 0; i < components.size(); ++i)
        {
            bool foundSameType = false;
            for (std::size_t j = 0; j < configuration.componentCount(); ++j)
            {
                if (typeid(*components[i]).name() ==
                    typeid(configuration[j]).name())
                {
                    // they are the same type
                    foundSameType = true;
                    if (configuration[j].isBetterThan(*components[i]))
                    {
                        return false;
                    }
                }
            }
            if (!foundSameType)
            {
                // there is a requirement we didn't meet
                return false;
            }
        }
        return true;
    }

    friend bool operator>=(const Requirement& req, const Configuration& config);
};

bool operator>=(const Requirement& req, const Configuration& config)
{
    return req.satisfiesRequirement(config);
}

class Configurator
{
public:
    Configurator(Shop& shop, const Requirement& req) : shop(shop), req(req) {}

    Configuration assembleForRequirement()
    {
        Configuration res;
        for (std::size_t i = 0; i < req.componentCount(); ++i)
        {
            bool foundPart = false;

            for (std::size_t j = 0; j < shop.componentCount(); ++j)
            {
                if (typeid(*shop.getAtAsPrt(j)) == typeid(req[i]) &&
                    shop[j].isBetterThan(req[i]))
                {
                    foundPart = true;
                    res.insert(&shop[i]);
                    shop.removeAt(i);
                    break;
                }
            }

            if (!foundPart)
            {
                for (std::size_t i = 0; i < res.componentCount(); ++i)
                {
                    shop.insertComponent(
                        &res[i]);  // it's going to get destructed so we don't
                                   // care for the nullptrs
                }
                throw std::runtime_error("No part matches the required part");
            }
        }
        return res;
    }

private:
    Shop& shop;
    const Requirement& req;
};

int main(const char** argv, int argc)
{
    Shop st = ShopBuilder::readFromFile("./test.txt");

    std::string filepath;
    if (argc == 0)
    {
        std::cout << "You should input the filepath! Input it now: "
                  << std::endl;
        std::getline(std::cin, filepath);
    }
    else if (argc == 1)
    {
        filepath = argv[0];
    }
    else
    {
        std::cerr << "Unrecognised number of args. Aborting!" << std::endl;
        return 1;
    }

    std::cout << "Loading shop..." << std::endl;
    Shop shop;
    try
    {
        shop = ShopBuilder::readFromFile(filepath);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    std::cout << "Loaded shop" << std::endl;
    std::cout << "Begginnning to input requirements. Enter finish to finalize"
              << std::endl;

    std::string currCommand = "";
    Requirement req;
    while (true)
    {
        std::cin >> currCommand;
        if (currCommand == "finish")
        {
            break;
        }
        try
        {
            if (currCommand == "CPU")
            {
                CPU cpu = readFromStreamCPU(std::cin);

                req.insert(new CPU(cpu));
            }
            else if (currCommand == "RAM")
            {
                RAM ram = readFromStreamRAM(std::cin);

                req.insert(new RAM(ram));
            }
            else if (currCommand == "HDD")
            {
                HDD hdd = readFromStreamHDD(std::cin);

                req.insert(new HDD(hdd));
            }
            else
            {
                std::cerr << "Unrecognised command please try again with other "
                             "command!"
                          << std::endl;
            }
        }
        catch (std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    Configurator configurator = Configurator(shop, req);
    try
    {
        Configuration cfg = configurator.assembleForRequirement();
        std::cout << "Configuration: " << std::endl;
        std::cout << "\t" << cfg << std::endl;
        std::cout << "Total price of configuration: " << cfg.getTotalPrice();
    }
    catch (std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
#include "configurator.hpp"
#include "store_builder.hpp"

int main(int argc, const char** argv)
{
    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    std::string filepath;
    if (argc == 1)
    {
        std::cout<<"Please input a filepath: "<< std::endl;
        std::getline(std::cin, filepath);
    }
    else if (argc == 2)
    {
        filepath = argv[1];
    }
    else
    {
        std::cout<<"Invalid filepath input."<<std::endl;
        return 1;
    }

    store* shop;
    try
    {
        shop = store_builder::buildStore(filepath); //delete !
        // shop = ShopBuilder::readFromFile(filepath);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    std::cout << "Loaded store." << std::endl;
    std::cout << "Enter your requirement parameters/CPU, RAM, HDD/. Enter finish to finalize"<< std::endl;

    std::string cmd = "";
    requirement req;
    while (true)
    {
        std::cin >> cmd;
        if (cmd == "finish")
        {
            break;
        }
        if (cmd == "CPU")
        {
            int cores;
            double corePrice;
            double frequency;
            double frequencyPrice;

            std::cin>>cores>>corePrice>>frequency>>frequencyPrice;
            CPU temp(cmd, cores, frequency, corePrice, frequencyPrice);
            try
            {
                req.add(new CPU(temp));
                std::cout <<"Parameter added."<< std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (cmd == "RAM")
        {;
            int gb;
            double gbPrice;
            int chip;
            double chipPrice;
            int colors;
            double colorPrice;

            std::cin>>gb>>gbPrice>>chip>>chipPrice>>colors>>colorPrice;

            RAM temp(cmd, gb, gbPrice, chip, chipPrice, colors, colorPrice);
            try
            {
                req.add(new RAM(temp));
                std::cout <<"Parameter added."<< std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if (cmd == "HDD")
        {
            int tb;
            double tbPrice;
            int readingSpeed;
            double readingPrice;
            int writingSpeed;
            double writingPrice;

            std::cin>>tb>>tbPrice>>readingSpeed>>readingPrice>>writingSpeed>>writingPrice;

            HDD temp(cmd, tb, tbPrice, readingSpeed, readingPrice, writingSpeed, writingPrice);
            try
            {
                req.add(new HDD(temp));
                std::cout <<"Parameter added."<< std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            std::cerr << "Invalid command. Try again: "
                        << std::endl;
        }
    }
    try
    {
        configurator& conf = configurator::getInstance();
        configuration* cfg = conf.configure(shop, req);
        std::cout << "Configuration: " << std::endl;
        for(std::size_t i = 0; i< cfg->componentCount(); ++i)
        {
            cfg->getComponent(i)->print();
        }
        std::cout << "Total price of configuration: " << cfg->calculatePrice();
    }
    catch (std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
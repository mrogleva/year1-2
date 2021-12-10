#define CATCH_CONFIG_MAIN
#include "implementation.h"
#include "catch2.hpp"

TEST_CASE("MrazMag initialization")
{
    MrazMag test;
    test.init(1, 2, 0);
    REQUIRE(test.bananasAvailable == 2);
    REQUIRE(test.schweppesAvailable == 0);

    std::vector<Client> clientsList = {
        Client{0, 0, 10, 10},
		Client{0, 10, 0, 3},
		Client{1, 10, 10, 5} };
    
    test.addClients(clientsList.data(), clientsList.size());
    REQUIRE(test.allClients.size() == 3);
    REQUIRE(test.allClients[0].index == 0);
    REQUIRE(test.allClients[1].index == 1);
    REQUIRE(test.allClients[2].index == 2);
    REQUIRE(test.allClients[2].arriveMinute == 1);
    REQUIRE(test.allClients[1].banana == 10);
    REQUIRE(test.allClients[2].leaveTime == 6);
}
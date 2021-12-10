#define CATCH_CONFIG_MAIN
#include "implementation.h"
#include "queue.h"
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

TEST_CASE("class queue")
{
    queue testQueue(3);
    REQUIRE(testQueue.size() == 0);
    REQUIRE(testQueue.empty() == true);
    REQUIRE(testQueue.full() == false);

    worker w1{ResourceType::banana, 2, 10};
    testQueue.enqueue(w1);
    REQUIRE(testQueue.size() == 1);
    REQUIRE(testQueue.empty() == false);
    REQUIRE(testQueue.full() == false);
    REQUIRE(testQueue.head()->minuteSent == 2);

    worker w2{ResourceType::schweppes, 3, 11};
    testQueue.enqueue(w2);
    REQUIRE(testQueue.size() == 2);
    REQUIRE(testQueue.empty() == false);
    REQUIRE(testQueue.full() == false);
    REQUIRE(testQueue.head()->minuteSent == 2);

    worker w3{ResourceType::schweppes, 4, 12};
    testQueue.enqueue(w3);
    REQUIRE(testQueue.size() == 3);
    REQUIRE(testQueue.empty() == false);
    REQUIRE(testQueue.full() == true);
    REQUIRE(testQueue.head()->minuteSent == 2);

    REQUIRE_THROWS_AS(testQueue.enqueue(w3), std::exception);

    testQueue.dequeue();
    REQUIRE(testQueue.size() == 2);
    REQUIRE(testQueue.empty() == false);
    REQUIRE(testQueue.full() == false);
    REQUIRE(testQueue.head()->minuteSent == 3);

    testQueue.dequeue();
    REQUIRE(testQueue.size() == 1);
    REQUIRE(testQueue.empty() == false);
    REQUIRE(testQueue.full() == false);
    REQUIRE(testQueue.head()->minuteSent == 4);

    testQueue.dequeue();
    REQUIRE(testQueue.size() == 0);
    REQUIRE(testQueue.empty() == true);
    REQUIRE(testQueue.full() == false);
    REQUIRE(testQueue.head() == nullptr);

    REQUIRE_THROWS_AS(testQueue.dequeue(), std::exception);
}
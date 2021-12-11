#pragma once

#include "interface.h"
#include "queue.h"
#include "client.h"

/// This is sample empty implementation you can place your solution here or delete this and include tests to your solution


struct MrazMag : Store {
	ActionHandler *actionHandler = nullptr;
	int workersAvailable = 0; ///< workers ready to be sent to the storage
	int bananaAvailable = 0; ///< amount of bananas available in store
	int schweppesAvailable = 0; ///< amount of schweppes available in store
	
	int bananaExpected = 0; ///< the amount of bananas, which will be brought by already sent workers
	int schweppesExpected = 0; ///< the amount of schweppes, which will be brought by already sent workers

	std::vector<MrazMag_client> allClients;
	std::vector<MrazMag_client> waitingList;
	myQueue storage;

	void setActionHandler(ActionHandler *handler) override;
	void init(int workerCount, int startBanana, int startSchweppes) override;
	void addClients(const Client *clients, int count) override;
	void advanceTo(int minute) override;
	int getBanana() const;
	int getSchweppes() const;

	/// Executes all the actions that must happen in a single minute
	void playMinute(int minute);
	/// Sends workers to the storage on (one)clients arrival
	void arrivals(size_t i);
	bool needsBanana(size_t index);
	bool needsSchweppes(size_t index);
};

Store *createStore();
console_v: client.o implementation.o queue.o worker.o ActionHandler.o main.o
	g++ client.o implementation.o queue.o worker.o ActionHandler.o main.o -o console_v

ActionHandler.o: ActionHandler.cpp
	g++ -c ActionHandler.cpp

client.o: client.cpp
	g++ -c client.cpp

implementation.o: implementation.cpp
	g++ -c implementation.cpp

queue.o: queue.cpp
	g++ -c queue.cpp

main.o: main.cpp
	g++ -c main.cpp

worker.o: worker.cpp
	g++ -c worker.cpp

clean:
	rm *.o
test_v: catch2.o client.o implementation.o queue.o tests.o worker.o
	g++ catch2.o client.o implementation.o queue.o tests.o worker.o -o test_v

catch2.o: catch2.cpp
	g++ -c catch2.cpp

client.o: client.cpp
	g++ -c client.cpp

implementation.o: implementation.cpp
	g++ -c implementation.cpp

queue.o: queue.cpp
	g++ -c queue.cpp

tests.o: tests.cpp
	g++ -c tests.cpp

worker.o: worker.cpp
	g++ -c worker.cpp

clean:
	rm *.o
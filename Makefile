all: server.out client.out

server.out: Server.o Sample.o InputAndValidation.o Distance.o Knn.o Command.o CLI.o DefaultIO.o
	g++ -pthread -std=c++11 Server.o Sample.o InputAndValidation.o Distance.o Knn.o  DefaultIO.o CLI.o Command.o -o server.out

client.out: Client.o Sample.o InputAndValidation.o Distance.o Knn.o CLI.o Command.o DefaultIO.o
	g++ -pthread -std=c++11 Client.o Sample.o InputAndValidation.o Distance.o Knn.o DefaultIO.o CLI.o Command.o -o client.out

CLI.o:
	g++ -std=c++11 -c CLI.cpp CLI.h

Client.o:
	g++ -std=c++11 -c Client.cpp Client.h

Server.o:
	g++ -std=c++11 -c Server.cpp Server.h

Command.o:
	g++ -std=c++11 -c Command.cpp Command.h

DefaultIO.o:
	g++ -std=c++11 -c DefaultIO.cpp DefaultIO.h

Distance.o:
	g++ -std=c++11 -c Distance.cpp Distance.h

InputAndValidation.o:
	g++ -std=c++11 -c InputAndValidation.cpp Header.h

Knn.o:
	g++ -std=c++11 -c Knn.cpp Knn.h

Sample.o:
	g++ -std=c++11 -c Sample.cpp Sample.h

target: dependencies
	action

clean:
	rm *.o *.h.gch a.out


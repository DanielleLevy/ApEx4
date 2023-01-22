# ApEx4
## How to compile:
write the following in the terminal , after each one press enter:

1. git clone git@github.com:DanielleLevy/ApEx4.git
2. cd ApEx4
3. make

## How to run:
### The Server(first):
1. make sure youre in ApEx4. if not write cd ApEx4
2. write :
./server.out port
3. press enter

### The Client(after the server):
1. make sure youre in ApEx4. if not write cd ApEx4
2. write :
./client.out ip port
3. press enter

YOU CAN RUN MORE THEN 1 CLIENT IN PARALLEL.


## Description:
This is the fourth and final exercise out of 4 exercises in the "Advanced Programming 1" course. The exercise is a continuation of the first three exercises in the course. In this part of the exercise we divided the work between us, each of us performed several departments and functions as set out below:

1. CLI class - we created a "CLI" class (in the cpp file and the h file). The class is initialized by an object of "DefaultIO" and creates a vector of the command objects. There is a starting function (presenting a menu, reading input and executing the command) and there is destructor (in order to free memory). This is a component of a "client" class that manages all commands (holding a set of commands).

2. DefaultIO class - we created a "DefaultIO" class (in the cpp file and the h file). The class is inherited to "StandardIO" and "SocketIO". The SocketIO has a number of functions (writing to the socket and 2 reading functions, one of which is intended for command 2 and one for command 1. The difference between the two is that because the result of command 2 may be long, we added "D" to know when the string is over).

3. Command class - we created a "Command" class (in the cpp file and the h file). The class presents execution functions for each of the 6 possible commands on the menu: (uploading a CSV file, set of KNN algorithm, Data Classify, View results, downloading the results, and exit the CLI). Also, "Setting" also has a checking function. Each of the commands, of course, also have its own constructor.

Additional Comments:

1. The work was carried out according to the guidelines and rules of object-oriented programming in the CPP language.
2. Each of the classes - server and client, has its own main function (which contains tests) that will allow you to run the file according to the instructions above.
3. The input from the user is composed as follows: in each vector the numbers are separated by a single space. From the last number in the vector to the distance function there is also a single space and from the distance function to K there is also a single space.
4.The exercise was implemented according to a "command" design pattern that there is an abstract class called "command" and has a method called "execute" and a "description" string.
5. We will also note that the "server" class and the "client" class have been adapted that the server can take care of a number of clients simultaneously at the same time, which means the server works with multi threads. Only the client is the one who can access the files.
6. The information that the server sends to the client is up to 4096 Bytes.
7. This program was written in the CPP language, developed in the CLION development environment and adapted to run on Bar Ilan University servers (U2/PLANET), as requested.

target =  main
sources = main.cpp mdfile.cpp comstr.cpp create_servers.cpp message_send.cpp auth.cpp er.cpp math.cpp
CC = g++
CCFlags = -Wall
LDLIBS = -lcrypto++
OPT = -Ofast
all:build
build:
	$(CC) $(CCFlags) $(OPT) $(sources) -o $(target) $(LDLIBS)
	
unittest:
	g++ -Wall -Ofast UnitTest.cpp mdfile.cpp comstr.cpp create_servers.cpp message_send.cpp auth.cpp er.cpp math.cpp -o result -lcrypto++ -lUnitTest++
dbg:
	$(CC) -g $(sources) -o $(target)DBG

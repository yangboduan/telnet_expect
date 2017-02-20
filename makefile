CPP      = g++
CC       = gcc
CFLAGS   = -std=gnu++0x -g 
OBJ      = main.o swexpect.o 
LINKOBJ  = main.o swexpect.o
LIBS     = -lexpect -ltcl  
BIN      = telnet_expect
RM       = rm -rf

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)  


clean: 
	${RM} $(OBJ) $(BIN)

cleanobj:
	${RM} *.o


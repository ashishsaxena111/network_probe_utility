#compiler
CC=gcc

INCLUDE_PROB=./process/inc/

INCLUDE_CLI=./cli/inc/

OBJ_PROB=./process/obj

OBJ_CLI=./cli/obj

SRC_CLI=./cli/src

SRC_PROB=./process/src

BIN=./bin

CFLAGS=-g -c 

#CFLAGS=-o2 -c 

#
all: $(BIN)/prob $(BIN)/util

$(BIN)/prob: $(OBJ_PROB)/main.o $(OBJ_PROB)/calculate.o $(OBJ_PROB)/process_packet.o $(OBJ_PROB)/send_to.o $(OBJ_PROB)/sig_alrm.o $(OBJ_PROB)/tv_sub.o $(OBJ_PROB)/host.o $(OBJ_PROB)/sock_host.o $(OBJ_PROB)/bandwidth.o 

	$(CC)  -g -o $(BIN)/prob $(OBJ_PROB)/main.o $(OBJ_PROB)/calculate.o $(OBJ_PROB)/process_packet.o  $(OBJ_PROB)/send_to.o  $(OBJ_PROB)/sig_alrm.o $(OBJ_PROB)/tv_sub.o $(OBJ_PROB)/host.o $(OBJ_PROB)/sock_host.o $(OBJ_PROB)/bandwidth.o

$(OBJ_PROB)/main.o: $(SRC_PROB)/main.c $(INCLUDE_PROB)/process.h
	$(CC) $(CFLAGS) -o $(OBJ_PROB)/main.o -c $(SRC_PROB)/main.c -I$(INCLUDE_PROB)
$(OBJ_PROB)/calculate.o: $(SRC_PROB)/calculate.c $(INCLUDE_PROB)/process.h
	$(CC) $(CFLAGS) -o $(OBJ_PROB)/calculate.o -c $(SRC_PROB)/calculate.c -I $(INCLUDE_PROB)
$(OBJ_PROB)/process_packet.o: $(SRC_PROB)/process_packet.c $(INCLUDE_PROB)/process.h
	$(CC) $(CFLAGS) -o $(OBJ_PROB)/process_packet.o -c $(SRC_PROB)/process_packet.c -I $(INCLUDE_PROB)
$(OBJ_PROB)/send_to.o: $(SRC_PROB)/send_to.c $(INCLUDE_PROB)/process.h
	$(CC) $(CFLAGS) -o $(OBJ_PROB)/send_to.o -c $(SRC_PROB)/send_to.c -I $(INCLUDE_PROB)
$(OBJ_PROB)/sig_alrm.o: $(SRC_PROB)/sig_alrm.c $(INCLUDE_PROB)/process.h
	$(CC) $(CFLAGS) -o $(OBJ_PROB)/sig_alrm.o -c $(SRC_PROB)/sig_alrm.c -I $(INCLUDE_PROB)
$(OBJ_PROB)/tv_sub.o: $(SRC_PROB)/tv_sub.c $(INCLUDE_PROB)/process.h
	$(CC) $(CFLAGS) -o $(OBJ_PROB)/tv_sub.o -c $(SRC_PROB)/tv_sub.c -I $(INCLUDE_PROB)
$(OBJ_PROB)/host.o: $(SRC_PROB)/host.c $(INCLUDE_PROB)/process.h
	$(CC) $(CFLAGS) -o $(OBJ_PROB)/host.o -c $(SRC_PROB)/host.c -I $(INCLUDE_PROB)
$(OBJ_PROB)/sock_host.o: $(SRC_PROB)/sock_host.c $(INCLUDE_PROB)/process.h
	$(CC) $(CFLAGS) -o $(OBJ_PROB)/sock_host.o -c $(SRC_PROB)/sock_host.c -I $(INCLUDE_PROB)
$(OBJ_PROB)/bandwidth.o: $(SRC_PROB)/bandwidth.c $(INCLUDE_PROB)/process.h
	$(CC) $(CFLAGS) -o $(OBJ_PROB)/bandwidth.o -c $(SRC_PROB)/bandwidth.c -I $(INCLUDE_PROB)


$(BIN)/util: $(OBJ_CLI)/main.o $(OBJ_CLI)/send.o
	$(CC) -g -o $(BIN)/util $(OBJ_CLI)/main.o $(OBJ_CLI)/send.o
$(OBJ_CLI)/main.o: $(SRC_CLI)/main.c $(INCLUDE_CLI)/cli.h
	$(CC) $(CFLAGS) -o $(OBJ_CLI)/main.o -c $(SRC_CLI)/main.c -I $(INCLUDE_CLI)
$(OBJ_CLI)/send.o: $(SRC_CLI)/send.c $(INCLUDE_CLI)/cli.h
	$(CC) $(CFLAGS) -o $(OBJ_CLI)/send.o -c $(SRC_CLI)/send.c -I $(INCLUDE_CLI)

clean:
	rm $(OBJ_PROB)/*.o
	rm $(OBJ_CLI)/*.o
	rm $(BIN)/*

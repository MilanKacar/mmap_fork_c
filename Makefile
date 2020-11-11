CC     = gcc
CFLAGS = -g -Wall
BIN = user server
OBJ = 

all: $(BIN)

user: user.c
	$(CC) $(CFLAGS) -o user user.c -lrt

server: server.c
	$(CC) $(CFLAGS) -o server server.c -lrt

clean:
	rm -f $(OBJ)
	rm -f $(BIN)		

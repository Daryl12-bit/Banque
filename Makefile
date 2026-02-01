CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

TARGET = prog

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)

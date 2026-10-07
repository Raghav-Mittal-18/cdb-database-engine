CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRC = src/main.c \
      src/table.c \
      src/parser.c \
      src/executor.c \
      src/storage.c \
      src/record.c \
      src/database.c

TARGET = cdb

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

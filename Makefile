CC = gcc
CFLAGS = -Wextra -g
OBJ = linux.c functii-Arb.c
TARGET = linux

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f *.o $(TARGET) *~

valgrind:
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)


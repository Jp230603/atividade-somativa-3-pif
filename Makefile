CC      = gcc
CFLAGS  = -Wall -Wextra -I include
SRC     = main/main.c src/clientes.c
TARGET  = contas

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) contas.bin

.PHONY: all clean

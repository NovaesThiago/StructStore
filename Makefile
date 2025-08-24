# Nome do executável, é um compilador de arquivos para compilar digite no terminal: make
#para rodar digite: ./programa
TARGET = programa

# Lista de arquivos fonte
SRCS = main.c produtos.c ordenacao.c fila_espera.c fila_pedidos.c

# Gera lista de arquivos objeto automaticamente
OBJS = $(SRCS:.c=.o)

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Regra principal
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regra para compilar cada .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

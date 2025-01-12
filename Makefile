# Nome do executável
EXECUTABLE = programa

# Diretórios
SRC_DIR = implementacoes
HEADER_DIR = cabecalhos
BUILD_DIR = build

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(HEADER_DIR)

# Fontes e objetos
SOURCES = main.c $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SOURCES)))

# Regras principais
all: $(BUILD_DIR) $(EXECUTABLE)
	./$(EXECUTABLE)
	$(MAKE) clean
# Criação do executável
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Compilação dos arquivos .c para .o
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Criar diretório build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza dos arquivos gerados
clean:
	rm -f *.o
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

# Regra para executar o programa
run: $(EXECUTABLE)
	./$(EXECUTABLE)
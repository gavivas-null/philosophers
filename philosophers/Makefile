NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
INCLUDES = -I include

SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c) # esto hay que quitarlo antes de la corrección.
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# --------------------------------------------------------------
# 👇 Regla principal
# --------------------------------------------------------------
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "✅ Proyecto compilado correctamente."

# --------------------------------------------------------------
# 🛠 Compilar cada archivo fuente
# --------------------------------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null
	@echo "🔧 Compilado: $<"


# --------------------------------------------------------------
# 🧹 Limpieza
# --------------------------------------------------------------

clean:
	@rm -rf $(OBJ_DIR) > /dev/null
	@echo "🧹 Archivos objeto y temporales eliminados."

fclean: clean
	@rm -f $(NAME) > /dev/null
	@echo "🧼 Todo limpio."

re: fclean all

.PHONY: all clean fclean re
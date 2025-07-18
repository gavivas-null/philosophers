NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = 

OBJ = $(SRC:.c=.o)
INCLUDES = -I include

# --------------------------------------------------------------
# 👇 Regla principal
# --------------------------------------------------------------
all: $(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
			@echo "✅ Proyecto compilado correctamente."

# --------------------------------------------------------------
# 🛠 Compilar cada archivo fuente
# --------------------------------------------------------------
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null
	@echo "🔧 Compilado: $<"


# --------------------------------------------------------------
# 🧹 Limpieza
# --------------------------------------------------------------

clean:
	@rm -f $(OBJS) > /dev/null
	@echo "🧹 Archivos objeto y temporales eliminados."

fclean: clean
	@rm -f $(NAME) > /dev/null
	@echo "🧼 Todo limpio."

re: fclean all

.PHONY: all clean fclean re
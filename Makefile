NAME=philo/philo
CC=clang
CFLAGS=-Wall -Wextra -Werror -g -MMD

SRC_FILES=main.c \
		parse.c \
		simul.c \
		philos.c \
		utils.c
SRC_DIR=philo/src
SRC=$(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ_DIR=philo/obj
OBJ=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

DEP=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.d))

INC_FILES=philo.h
INC_DIR=philo/include
CFLAGS+=-I $(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -lpthread -o $(NAME)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re

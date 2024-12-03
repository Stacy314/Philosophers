NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread
SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = main.c  \
			utils.c  \
			utils2.c \
			simulation.c \
			philosopher.c \
			actions.c
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS =  $(OBJ_DIR)/main.o \
		$(OBJ_DIR)/simulation.o \
		$(OBJ_DIR)/philosopher.o \
		$(OBJ_DIR)/utils.o \
		$(OBJ_DIR)/utils2.o \
		$(OBJ_DIR)/actions.o  

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c philo.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
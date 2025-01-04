NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = main.c  \
			utils.c  \
			time.c \
			simulation.c \
			philosopher.c \
			actions.c \
			monitor.c \
			forks.c \
			clean.c \
			initialization.c \
			validation.c \
			conversion.c \
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS =  $(OBJ_DIR)/main.o \
		$(OBJ_DIR)/simulation.o \
		$(OBJ_DIR)/philosopher.o \
		$(OBJ_DIR)/utils.o \
		$(OBJ_DIR)/time.o \
		$(OBJ_DIR)/actions.o \
		$(OBJ_DIR)/monitor.o \
		$(OBJ_DIR)/forks.o \
		$(OBJ_DIR)/clean.o \
		$(OBJ_DIR)/initialization.o \
		$(OBJ_DIR)/validation.o \
		$(OBJ_DIR)/conversion.o \

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
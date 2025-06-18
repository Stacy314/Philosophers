################################################################################
#                                                                              #
#	                                Vars                                       #
#                                                                              #
################################################################################

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
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

SILENT = @

################################################################################
#                                                                              #
#	                                Rules                                      #
#                                                                              #
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	$(SILENT)$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "██████╗░██╗░░██╗██╗██╗░░░░░░█████╗░░██████╗░█████╗░██████╗░██╗░░██╗███████╗██████╗░░██████╗"
	@echo "██╔══██╗██║░░██║██║██║░░░░░██╔══██╗██╔════╝██╔══██╗██╔══██╗██║░░██║██╔════╝██╔══██╗██╔════╝"
	@echo "██████╔╝███████║██║██║░░░░░██║░░██║╚█████╗░██║░░██║██████╔╝███████║█████╗░░██████╔╝╚█████╗░"
	@echo "██╔═══╝░██╔══██║██║██║░░░░░██║░░██║░╚═══██╗██║░░██║██╔═══╝░██╔══██║██╔══╝░░██╔══██╗░╚═══██╗"
	@echo "██║░░░░░██║░░██║██║███████╗╚█████╔╝██████╔╝╚█████╔╝██║░░░░░██║░░██║███████╗██║░░██║██████╔╝"
	@echo "╚═╝░░░░░╚═╝░░╚═╝╚═╝╚══════╝░╚════╝░╚═════╝░░╚════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚═════╝░"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c philo.h | $(OBJ_DIR)
	$(SILENT)$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	$(SILENT)mkdir -p $(OBJ_DIR)

clean:
	$(SILENT)rm -rf $(OBJ_DIR)

fclean: clean
	$(SILENT)rm -f $(NAME)

re: fclean all
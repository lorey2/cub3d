# Compiler and flags
CC = cc
SRC_DIR = ./
OBJ_DIR = obj/
CFLAGS = -g -I/usr/include -Imlx_linux -O3 
#-Wall -Wextra -Werror
LDFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -Wall -Wextra -Werror

NAME = so_long

# Source and object files
SRC_FILES = main
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# Default target
all: $(NAME)

# Bonus target (same as all in this case)
bonus: all

# Linking the final executable
$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

# Rule for creating object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)   # Ensure object directory exists
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleaning up object files
clean:
	@rm -rf $(OBJ_DIR)

# Cleaning everything, including the executable
fclean: clean
	@rm -f $(NAME)

# Rebuilding everything from scratch
re: fclean all

.PHONY: all bonus clean fclean re

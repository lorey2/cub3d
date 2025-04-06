# Compiler and flags
CC = cc
SRC_DIR = src/
OBJ_DIR = obj/
CFLAGS = -g -I/usr/include -Imlx_linux -O3 -Wall -Wextra -Werror -I$(INCLUDE)
LDFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -Wall -Wextra -Werror
INCLUDE = include/

DEF_COLOR = \033[0;39m
GREEN     = \033[0;92m
YELLOW    = \033[0;93m
BLUE      = \033[0;94m
CYAN      = \033[0;96m

NAME = cub3d

# Source and object files
SRC_FILES = cub3d draw_utils hook setup_init utils draw_best_line 3d minimap exit
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# Default target
all: $(NAME)

# Bonus target (same as all in this case)
bonus: all

# Linking the final executable
$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)cub3d compiled!$(DEF_COLOR)"

# Rule for creating object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)   # Ensure object directory exists
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Compiling: $<$(DEF_COLOR)"

# Cleaning up object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(CYAN)cub3d objet files cleaned!$(DEF_COLOR)"

# Cleaning everything, including the executable
fclean: clean
	@rm -f $(NAME)
	@echo "$(CYAN)cub3d executables cleaned!$(DEF_COLOR)"

# Rebuilding everything from scratch
re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for cub3d!$(DEF_COLOR)"

.PHONY: all bonus clean fclean re

# Compiler and flags
CC = cc
SRC_DIR = src/
OBJ_DIR = obj/
CFLAGS = -g -I/usr/include -Imlx_linux -O3  -I$(INCLUDE) # -Wall -Wextra -Werror
LDFLAGS = -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -Wall -Wextra -Werror
INCLUDE = include/
MLX = $(MLX_DIR)/libmlx_Linux.a
MLX_DIR = ./mlx_linux
GNL_DIR = ./gnl

# LIBFT
LIBC_DIR = ./libft
LIBC = $(LIBC_DIR)/libft.a

DEF_COLOR = \033[0;39m
GREEN     = \033[0;92m
YELLOW    = \033[0;93m
BLUE      = \033[0;94m
CYAN      = \033[0;96m

NAME = cub3d

# Source and object files
SRC_FILES = cub3d draw_utils hook setup_init utils draw_best_line 3d minimap exit calcul_ray update_movement_angle parsing
GNL_FILES = get_next_line_bonus get_next_line_utils_bonus

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJ_GNL = $(addprefix $(OBJ_DIR)/gnl/, $(addsuffix .o, $(GNL_FILES)))

# Default target
all: $(NAME)

# Bonus target (same as all in this case)
bonus: all

$(LIBC):
	@make -s -C $(LIBC_DIR) all

# Linking the final executable
$(NAME): $(LIBC) $(OBJ) $(MLX) $(OBJ_GNL)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)cub3d compiled!$(DEF_COLOR)"

$(MLX):
	@make -C $(MLX_DIR) all

# Rule for creating object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)   # Ensure object directory exists
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Compiling: $<$(DEF_COLOR)"

$(OBJ_DIR)/gnl/%.o: $(GNL_DIR)%.c
	@mkdir -p $(OBJ_DIR)/gnl
	@echo "$(YELLOW)Compiling gnl: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Cleaning up object files
clean:
	@rm -rf $(OBJ_DIR)
	@make -s -C $(LIBC_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "$(CYAN)cub3d objet files cleaned!$(DEF_COLOR)"

# Cleaning everything, including the executable
fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBC_DIR) fclean
	@echo "$(CYAN)cub3d executables cleaned!$(DEF_COLOR)"

# Rebuilding everything from scratch
re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for cub3d!$(DEF_COLOR)"

.PHONY: all bonus clean fclean re

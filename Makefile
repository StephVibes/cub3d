# Project Name
NAME = cub3D

# Compiler and Flags
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

# Directories
INCLUDE_DIR = include
SRC_DIR = srcs
OBJ_DIR = objs
LIB_DIR = include/minilibx-linux
LIBFT_DIR = libft
LIB_DIR = include/minilibx-linux

# Files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/rendering/init.c \
       $(SRC_DIR)/rendering/events.c \
       $(SRC_DIR)/rendering/render.c \
       $(SRC_DIR)/rendering/draw.c \
       $(SRC_DIR)/parsing/read_file.c \
	   $(SRC_DIR)/parsing/parsing.c \
	   $(SRC_DIR)/parsing/player_init.c \
	   $(SRC_DIR)/parsing/validation.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


# Libraries and Frameworks
MLX = -L$(LIB_DIR) -lmlx -lXext -lX11 -lm
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(LIB_DIR)/libmlx.a
LIBS = $(MLX) $(LIBFT)


# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(OBJS) -o $(NAME) $(LIBS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(LIB_DIR)
	   
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/rendering
	@mkdir -p $(OBJ_DIR)/parsing
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


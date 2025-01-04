# Project Name
NAME = cub3d

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
INCLUDE_DIR = include
SRC_DIR = srcs
OBJ_DIR = objs
LIB_DIR = include/minilibx-linux
LIBFT_DIR = $(SRC_DIR)/libft

# Files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/image/init.c \
       $(SRC_DIR)/image/events.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


# Libraries and Frameworks
MLX = -L$(LIB_DIR) -lmlx -lXext -lX11
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = $(MLX) $(LIBFT)


# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(OBJS) -o $(NAME) $(LIBS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/image
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


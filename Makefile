CC					= cc
CFLAGS			=
PROGRAM			= cub3D
SRC_DIR			= src
CMD_DIR			= cmd
BUILD_DIR		= build
BIN_DIR			= $(BUILD_DIR)/bin
INC_DIR			= -Iinc -I$(MLX_DIR) -I$(LIBFT_DIR)
NAME				= $(BIN_DIR)/$(PROGRAM)
SRCS				= $(SRC_DIR)/err.c $(SRC_DIR)/init.c $(SRC_DIR)/init_texture.c $(SRC_DIR)/set_texture.c $(SRC_DIR)/str_utils.c \
						$(SRC_DIR)/control_map_items.c $(SRC_DIR)/control_map.c $(SRC_DIR)/helper.c $(SRC_DIR)/dispose.c \
						$(SRC_DIR)/start_game.c $(SRC_DIR)/raycasting.c $(SRC_DIR)/key_hook.c \
						$(SRC_DIR)/main_helper.c $(SRC_DIR)/init_texture_color.c $(SRC_DIR)/control_map2.c $(SRC_DIR)/map_h_fill.c \
						$(SRC_DIR)/draw_and_ray_cast.c $(SRC_DIR)/dispose_helper.c $(SRC_DIR)/set_texture_color.c \
						$(SRC_DIR)/game_utils.c $(SRC_DIR)/ray_utils.c



OBJS				= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
CMD					= $(CMD_DIR)/$(PROGRAM).c
RM					= rm -rf

MLX_DIR			= lib/libmlx
MLX					= $(MLX_DIR)/libmlx.a
MLX_FLAGS		= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

LIBFT_DIR		= lib/libft
LIBFT				= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

w = 1
ifeq '$(w)' '1'
CFLAGS += -Wextra -Werror -Wall
endif

debug = 1
ifeq '$(debug)' '1'
CFLAGS += -g
endif

asan = 0
ifeq '$(asan)' '1'
CFLAGS += -fsanitize=address -g
endif

all: $(MLX) $(LIBFT)
	@mkdir -p build/bin
	@$(MAKE) $(NAME)

$(NAME): $(CMD) $(OBJS) inc/cub3d.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $(MLX_FLAGS) $(LIBFT_FLAGS) $(CMD) $(OBJS) -o $(NAME)

$(MLX):
	@curl -O https://cdn.intra.42.fr/document/document/28881/minilibx_opengl.tgz

	@tar -xvf minilibx_opengl.tgz
	@mkdir -p $(MLX_DIR)
	@mv minilibx_opengl_20191021/* $(MLX_DIR)
	@$(RM) minilibx_opengl_20191021
	@$(RM) minilibx_opengl.tgz
	make -s -C $(MLX_DIR)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(LIBFT) & wait

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re

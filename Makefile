NAME		=	cub3D
NAME_BONUS	=	cub3D_bonus

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
DEPFLAGS	=	-MMD -MP
RM			=	rm -rf

SRC_DIR		=	src
OBJ_DIR		=	obj
OBJ_B_DIR	=	obj_bonus
INC_DIR		=	includes

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

# ---------------------------------------------------------------------------
# macOS (mlx_macos) vs Linux (mlx_linux = school machines + CI)
# ---------------------------------------------------------------------------
ifeq ($(shell uname -s), Darwin)
	MLX_DIR		=	mlx_macos
	MLX_FLAGS	=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	PLATFORM	=	platform/display_macos.c
else
	MLX_DIR		=	mlx_linux
	MLX_FLAGS	=	-L$(MLX_DIR) -lmlx -lXext -lX11
	PLATFORM	=	platform/display_linux.c
endif
MLX			=	$(MLX_DIR)/libmlx.a

INCLUDES	=	-I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		=	$(LIBFT) $(MLX_FLAGS) -lm

# ---------------------------------------------------------------------------
# Sources — one line per file, sorted by module.
# Add your new file HERE (no wildcard: forbidden at 42).
# ---------------------------------------------------------------------------
SRC_FILES	=	main.c \
				parsing/parse_scene.c \
				parsing/read_file.c \
				parsing/parse_elements.c \
				parsing/parse_color.c \
				parsing/parse_map.c \
				parsing/check_map.c \
				render/init_graphics.c \
				render/render_frame.c \
				render/raycast.c \
				render/draw_wall.c \
				render/pixel.c \
				game/init_player.c \
				game/hooks.c \
				game/movement.c \
				utils/error.c \
				utils/cleanup.c \
				utils/string_utils.c \
				$(PLATFORM)

# TODO (week 5, bonus issues): list the *_bonus.c files here.
# Until then the bonus binary is built from the mandatory sources.
SRC_BONUS_FILES	=	$(SRC_FILES)

SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
DEPS		=	$(OBJS:.o=.d)
OBJS_BONUS	=	$(addprefix $(OBJ_B_DIR)/, $(SRC_BONUS_FILES:.c=.o))
DEPS_BONUS	=	$(OBJS_BONUS:.o=.d)

# ---------------------------------------------------------------------------
# Rules
# ---------------------------------------------------------------------------
all:		$(NAME)

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus:		$(NAME_BONUS)

$(NAME_BONUS):	$(LIBFT) $(MLX) $(OBJS_BONUS)
			$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_B_DIR)/%.o:	$(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

$(MLX):
			$(MAKE) -C $(MLX_DIR) 2>/dev/null

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
			-$(MAKE) -C $(MLX_DIR) clean 2>/dev/null
			$(RM) $(OBJ_DIR) $(OBJ_B_DIR)

fclean:		clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME) $(NAME_BONUS)

re:			fclean all

# --- helpers (not required by the subject) --------------------------------
norm:
			norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_DIR)

test:		$(NAME)
			./tests/run_tests.sh

-include $(DEPS) $(DEPS_BONUS)

.PHONY:		all bonus clean fclean re norm test

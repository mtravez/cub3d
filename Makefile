NAME = cub3d
SRC = main.c parser/arr.c parser/input_data.c parser/parser.c parser/get_identifier.c parser/get_map.c parser/validate_map.c \
parser/check_player.c parser/set_color.c parser/set_textures.c parser/utils.c cub3d.c raycast.c math_utils.c raycast_utils.c drawing_rays.c

# CFLAGS      = -Wall -Wextra -Werror
CFLAGS      = -Wall -Wextra -Werror -fsanitize=address

SAN_LDFLAGS = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT = ./lib/libft/libft.a
MLX42 = ./lib/MLX42/libmlx42.a

GL_FLAGS = -lglfw -L "$(shell brew --prefix glfw)/lib/"

PINK = \033[1;95m
GREEN = \033[1;92m
RESET := \033[0m

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser

$(NAME): $(LIBFT) $(MLX42) $(OBJ_DIR) $(OBJ)
	@cc $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(GL_FLAGS) $(SAN_LDFLAGS) -o $(NAME)
	@printf "$(PINK)[Cub3d] Compiled successfuly!!! :D $(RESET)\n"

$(LIBFT):
	@make -C ./lib/libft

$(MLX42):
	@make -C ./lib/MLX42

$(OBJ_DIR)/%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

clean:
	@printf "$(GREEN)Cleaning cub3d$(RESET)\n"
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME) $(BONUS)
	@make fclean -C lib/libft
	@make fclean -C lib/MLX42

re: fclean all

.PHONY: all clean fclean re
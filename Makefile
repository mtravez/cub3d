NAME = cub3d
SRC = main.c arr.c input_data.c parser.c get_identifier.c get_map.c validate_map.c check_player.c utils.c
# SRC = cub3d.c raycast.c parser.c

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

$(NAME): $(LIBFT) $(MLX42) $(OBJ_DIR) $(OBJ)
	@cc $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(GL_FLAGS) -o $(NAME)
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
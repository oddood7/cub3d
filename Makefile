NAME		=	cub3d

CC			=	cc

FLAG		=	-Wall -Wextra -Werror

LIBFT_PATH	=	include/libft/

LIBFT_FILE	=	libft.a

MLX_FILE	=	libmlx.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX_FLAG	=	-lX11 -lXext

MLX_PATH	=	./minilibx-linux/

MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))

MLX_EX		=	$(MLX_LIB) $(MLX_FLAG)

C_FILE		=	parsing/parsing.c \
				parsing/parsingmap.c \
				parsing/drawing.c \
				parsing/graphic_utils.c \
				parsing/parsing_utils.c \
				parsing/colors.c \
				raycast/all.c \
				raycast/end.c \
				raycast/init_rc.c \
				raycast/keypress.c \
				raycast/movement.c \
				raycast/raycast.c \
				raycast/text_update.c \
				utils/get_next_line_utils.c \
				utils/get_next_line.c \
				utils/ft_lib.c \
				utils/ft_lib2.c \
				utils/utils.c \
				utils/utils2.c \
				utils/utils3.c \
				cub3d.c

SRC_DIR		=	./src/

INC_DIR		=	./include/

SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJ			=	$(SRC:.c=.o)

%.o: %.c
	$(CC) $(FLAG) -I$(INC_DIR) -c $< -o $@

all: lib mlx
	make $(NAME)

lib:
	@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)\n"
	@make -C $(LIBFT_PATH)
	@echo "\033[1;32mLIBFT_lib created\n"

mlx:
	@echo "\033[0;33m\nCOMPILING $(MLX_PATH)...\n"
	@make -sC $(MLX_PATH)
	@echo "\033[1;32mMLX_lib created\n"

$(NAME): $(OBJ)
	@echo "\033[0;33m\nCOMPILING CUB3D...\n"
	$(CC) $(FLAG) $(OBJ) $(LIBFT_LIB) $(MLX_EX) -lm -I$(INC_DIR) -o $(NAME)
	@echo "\033[1;32m./cub3d created\n"

bonus: all

clean:
	@echo "\033[0;31mDeleting Obj file in $(MLX_PATH)...\n"
	@make clean -sC $(MLX_PATH)
	@echo "\033[0;31mDeleting Obj file in $(LIBFT_PATH)...\n"
	@make clean -sC $(LIBFT_PATH)
	@echo "\033[1;32mDone\n"
	@echo "\033[0;31mDeleting cub3d object...\n"
	@rm -f $(OBJ)
	@echo "\033[1;32mDone\n"

fclean: clean
	@echo "\033[0;31mDeleting cub3d executable..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "\033[1;32mDone\n"

re: fclean
	make all

.PHONY: all clean fclean re

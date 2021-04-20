NAME = cub3D

SRCS =  ./parsing/check_map.c			\
		./parsing/check_map2.c			\
		./parsing/check_address.c		\
		./parsing/manage_cub.c			\
		./parsing/manage_errors.c		\
		./parsing/parsing.c				\
		./parsing/save_map.c			\
		./parsing/save_params.c			\
		./parsing/utils.c				\
		./raycasting/raycasting.c		\
		./raycasting/textures.c			\
		./raycasting/sprites.c			\
		./minilibx/minilibx_keys.c		\
		./minilibx/movement_keys.c		\
		./minilibx/draw.c				\
		./minilibx/draw_utils.c			\
		./minilibx/handle_hook.c		\
		./save/save.c					\
		./bonus/health.c				\
		./main.c


OBJS = $(SRCS:.c=.o)

CC  = gcc

FLAGS =   -L includes/minilibx-linux -lXext -lX11 -lm -lbsd
CFLAGS =  -Wall -Wextra -Werror
SAN = -g3 -fsanitize=address -O3
RM  = rm -f

BLACK		:= $(shell tput -Txterm setaf 0)
RED		:= $(shell tput -Txterm setaf 1)
GREEN		:= $(shell tput -Txterm setaf 2)
YELLOW		:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
PURPLE		:= $(shell tput -Txterm setaf 5)
BLUE		:= $(shell tput -Txterm setaf 6)
WHITE		:= $(shell tput -Txterm setaf 7)
RESET		:= $(shell tput -Txterm sgr0)

ifneq ("$(wildcard $(/libft/libft.a))","")
LIBFT_EXISTS = 1
else
LIBFT_EXISTS = 0
endif

ifneq ("$(wildcard $(/minilibx-linux/libmlx.a))","")
MLX_EXISTS = 1
else
MLX_EXISTS = 0
endif

$(NAME): $(OBJS)
	@echo "$(LIGHTPURPLE)Compilation...$(RESET)"
	if [ LIBFT_EXISTS=0 ]; then make -C libft; fi;
	@echo "$(PURPLE)Libft compiled$(RESET)"
	if [ MLX_EXISTS=0 ]; then make -C minilibx-linux; fi;
	@echo "$(PURPLE)Minilibx compiled$(RESET)"
	@(gcc -o $(NAME) -I include -I include/minilibx-linux $(SRCS) libft/libft.a minilibx-linux/libmlx.a $(FLAGS) $(CFLAGS))
	@echo "$(GREEN)Compilation OK$(RESET)"

all:  $(NAME)

clean:
	@echo "$(RED)Deleting objects$(RESET)"
	make clean -C libft
	make clean -C minilibx-linux
	@($(RM)	$(OBJS))

fclean:  clean
	@echo "$(RED)Deleting executables$(RESET)"
	@($(RM) $(NAME))

re: fclean all

san :
	@(gcc -o $(NAME) -I include -I include/minilibx-linux $(SRCS) libft/libft.a minilibx-linux/libmlx.a $(FLAGS) $(CFLAGS) $(SAN))

.PHONY: all clean fclean re

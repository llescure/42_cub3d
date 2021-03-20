# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llescure <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:33:15 by llescure          #+#    #+#              #
#    Updated: 2021/03/20 17:39:58 by llescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
		./minilibx/minilibx_keys.c		\
		./minilibx/draw.c				\
		./raycasting/raycasting.c		\
		./main.c


OBJS = $(SRCS:.c=.o)

CC  = gcc

FLAGS =   -L includes/minilibx-linux -lXext -lX11 -lm -lbsd
CFLAGS =  -Wall -Wextra -Werror
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

$(NAME): $(OBJS)
	@echo "$(LIGHTPURPLE)Compilation...$(RESET)"
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

lib:
	make -C libft
	make -C minilibx-linux

.PHONY: all clean fclean re

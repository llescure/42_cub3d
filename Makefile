# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llescure <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:33:15 by llescure          #+#    #+#              #
#    Updated: 2021/03/18 17:37:39 by llescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS =  ./parsing/check_map.c \
	./parsing/manage_cub.c \
	./parsing/manage_errors.c \
	./parsing/parsing.c \
	./parsing/save_map.c \
	./parsing/save_params.c \
	./parsing/utils.c \
	./minilibx/reading_image.c \

LIBFT_DIR = Libft

MLX_DIR = minilibx-linux

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I include -I minilibx-linux -I Libft

LIBS =  -L $(MLX_DIR) -L $(LIBFT_DIR) -lmlx -lXext -lX11 -lm -lz

RM = /bin/rm -f

all:	$(NAME)

$(NAME) : 	$(OBJS)
			make -C $(LIBFT_DIR)
			make -C $(MLX_DIR)
	$(CC) -o $(NAME) $(CFLAGS) $(LIBS) $(OBJS)

%.o : %.c $(HEADER)
			$(CC) -c $(CFLAGS) $< -o $@
clean:
		make clean -C $(LIBFT_DIR)
		make clean -C $(MLX_DIR)
		$(RM) $(OBJS)

fclean: clean
		make fclean -C $(LIBFT_DIR)
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

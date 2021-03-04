# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llescure <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:33:15 by llescure          #+#    #+#              #
#    Updated: 2021/03/04 12:07:33 by llescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D.a

SRCS =  parsing/check_map.c \
		parsing/manage_cub.c \
		parsing/manage_errors.c \
		parsing/parsing.c \
		parsing/save_map.c \
		parsing/save_params.c \
		parsing/utils.c \

SUBDIR = libft

LIBRARY = libft.a

HEADER = cub3D.h

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Imlx -c

RM = /bin/rm -f

all:	$(NAME)

$(NAME) : $(OBJS)
			make -C $(SUBDIR)
			cp ${SUBDIR}/${LIBRARY} ${NAME}
			ar rcs $(NAME) $(OBJS)

%.o : %.c $(HEADER)
			$(CC) -c $(CFLAGS) $< -o $@

clean:
		make fclean -C $(SUBDIR)
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

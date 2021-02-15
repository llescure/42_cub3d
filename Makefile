# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llescure <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:33:15 by llescure          #+#    #+#              #
#    Updated: 2021/02/10 12:36:06 by llescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D.a

SRCS =  \

SUBDIR = libft

LIBRARY = libft.a

HEADER = cub3D.h

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

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

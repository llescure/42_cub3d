# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llescure <llescure@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 17:55:58 by llescure          #+#    #+#              #
#    Updated: 2021/05/03 15:21:50 by llescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_memset.c			\
	  	ft_bzero.c		\
	  	ft_memcpy.c		\
	  	ft_memccpy.c		\
	  	ft_memmove.c		\
	  	ft_memchr.c		\
	  	ft_memcmp.c		\
	  	ft_strlen.c		\
	  	ft_isalpha.c		\
	  	ft_isdigit.c		\
	  	ft_isalnum.c		\
	  	ft_isascii.c		\
	  	ft_isprint.c		\
	  	ft_toupper.c		\
	  	ft_tolower.c		\
	  	ft_strchr.c		\
	  	ft_strrchr.c		\
	  	ft_strncmp.c		\
	  	ft_strlcpy.c		\
	  	ft_strlcat.c		\
	  	ft_strnstr.c		\
	  	ft_atoi.c		\
	  	ft_calloc.c		\
	  	ft_strdup.c		\
	  	ft_substr.c		\
	  	ft_strjoin.c		\
	  	ft_strtrim.c		\
	  	ft_split.c		\
	  	ft_itoa.c		\
	  	ft_strmapi.c		\
	 	ft_putchar_fd.c		\
	  	ft_putstr_fd.c		\
	  	ft_putendl_fd.c		\
	  	ft_putnbr_fd.c		\
		get_next_line.c		\
		get_next_line_utils.c	\

BONUS = ft_lstnew.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_front.c \
		ft_lstdelone.c \
		ft_lstadd_back.c \
		ft_lstiter.c \
		ft_lstclear.c \
		ft_lstmap.c \

HEADER = libft.h

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = /bin/rm -f

ifdef WITH_BONUS
ALL_OBJS = $(OBJS) $(BONUS_OBJS)
else
ALL_OBJS = $(OBJS)
endif

all:	 $(NAME)

$(NAME) : $(ALL_OBJS)
			ar rcs $(NAME) $(ALL_OBJS)

%.o : %.c $(HEADER)
			$(CC)  -c $(CFLAGS) $< -o $@

clean:
		$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

bonus : 
	$(MAKE) WITH_BONUS=1 all

.PHONY: all clean fclean re bonus

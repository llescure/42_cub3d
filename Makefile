# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llescure <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 12:33:15 by llescure          #+#    #+#              #
#    Updated: 2021/03/19 14:31:39 by llescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CUB = cub3D.cub

SRCS =  ./parsing/check_map.c			\
		./parsing/check_map2.c			\
		./parsing/check_address.c		\
		./parsing/manage_cub.c			\
		./parsing/manage_errors.c		\
		./parsing/parsing.c				\
		./parsing/save_map.c			\
		./parsing/save_params.c			\
		./parsing/utils.c				\
		./minilibx/reading_image.c		\
		./raycasting/raycasting.c

OBJS = ${SRCS:.c=.o}

CC  = gcc

FLAGS =   -L includes/minilibx-linux -lXext -lX11 -lm -lbsd
CFLAGS =  -Wall -Wextra -Werror
RM  = rm -f

BLACK		:= $(shell tput -Txterm setaf 0)
RED			:= $(shell tput -Txterm setaf 1)
GREEN		:= $(shell tput -Txterm setaf 2)
YELLOW		:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
PURPLE		:= $(shell tput -Txterm setaf 5)
BLUE		:= $(shell tput -Txterm setaf 6)
WHITE		:= $(shell tput -Txterm setaf 7)
RESET		:= $(shell tput -Txterm sgr0)

$(NAME):
	@echo "${YELLOW}Compilation...${RESET}"
	@(gcc -o ${NAME} -I include -I include/minilibx-linux ${SRCS} libft/libft.a minilibx-linux/libmlx.a ${FLAGS} ${CFLAGS})
	@echo "${GREEN}Compilation OK${RESET}"

all:  ${NAME}

clean:
	@echo "${RED}deleting ojbects${RESET}"
	@(${RM}	${OBJS})

fclean:  clean
	@echo "${RED}deleting executable${RESET}"
	@(${RM} ${NAME})

re: fclean all clean

lib:
	make -C libft
	make -C minilibx-linux

exe: re
	@echo "${YELLOW}Execution${RESET}"
	@(./${NAME} ${CUB})
	@echo "${GREEN}Programm Closed${RESET}"
	@(rm ${NAME})

screen: re
	@echo "${YELLOW}Execution${RESET}"
	@(./${NAME} ${CUB} --save)
	@echo "${GREEN}Programm Closed${RESET}"
	@(rm ${NAME})

bonus: re

help:
	@echo "${RED}===MAKFILE of Cub3D 42 project===${RESET}\n"
	@echo "${BLUE}all :${RESET} be the default value. Just compile SRCS in NAME."
	@echo "${BLUE}clean :${RESET} delete all objects files."
	@echo "${BLUE}fclean :${RESET} delete the executable NAME. he use clean"
	@echo "${BLUE}re :${RESET} compile the lasted version of the files OBJS in NAME. He use fclean and all."
	@echo "${BLUE}exe :${RESET} compile the lastead version of the files OBJS in NAME and execute the programm. He use re"


.PHONY: all clean fclean re exe help

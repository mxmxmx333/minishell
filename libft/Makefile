# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 12:08:46 by mbonengl          #+#    #+#              #
#    Updated: 2024/09/18 15:07:52 by mbonengl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS		:= -I$(INC_DIR)/libft.h -I./inc -Wall -Wextra -Werror
CC			:= cc
LIBC		:= ar rcs
RM			:= rm -f
NAME		:= libft.a
OBJ_DIR		:= ./obj
SRC_DIR		:= ./src
INC_DIR		:= ./inc
SRC 		:= 	$(SRC_DIR)/ft_atoi.c \
				$(SRC_DIR)/ft_bzero.c \
				$(SRC_DIR)/ft_calloc.c \
				$(SRC_DIR)/ft_countwords.c \
				$(SRC_DIR)/ft_isalnum.c \
				$(SRC_DIR)/ft_isalpha.c \
				$(SRC_DIR)/ft_isascii.c \
				$(SRC_DIR)/ft_isdigit.c \
				$(SRC_DIR)/ft_isprint.c \
				$(SRC_DIR)/ft_itoa.c \
				$(SRC_DIR)/ft_memchr.c \
				$(SRC_DIR)/ft_memcmp.c \
				$(SRC_DIR)/ft_memcpy.c \
				$(SRC_DIR)/ft_memmove.c \
				$(SRC_DIR)/ft_memset.c \
				$(SRC_DIR)/ft_putchar_fd.c \
				$(SRC_DIR)/ft_putendl_fd.c \
				$(SRC_DIR)/ft_putnbr_fd.c \
				$(SRC_DIR)/ft_putstr_fd.c \
				$(SRC_DIR)/ft_split.c \
				$(SRC_DIR)/ft_strchr.c \
				$(SRC_DIR)/ft_strdup.c \
				$(SRC_DIR)/ft_strndup.c \
				$(SRC_DIR)/ft_striteri.c \
				$(SRC_DIR)/ft_strjoin.c \
				$(SRC_DIR)/ft_strlcat.c \
				$(SRC_DIR)/ft_strlcpy.c \
				$(SRC_DIR)/ft_strlen.c \
				$(SRC_DIR)/ft_strmapi.c \
				$(SRC_DIR)/ft_strcmp.c \
				$(SRC_DIR)/ft_strncmp.c \
				$(SRC_DIR)/ft_strnstr.c \
				$(SRC_DIR)/ft_strrchr.c \
				$(SRC_DIR)/ft_strtrim.c \
				$(SRC_DIR)/ft_substr.c \
				$(SRC_DIR)/ft_tolower.c \
				$(SRC_DIR)/ft_toupper.c \
				$(SRC_DIR)/get_next_line.c \
				$(SRC_DIR)/get_next_line_utils.c \
				$(SRC_DIR)/empty_white.c \
				$(SRC_DIR)/ft_free.c

OBJ 		:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: ${NAME}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	${CC} ${CFLAGS} -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

${NAME}: ${OBJ}
	${LIBC} ${NAME} ${OBJ}

fclean: clean
	${RM} ${NAME}

clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re

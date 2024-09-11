# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonengl <mbonengl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 10:57:59 by mbonengl          #+#    #+#              #
#    Updated: 2024/09/11 08:27:41 by mbonengl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name 		:= 	minishell
CFLAGS 		:= 	-I./inc -I./libft/inc -Wall -Wextra -Werror
BFLAGS		:= 	-I./bonus/inc
LDFLAGS		:= 	-L./libft -lft
CC 			:= 	cc
SRC_DIR 	:= 	./src
OBJ_DIR 	:= 	./obj
INC_DIR 	:= 	./inc
BONUS_DIR	:= 	./bonus
B_INC_DIR	:= 	./bonus/inc
B_SRC_DIR	:= 	./bonus/src
B_OBJ_DIR	:= 	./bonus/obj
LIBFT_DIR	:= 	./libft
LIBFT		:= 	$(LIBFT_DIR)/libft.a
SRC 		:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/exe/exe.c \
				$(SRC_DIR)/lex/lex.c \
				$(SRC_DIR)/pars/pars.c
BSRC		:=	$(B_SRC_DIR)/main_bonus.c \

OBJ 		:= 	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BOBJ		:=	$(BSRC:$(B_SRC_DIR)/%.c=$(B_OBJ_DIR)/%.o)

all: $(Name)

$(Name): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(Name) $(OBJ) $(LDFLAGS)

bonus: $(BOBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BFLAGS) -o $(Name) $(BOBJ) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(B_OBJ_DIR)/%.o: $(B_SRC_DIR)/%.c | $(B_OBJ_DIR)
	$(CC) $(CFLAGS) $(BFLAGS) -c $< -o $@

$(B_OBJ_DIR):
	mkdir -p $(B_OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ) $(BOBJ)
	rm -rf $(OBJ_DIR) $(B_OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(Name)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

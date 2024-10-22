# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonengl <mbonengl@student.42vienna.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 10:57:59 by mbonengl          #+#    #+#              #
#    Updated: 2024/09/19 12:32:49 by mbonengl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name 		:= 	minishell
CFLAGS 		:= 	-g -I./inc -I./libft/inc -Wall -Wextra -Werror
BFLAGS		:= 	-I./bonus/inc
LDFLAGS		:= 	-L./libft -lft -lreadline
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
				$(SRC_DIR)/interface.c \
				$(SRC_DIR)/initialization/initialization.c \
				$(SRC_DIR)/initialization/environment.c \
				$(SRC_DIR)/execution/convert_export.c \
				$(SRC_DIR)/execution/paths.c \
				$(SRC_DIR)/execution/execution.c \
				$(SRC_DIR)/execution/pathfinder.c \
				$(SRC_DIR)/execution/wrappers_exec.c \
				$(SRC_DIR)/execution/wrappers_open.c \
				$(SRC_DIR)/execution/close_pipes.c \
				$(SRC_DIR)/execution/conditions.c \
				$(SRC_DIR)/execution/execute_command.c \
				$(SRC_DIR)/execution/redirections.c \
				$(SRC_DIR)/errors/error_msg.c \
				$(SRC_DIR)/errors/syntax_error.c \
				$(SRC_DIR)/memory/destruction.c \
				$(SRC_DIR)/lexer/interpreting_utils.c \
				$(SRC_DIR)/lexer/token_list_utils.c \
				$(SRC_DIR)/lexer/tokenizing.c \
				$(SRC_DIR)/lexer/tok_redirection.c \
				$(SRC_DIR)/lexer/token_refining.c \
				$(SRC_DIR)/lexer/lexer.c \
				$(SRC_DIR)/expander/expander.c \
				$(SRC_DIR)/expander/expander_utils.c \
				$(SRC_DIR)/expander/get_length.c \
				$(SRC_DIR)/parser/destroy_executables.c \
				$(SRC_DIR)/parser/parser.c \
				$(SRC_DIR)/parser/words_and_rest.c \
				$(SRC_DIR)/parser/executable.c \
				$(SRC_DIR)/parser/executable_utils.c \
				$(SRC_DIR)/console/console.c \
				$(SRC_DIR)/console/get_hostname.c \
				$(SRC_DIR)/console/history.c \
				$(SRC_DIR)/signal/signal.c \
				$(SRC_DIR)/printing/printing.c \
				$(SRC_DIR)/builtins/echo.c \
				$(SRC_DIR)/builtins/cd.c \
				$(SRC_DIR)/testing/test_echo.c
OBJ 		:= 	$(SRC:.c=.o)

all: $(Name)

$(Name): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(Name) $(OBJ) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

.c.o:		
	$(CC) $(CFLAGS) -c $< -o $@

$(B_OBJ_DIR):
	mkdir -p $(B_OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

myclean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(Name)
	make -C $(LIBFT_DIR) fclean

re: fclean all

my: all myclean

.PHONY: all clean fclean re bonus my myclean

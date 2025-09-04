# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 20:00:00 by skimura           #+#    #+#              #
#    Updated: 2025/09/04 19:51:29 by skimura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRC			= \
                main.c \
                utils.c \
                parse.c \
                init_table.c \
                init_philo.c \
                dining.c \
                monitoring.c \
                routine.c \
                action.c \

OBJ_DIR		= obj

OBJS		= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
#CFLAGS		+= -g -O1 -fsanitize=thread
#CFLAGS		+= -g -O1 -fsanitize=address
#setarch $(uname -m) -R ./philo
#valgrind --tool=helgrind
RM			= rm -f
MAKEFLAGS	+= --no-print-directory

RESET	= \033[0m
BOLD	= \033[1m
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
CYAN	= \033[0;36m
WHITE	= \033[0;37m
MAGENTA	= \033[0;35m

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@echo  "$(BOLD)$(GREEN)[INFO]$(CYAN) Building $(WHITE)$(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[OK]$(BLUE) Build completed!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo  "$(BOLD)$(YELLOW)[INFO]$(MAGENTA) Cleaning $(NAME)..."
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_DIR) 2>/dev/null || true
	@echo "$(RED)[DONE]$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BOLD)$(YELLOW)[DELETE]$(RED)All clean $(NAME)$(RESET)"

re: fclean all

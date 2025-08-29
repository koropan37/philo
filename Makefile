# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 21:24:00 by skimura           #+#    #+#              #
#    Updated: 2025/08/28 18:09:05 by skimura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= philo
BONUS_NAME	= philo_bonus

SRC			= \
				src/main.c \
				src/utils.c \
				src/parse.c \
				src/init_table.c \
				src/init_philo.c \
				src/dining.c \
				src/monitoring.c \
				src/routine.c \
				src/action.c \

BONUS_SRC	= \
				bonus/main_bonus.c \
				bonus/utils_bonus.c \
				bonus/parse_bonus.c \
				bonus/init_table_bonus.c \
				bonus/init_philo_bonus.c \
				bonus/dining_bonus.c \
				bonus/monitoring_bonus.c \
				bonus/routine_bonus.c \
				bonus/action_bonus.c \
				bonus/cleanup_bonus.c \

OBJ_DIR		= obj
BONUS_DIR 	= obj_bonus
INC_DIR	 	= include

OBJS		= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
BONUS_OBJS	= $(addprefix $(BONUS_DIR)/, $(notdir $(BONUS_SRC:.c=.o)))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS		+= -g -O1 -fsanitize=thread
#CFLAGS		+= -g -O1 -fsanitize=address
#setarch $(uname -m) -R ./philo
#valgrind --tool=helgrind
RM			= rm -f
INCLUDES	= -I$(INC_DIR)
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




.PHONY: all bonus clean fclean re


all: $(OBJ_DIR) $(NAME)


bonus: $(BONUS_DIR) $(BONUS_OBJS)
	@echo  "$(BOLD)$(GREEN)[INFO]$(CYAN) Building $(WHITE)$(BONUS_NAME)..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS)  -o $(BONUS_NAME)
	@echo "$(GREEN)[OK]$(BLUE) Bonus build completed!$(RESET)"



$(NAME): $(OBJS)
	@echo  "$(BOLD)$(GREEN)[INFO]$(CYAN) Building $(WHITE)$(NAME)..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[OK]$(BLUE) Build completed!$(RESET)"


$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_DIR)/%.o: bonus/%.c
	@mkdir -p $(BONUS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BONUS_DIR):
	@mkdir -p $(BONUS_DIR)


clean:
	@echo  "$(BOLD)$(YELLOW)[INFO]$(MAGENTA) Cleaning $(NAME)..."
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@$(RM) -r $(OBJ_DIR) $(BONUS_DIR) 2>/dev/null || true
	@echo "$(RED)[DONE]$(RESET)"

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(BOLD)$(YELLOW)[DELETE]$(RED)All clean $(NAME) and $(BONUS_NAME)$(RESET)"

re: fclean all

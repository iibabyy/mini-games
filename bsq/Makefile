# Colors
BLACK	= $(shell tput -Txterm setaf 0)
RED		= $(shell tput -Txterm setaf 1)
GREEN	= $(shell tput -Txterm setaf 2)
YELLOW	= $(shell tput -Txterm setaf 3)
BLUE	= $(shell tput -Txterm setaf 6)
WHITE	= $(shell tput -Txterm setaf 7)
END		= $(shell tput -Txterm sgr0)

# Program name and paths
NAME	= bsq
LIBFT	= libft/libft.a

# Source files
SRCS_DIR	= srcs/
SRCS	= $(SRCS_DIR)bsq.c

# Object files
OBJS_DIR = .objs/
OBJS	= $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 -pg
INCLUDE	= -Iincludes -Ilibft

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(BLUE)BSQ compiled successfully ✅$(END)"

$(LIBFT):
	@make -sC libft

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -sC libft
	@echo "$(YELLOW)Object files cleaned$(END)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC libft
	@echo "$(RED)Executables cleaned$(END)"

re: fclean all

.PHONY: all clean fclean re

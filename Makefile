# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javiersa <javiersa@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 18:02:29 by javiersa          #+#    #+#              #
#    Updated: 2023/10/26 11:34:52 by javiersa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# General variables
NAME = cub3D.a
PROGRAM = cub3D
CFLAGS = -Wall -Werror -Wextra
PERSONALNAME = Cub3D
LIBFTPLUS = libftplus
LIBFTPLUS_LIB = $(LIBFTPLUS)/libftplus.a
MLX42 = MLX42
MLX_LIB = MLX42/libmlx42.a
MLX_FLAGS = -lm -I include -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
CC = gcc
CLEAN = rm -Rf
SRC = $(wildcard src/*.c src/parse/*.c src/hooks/*.c src/utils/*.c src/picasso/*.c)
OBJS := $(SRC:.c=.o)

# Personal use variables
PARAMS = maps/minimalist.cub
DATETIME := $(shell date +%Y-%m-%d' '%H:%M:%S)
GIT_BRANCH := $(shell git rev-parse --abbrev-ref HEAD)
USER := $(shell whoami)
GITIGNORE = .gitignore

# General rules

all: $(PROGRAM)


$(PROGRAM): $(LIBFTPLUS_LIB) $(MLX_LIB) $(NAME)
	@$(CC) $(CFLAGS) $(NAME) $(LIBFTPLUS_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(PROGRAM)
	@echo "$(MAGENTA)Program $(PERSONALNAME) created successfully.$(DEFAULT)"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	@echo "$(GREEN)Compiling:$(DEFAULT) $(notdir $<)"
	
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(MAGENTA)Library $(NAME) created successfully.$(DEFAULT)"
clean: libftplusclean mlx42clean mlx42fclean
	@$(CLEAN) ./$(OBJS)
	@echo "$(RED)Removing:$(DEFAULT) All objects from $(PERSONALNAME)."
fclean: libftplusfclean mlx42fclean clean
	@$(CLEAN) ./$(NAME) ./$(PROGRAM)
	@echo "$(RED)Removing:$(DEFAULT) Library $(NAME)."
	@echo "$(RED)Removing:$(DEFAULT) Program $(PROGRAM)."
re: fclean all

# Lib rules

$(LIBFTPLUS_LIB): libftplusmake

libftplusmake:
	@make -C $(LIBFTPLUS)
libftplusclean:
	@make clean -C $(LIBFTPLUS)
libftplusfclean:
	@make fclean -C $(LIBFTPLUS)
libftplusre: libftplusclean libftplusmake

$(MLX_LIB):
	@make -C $(MLX42)
	@echo "$(MAGENTA)Library $(MLX_LIB) created successfully.$(DEFAULT)"
mlx42clean:
	@make clean -C $(MLX42)
mlx42fclean:
	@make fclean -C $(MLX42)
mlx42re: libftplusclean libftplusmake

#Personal use
git: fclean $(GITIGNORE)
	@git add *
	@echo "$(BOLD)$(YELLOW)Git ($(GIT_BRANCH)):$(WHITE) Adding all archives.$(DEFAULT)"
	@git commit -m "[$(DATETIME)] - Little changes by $(USER)"
	@echo "$(BOLD)$(CYAN)Git ($(GIT_BRANCH)):$(WHITE) Commit this changes in brunch\
	 $(GIT_BRANCH) with "[$(DATETIME)] - Little changes by $(USER)".$(DEFAULT)"
	@git push --set-upstream origin $(GIT_BRANCH)
	@echo "$(BOLD)$(GREEN)Git ($(GIT_BRANCH)):$(WHITE) Pushing all changes.$(DEFAULT)"
submodules:
	@git submodule update --init --recursive
	@echo "$(GREEN)The submodules have been created and updated successfully.$(DEFAULT)"
$(GITIGNORE):
	@echo ".*\n*.out\n*.o\n*.a\n*.dSYM">.gitignore
	@echo "$(GREEN)Creating:$(DEFAULT) Gitignore."
42prepare: submodules
	@rm -rf .git*
	@echo "$(GREEN)All .git removed.$(DEFAULT)"
valgrind_datarace: $(PROGRAM)
	valgrind --tool="helgrind" ./$(PROGRAM) $(PARAMS)
valgrind_leaks: $(PROGRAM)
	valgrind --leak-check=full -s ./$(PROGRAM) $(PARAMS)

#COLORS
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
DEFAULT	:= \033[0m

.PHONY : all clean fclean re \
libftplusmake libftplusclean libftplusfclean libftplusre \
git submodules gitignore 42prepare valgrind_datarace valgrind_leaks

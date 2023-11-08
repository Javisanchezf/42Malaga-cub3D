# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 18:02:29 by javiersa          #+#    #+#              #
#    Updated: 2023/11/08 20:10:00 by antdelga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# General variables
NAME = cub3D.a
NAME_BONUS = cub3D_bonus.a
PROGRAM = cub3D
PROGRAM_BONUS = cub3D_bonus
CFLAGS = -Wall -Werror -Wextra
PERSONALNAME = Cub3D
LIBFTPLUS = libftplus
LIBFTPLUS_LIB = $(LIBFTPLUS)/libftplus.a
MLX42 = MLX42
MLX_LIB = MLX42/libmlx42.a
MLX_FLAGS = -lm -I include -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
CC = gcc
CLEAN = rm -Rf
SRC = 	src/picasso/draw_raycasting.c \
		src/main.c \
		src/parse/map_parse.c \
		src/parse/map_construct.c \
		src/parse/ids_parse.c \
		src/parse/general_parse.c \
		src/utils/cleaner.c \
		src/utils/init.c \
		src/utils/utils_dynamics.c \
		src/utils/utils_img.c \
		src/picasso/draw_minimap.c \
		src/picasso/draw_ufo_rays.c \
		src/hooks/cursor_hooks.c \
		src/hooks/keyboard_hooks.c \
		src/hooks/time_hooks.c


SRC_BONUS = src_bonus/picasso/draw_raycasting_bonus.c \
		src_bonus/main_bonus.c \
		src_bonus/parse/map_parse_bonus.c \
		src_bonus/parse/map_construct_bonus.c \
		src_bonus/parse/ids_parse_bonus.c \
		src_bonus/parse/general_parse_bonus.c \
		src_bonus/utils/cleaner_bonus.c \
		src_bonus/utils/init_bonus.c \
		src_bonus/utils/utils_dynamics_bonus.c \
		src_bonus/utils/utils_img_bonus.c \
		src_bonus/picasso/draw_minimap_bonus.c \
		src_bonus/picasso/draw_ufo_rays_bonus.c \
		src_bonus/hooks/cursor_hooks_bonus.c \
		src_bonus/hooks/keyboard_hooks_bonus.c \
		src_bonus/hooks/time_hooks_bonus.c
		
OBJS := $(SRC:.c=.o)

OBJS_BONUS := $(SRC_BONUS:.c=.o)

# Personal use variables
PARAMS = maps/minimalist.cub
DATETIME := $(shell date +%Y-%m-%d' '%H:%M:%S)
GIT_BRANCH := $(shell git rev-parse --abbrev-ref HEAD)
USER := $(shell whoami)
GITIGNORE = .gitignore

# General rules

all: $(PROGRAM)

bonus: $(PROGRAM_BONUS)


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
	@$(CLEAN) ./$(OBJS) $(OBJS_BONUS) ./$(NAME_BONUS) ./$(NAME)
	@echo "$(RED)Removing:$(DEFAULT) All objects from $(PERSONALNAME)."
	@echo "$(RED)Removing:$(DEFAULT) Library $(NAME)."
	@echo "$(RED)Removing:$(DEFAULT) Library $(NAME_BONUS)."
fclean: libftplusfclean mlx42fclean clean
	@$(CLEAN) ./$(PROGRAM) ./$(PROGRAM_BONUS)
	@echo "$(RED)Removing:$(DEFAULT) Program $(PROGRAM)."
	@echo "$(RED)Removing:$(DEFAULT) Program $(PROGRAM_BONUS)."
re: fclean all

# Lib rules
$(PROGRAM_BONUS): $(LIBFTPLUS_LIB) $(MLX_LIB) $(NAME_BONUS)
	@$(CC) $(CFLAGS) $(NAME_BONUS) $(LIBFTPLUS_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(PROGRAM_BONUS)
	@echo "$(MAGENTA)Program $(PERSONALNAME) created successfully.$(DEFAULT)"

$(NAME_BONUS): $(OBJS_BONUS)
	@ar rcs $(NAME_BONUS) $(OBJS_BONUS)
	@echo "$(MAGENTA)Library $(NAME_BONUS) created successfully.$(DEFAULT)"

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

.PHONY : all clean fclean re bonus-\
libftplusmake libftplusclean libftplusfclean libftplusre \
git submodules gitignore 42prepare valgrind_datarace valgrind_leaks

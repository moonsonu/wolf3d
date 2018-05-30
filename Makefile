# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/29 17:16:50 by ksonu             #+#    #+#              #
#    Updated: 2018/05/29 17:16:56 by ksonu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 
OBJ = $(SRC:.c=.o)
MLX = -L $(MLXDIR) -lmlx -framework OpenGL -framework Appkit

SRCDIR = srcs
OBJDIR = objs
LIBDIR = libs/libft
MLXDIR = libs/mlx

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))
LIBS = -L $(LIBDIR) -lft $(MLX)
HEADER = -I includes -I $(LIBDIR)/includes -I $(MLXDIR)

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

NAME = wolf3d

.PHONY: all clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADER) $< -o $@

$(NAME): $(OBJS)
	@make -C $(MLXDIR)
	@make -C $(LIBDIR)
	@$(CC) $(OBJS) $(LIBS) -o $@
	@echo "\x1b[32;1m[나는 예쁘다!😘]\x1b[0m"

clean:
	@/bin/rm -rf $(OBJDIR)
	@make -C $(MLXDIR) clean
	@make -C $(LIBDIR) clean
	@echo "\x1b[35;1m[아니다!]\x1b[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@rm -f $(LIBDIR)/libft.a
	@echo "\x1b[31m[못났다!]\x1b[0m"

re: fclean all

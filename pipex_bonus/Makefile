# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnantaki <tnantaki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 11:35:05 by tnantaki          #+#    #+#              #
#    Updated: 2023/02/03 17:37:09 by tnantaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#setup
NAME	= pipex
CC		= gcc
FLAGS	= -Wall -Werror -Wextra
RM		= rm -f

#path
LIBFT_PATH	= libft/
GNL_PATH	= get_next_line/
BONUS_PATH	= bonus/
MANDA_PATH	= mandatory/

#srcs
MANDA_SRCS	= ft_pipex.c ft_utils.c

BONUS_SRCS	= ft_pipex_bonus.c ft_utils_bonus.c ft_create_pipe_bonus.c ft_setup_bonus.c ft_setcmd_bonus.c

LIBFT_SRCS	= ft_strlen.c ft_strjoin.c ft_strjoinfree.c ft_strtrim.c\
			ft_split.c ft_putstr_fd.c ft_putendl_fd.c ft_strncmp.c

GNL_SRCS	= get_next_line.c get_next_line_utils.c

#all_src
SRCS	= $(addprefix $(MANDA_PATH), $(MANDA_SRCS))\
		$(addprefix $(LIBFT_PATH), $(LIBFT_SRCS))

B_SRCS	= $(addprefix $(BONUS_PATH), $(BONUS_SRCS))\
		$(addprefix $(LIBFT_PATH), $(LIBFT_SRCS))\
		$(addprefix $(GNL_PATH), $(GNL_SRCS))

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(B_SRCS:.c=.o)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_OBJS)
	$(CC) $(FLAGS) $(BONUS_OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re

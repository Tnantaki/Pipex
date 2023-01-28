# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnantaki <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 11:35:05 by tnantaki          #+#    #+#              #
#    Updated: 2022/09/22 12:30:19 by tnantaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

FLAGS = -Wall -Werror -Wextra

RM = rm -f

LIBFT_PATH = libft/

PIPE_SRCS = ft_pipex.c ft_utils.c

LIBFT_SRCS = ft_strlen.c ft_strjoin.c ft_strjoinfree.c\
			 ft_strtrim.c ft_split.c ft_putstr_fd.c

#SRCS = ft_pipex.c ft_utils.c\

SRCS = $(PIPE_SRCS)\
	   $(addprefix $(LIBFT_PATH), $(LIBFT_SRCS))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re

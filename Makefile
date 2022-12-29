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

FLAGS = -Wall -Werror -Wextra
NAME = pipex

LIBFT_SRCS = ft_strlen.c ft_strjoin.c ft_strjoinfree.c\
			 ft_strtrim.c ft_split.c ft_putstr_fd.c
LIBFT_PATH = libft/
SRCS = ft_pipex.c ft_utils.c\
	   $(addprefix $(LIBFT_PATH), $(LIBFT_SRCS))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re

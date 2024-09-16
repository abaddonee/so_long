# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: likiffel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 03:09:08 by likiffel          #+#    #+#              #
#    Updated: 2024/04/25 03:11:57 by likiffel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= so_long.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

NAME			= so_long

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)	

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@


clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re

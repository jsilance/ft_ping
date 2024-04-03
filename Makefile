# ============================================================================= #
                                                      
NAME		= ft_ping

# ============================================================================= #

SRCS		= main.c ft_strcmp.c ft_bzero.c init.c ft_error.c ft_ping.c \
				parsing.c ft_strlen.c \

# ============================================================================= #

BASE_SRC	= $(addprefix srcs/, $(SRCS))

# ============================================================================= #

BASE_OBJS	= $(BASE_SRC:.c=.o)

ALL_OBJS	= $(BASE_OBJS)

# ============================================================================= #

LDFLAGS		= -I./srcs

# ============================================================================= #

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g -g3 -fsanitize=address

RM			= rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME):	$(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(LDFLAGS) -o $(NAME)

# ============================================================================= #

all:	$(NAME)

clean:
	$(RM) $(ALL_OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

# ============================================================================= #
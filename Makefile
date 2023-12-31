NAME = ircserv

SRCS = main.cpp\
		srcs/server_conf.cpp\
		srcs/client_conf.cpp\
		srcs/poll_main.cpp\
		srcs/ft_itoa.cpp\
		srcs/utils.cpp\
		srcs/nickname.cpp\
		srcs/channel_conf.cpp\
		srcs/topic.cpp\
		srcs/msg.cpp\
		srcs/password.cpp\
		srcs/username.cpp\
		srcs/channel_creation.cpp\
		srcs/join.cpp\
		srcs/limit.cpp\
		srcs/kick.cpp\
		srcs/invite.cpp\
		srcs/op.cpp\
		srcs/skibidi.cpp\
		srcs/help.cpp\

OBJS = $(SRCS:.cpp=.o)

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98 -g
RM = rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
				
clean:
			$(RM) $(OBJS)
			
fclean:		clean
			$(RM) $(NAME)
			
re:			fclean all

.PHONY:		all clean fclean re

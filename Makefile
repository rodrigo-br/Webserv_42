NAME = webserv

INCLUDES = -I includes

CC	= c++

RM	= rm -rf

CFLAGS	= -Wall -Wextra -Werror -std=c++98


DIR_SRCS	=	sources
DIR_OBJS	=	obj

SRCS		=	$(DIR_SRCS)/main.cpp \
				$(DIR_SRCS)/Server.cpp \

TEST		=	tests/cavalinho.o
TEST_SRC	=	$(addprefix tests/, $(shell ls tests/ | grep tests_*))
TEST_SRC	+=	$(filter-out $(DIR_SRCS)/main.cpp, $(SRCS))

OBJS		=	$(subst $(DIR_SRCS), $(DIR_OBJS), $(SRCS:.cpp=.o))

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJS)/%.o	:	$(DIR_SRCS)/%.cpp
			mkdir -p $(DIR_OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
		$(RM) $(OBJS)
		$(RM) -r $(DIR_OBJS)

fclean:	clean
		$(RM) $(NAME)
		$(RM) $(OBJS)
		$(RM) -r $(DIR_OBJS)

re:		fclean all

$(TEST):
		c++ -c tests/main_t.cpp $< -o $(TEST)

test:	$(TEST)
		$(CC) $(INCLUDES) -g3 $(TEST_SRC) $(TEST) -o tests/cavalinho
		@echo
		valgrind --leak-check=full --show-leak-kinds=all --log-file="leaks.txt" tests/cavalinho $(TEST_FLAG)

PHONY:	all clean fclean re
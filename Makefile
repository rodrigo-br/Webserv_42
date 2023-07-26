NAME = webserv

INCLUDES = -I includes

CC	= c++

RM	= rm -rf

CFLAGS	= -g3 -Wall -Wextra -Werror -Wshadow -std=c++98

DIR_SRCS	=	sources
DIR_OBJS	=	obj
DIR_TESTS	=	tests

SRCS		=	$(addprefix $(DIR_SRCS)/, $(shell ls $(DIR_SRCS) | grep .cpp$))

TEST		=	$(DIR_TESTS)/cavalinho.o
TEST_SRC	=	$(addprefix $(DIR_TESTS)/, $(shell ls $(DIR_TESTS)/ | grep tests_*))
TEST_SRC	+=	$(filter-out $(DIR_SRCS)/main.cpp, $(SRCS))

OBJS		=	$(subst $(DIR_SRCS), $(DIR_OBJS), $(SRCS:.cpp=.o))

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJS)/%.o	: $(DIR_SRCS)/%.cpp
			@mkdir -p $(DIR_OBJS)
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
		$(CC) $(INCLUDES) -c $(DIR_TESTS)/main_t.cpp $< -o $(TEST)

test:	$(TEST)
		$(CC) $(INCLUDES) -g3 $(TEST_SRC) $(TEST) -o $(DIR_TESTS)/cavalinho -lcurl -pthread
		valgrind --leak-check=full --show-leak-kinds=all --log-file="leaks.txt" $(DIR_TESTS)/cavalinho $(TEST_FLAG)

PHONY:	all clean fclean re

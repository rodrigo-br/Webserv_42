NAME = webserv

CC = c++
RM = rm -rf
CFLAGS = -g3 -Wall -Wextra -Werror -Wshadow -std=c++98

INCLUDES = -I includes
DIR_SOURCES = sources
DIR_OBJS = obj
DIR_TESTS = tests

SOURCES = $(shell find $(DIR_SOURCES) -type f -name "*.cpp")
OBJS = $(subst $(DIR_SOURCES),$(DIR_OBJS),$(SOURCES:.cpp=.o))

NAME_TESTS = cavalinho
BIN_TESTS = ./bin/test.bin
TEST		=	$(DIR_TESTS)/cavalinho.o
TEST_SRC	=	$(addprefix $(DIR_TESTS)/, $(shell ls $(DIR_TESTS)/ | grep tests_*))
TEST_SRC	+=	$(filter-out $(DIR_SOURCES)/main.cpp, $(SOURCES))

all: $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SOURCES)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SOURCES)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(TESTS_OBJS)
	$(RM) $(DIR_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(TEST):
		$(CC) $(INCLUDES) -c $(DIR_TESTS)/main_t.cpp $< -o $(TEST)

test:	$(TEST)
		$(CC) $(INCLUDES) -g3 $(TEST_SRC) $(TEST) -o $(DIR_TESTS)/cavalinho -lcurl -pthread
		valgrind --leak-check=full --show-leak-kinds=all --log-file="leaks.txt" $(DIR_TESTS)/cavalinho $(TEST_FLAG)

.PHONY: all clean fclean re test

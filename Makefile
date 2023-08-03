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
TESTS_SOURCES = $(shell find $(DIR_SOURCES) -type f -name "*.cpp" -not -name "main.cpp")
TESTS_SOURCES += $(shell find $(DIR_TESTS) -type f -name "*.cpp")
TESTS_OBJS += $(subst $(DIR_SOURCES),$(DIR_OBJS),$(TESTS_SOURCES:.cpp=.o))

all: $(NAME)

test: $(NAME_TESTS)

$(NAME_TESTS): $(TESTS_OBJS) $(BIN_TESTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_OBJS) $(BIN_TESTS) -o $(NAME_TESTS)

$(DIR_OBJS)/%.o: $(DIR_TESTS)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SOURCES)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(NAME_TESTS)
	rm -rf $(TESTS_OBJS)
	$(RM) $(DIR_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test

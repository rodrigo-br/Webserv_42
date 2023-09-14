NAME = webserv

CC = c++
RM = rm -rf
CFLAGS = -g3 -Wall -Wextra -Werror -Wshadow -std=c++98

INCLUDES = -I includes
DIR_SOURCES = sources
DIR_OBJS = obj

SOURCES = $(shell find $(DIR_SOURCES) -type f -name "*.cpp")
OBJS = $(subst $(DIR_SOURCES),$(DIR_OBJS),$(SOURCES:.cpp=.o))

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
	if [ -e web_leaks.txt ]; then \
		rm web_leaks.txt; \
	fi

fclean: clean
	$(RM) $(NAME)

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --log-file="web_leaks.txt" ./webserv

.PHONY: all clean fclean re test

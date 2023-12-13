CC := c++
CPPFLAGS := -Wall -Wextra -Werror -std=c++98 -g
RM := rm -rf

NAME := parse

HEADERS := common.hpp ConfigParse.hpp SyntaxException.hpp Token.hpp \
TokenType.hpp Scanner.hpp

SRCS := $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $^ -o $@

%.o: %.cpp $(HEADERS)
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re

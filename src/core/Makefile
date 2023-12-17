CC := g++
CPPFLAGS := -Wall -Wextra -Werror -std=c++98 -g -I include/
RM := rm -rf

NAME := parse
OBJ_DIR := ../../build/

PARSER_DIR := Parser/
SCANNER_DIR := Sanner/
INCLUDE_DIR := include/
VISITOR_DIR := visitor/

HEADERS := $(wildcard $(INCLUDE_DIR)*.hpp)

SRCS := $(wildcard *.cpp)
OBJS = $(addprefix $(OBJ_DIR),$(SRCS:%.cpp=%.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $^ -o $@

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR)%.o: %.cpp $(HEADERS)
	@$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re

GREEN = \033[38;2;0;153;0m
NC = \033[0m # No Color

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g
RM			= rm -rf

NAME		= webserv

SRC_DIR		= src
BUILD_DIR	= build

SRCS		= $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJECTS		= $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:%.cpp=%.o)))

LIB			= $(BUILD_DIR)/libwebserv.a

INCLUDE		= include/webserv.h
INCLUDE		+= $(shell find src -type f -name "*.hpp")
all:	$(NAME)

r:
	@echo $(SRCS)

$(NAME): $(OBJECTS)
	@echo $(CXX) $^ -o $@
	@$(CXX) $^ -fsanitize=address -o $@

$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE)
	@echo "$(GREEN)=> Compiling$(NC) $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/*/%.cpp $(INCLUDE)
	@echo "$(GREEN)=> Compiling$(NC) $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@


$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

unittest:
	@docker compose up --build; make fclean -f Makefile-test

clean:
	@$(RM) $(BUILD_DIR) $(LIB)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests

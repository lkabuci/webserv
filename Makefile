GREEN = \033[38;2;0;153;0m
NC = \033[0m # No Color

CC			= c++
CPPFLAGS	= -Wall -Wextra -Werror -std=c++17 -g
RM			= rm -rf

NAME		= webserv

SRC_DIR		= src/

SRCS		= main.cpp test.cpp
BUILD_DIR	= build/
OBJECTS		= $(addprefix $(BUILD_DIR),$(SRCS:%.cpp=%.o))

LIB			= $(BUILD_DIR)libwebserv.a

INCLUDE		= include/

# Unittest --------------
GTEST = /usr/local/lib/libgtest.a
TEST_DIR = test/
UNITTEST_FLAGS 	= -std=c++17 -Wall -I $(INCLUDE) -I /usr/local/include/gtest/ -c
UNITTEST_LFLAGS = -std=c++17 -I $(INCLUDE) -pthread
UNITTEST_SRCS 		= $(wildcard test/*.cpp)
UNITTEST_OBJECTS	= $(addprefix $(BUILD_DIR),$(UNITTEST_SRCS:%.cpp=%.o))
# -----------------------

all:	$(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $^ -o $@
	@ar cr $(LIB) $(filter-out build/main.o,$^)

$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR)%.o:	$(SRC_DIR)%.cpp
	@echo "$(GREEN)=> Compiling$(NC) $<"
	@$(CC) $(CPPFLAGS) -c $< -o $@

tests:  all $(UNITTEST_OBJECTS)
	@$(CC) $(UNITTEST_LFLAGS) -o $@ $(UNITTEST_OBJECTS) $(GTEST) $(LIB) && ./$@

$(BUILD_DIR)$(TEST_DIR)%.o: $(TEST_DIR)%.cpp
	@$(CC) $(CPPFLAGS) $(UNITTEST_FLAGS) $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Dockerfile ----------
d:
	@docker compose up

dit:
	@docker build -t webserv . && docker run -it --rm --entrypoint bash webserv

dc:
	@docker system prune -af
# ---------------------

clean:
	@$(RM) $(BUILD_DIR) $(LIB)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests

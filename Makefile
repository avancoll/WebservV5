#          ----------========== {     VARS     } ==========----------

NAME = webserv
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDE = -I includes

#          ----------========== {     SRCS     } ==========----------

SRC_DIR = srcs

SRC =	main.cpp\
		Webserv.cpp\
		utils.cpp\
		Config.cpp\
		Server.cpp\
		Socket.cpp\
		CGI.cpp\
		HTTP.cpp\
		Request.cpp\
		Response.cpp
		
#          ----------========== {     OBJS     } ==========----------

OBJ_DIR = obj_dir/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

VPATH= $(shell find ./ -type d)

#          ----------========== {    REGLES    } ==========----------

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: %.cpp
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@printf "\e[1;42m \e[0;m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJ)
	@rm -rf obj_dir
	@printf "\e[0;31m[.o files deleted]\n\e[0;m"

fclean: clean
	@rm -f $(NAME)
	@printf "\e[0;31m[webserv deleted]\n\e[0;m"

re: fclean all

.PHONY: all clean fclean re bonus
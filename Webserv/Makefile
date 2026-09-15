######## Colours ########

RST = "\033[0m"
RED = "\033[31m"
GRN = "\033[32m"
YEL = "\033[33m"
BLU = "\033[34m"
MAG = "\033[35m"
CYN = "\033[36m"
WHT = "\033[37m"

######## Typographicals ########

BLD = "\033[1m"
FNT = "\033[2m"
ITA = "\033[3m"
UNL = "\033[4m"

######## ------------- ########

NAME = webserv
CXX = c++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -O2
CC = $(CXX) $(CXXFLAGS)

SRC = \
	./src/main.cpp \
	./src/Server.cpp \
	./src/HttpRequest.cpp \
	./src/HttpResponse.cpp \
	./src/ConfigHandler.cpp \
	./src/utils.cpp \

OBJS = $(SRC:.cpp=.o)

.cpp.o:
		@echo $(CYN)"Compiling:" $(WHT)$<$(RST)
		$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GRN)"Compiling..." $(YEL)$(NAME)$(RST)
	$(CC) $(OBJS) -o $(NAME)
	@echo $(GRN)"\n\n 		Compilations Complete :)\n\n"$(RST)

clean:
	@echo $(RED)"removing object files"$(RST)
	rm -f $(OBJS)
	@echo $(GRN)"request completed"$(RST)

fclean: clean
	@echo $(RED)"removing executable" $(YEL)$(NAME)$(RST)
	@rm -f $(NAME)
	@echo $(GRN)"request completed"$(RST)

re:	fclean all

# Debug build: no optimisation, symbols, AddressSanitizer
debug: CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -O0 -g -fsanitize=address
debug: fclean $(NAME)

.PHONY: all clean fclean re debug
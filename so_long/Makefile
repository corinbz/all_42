NAME    = so_long
CFLAGS  = -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
#MLX STUFF
LIBMLX	= ./LIBS/MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

LIBFTDIR = ./LIBS/LIBFT
SRCS    = $(shell find ./src -name "*.c")
OBJS    = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
OBJDIR  = ./obj/

GREEN=\033[1;32m
BLUE=\033[1;36m
YELLOW=\033[1;33m
RED=\033[1;31m
NC=\033[0m # No Color

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJDIR)%.o: ./src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(LIBFTDIR) -c $< -o $@ $(HEADERS)
	@echo "$(GREEN)Compiled $< successfully!$(NC)"

$(NAME): $(OBJS)
	@make -s -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -I$(LIBFTDIR) $(LIBS) $(HEADERS) -o $@
	@echo "$(BLUE)$(NAME) created successfully!$(NC)"

clean:
	@rm -rf $(OBJDIR)
	@make -s -C $(LIBFTDIR) clean
	@rm -rf $(LIBMLX)/build
	@echo "$(YELLOW)$(NAME) -> Object files removed!$(NC)"

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBFTDIR) fclean
	@echo "$(RED)$(NAME) executable removed!$(NC)"

re: fclean all

.PHONY: all clean fclean re libmlx

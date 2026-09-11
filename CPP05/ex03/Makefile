# Compiler
CXX = c++
OBJDIR = obj

# Compiler flags
CXXFLAGS = -Wall -Werror -Wextra

# Executable name
TARGET = intern

SRCS = src/main.cpp \
			 src/Bureaucrat.cpp \
			 src/AForm.cpp \
			 src/ShrubberyCreationForm.cpp \
			 src/RobotomyRequestForm.cpp \
			 src/PresidentialPardonForm.cpp \
			 src/Intern.cpp \

OBJS = $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

# Colors 
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
RESET = \033[0m

# Default rule 
all: $(TARGET)

$(OBJDIR):
					@mkdir -p $(OBJDIR)

# Rule to build the target executable
$(TARGET): $(OBJS)
	@echo "$(GREEN)Building $(TARGET) from $(OBJS)...$(RESET)"
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "$(GREEN)Done! Executable created: $(TARGET)$(RESET)"

# Rule to build object files from source files
$(OBJDIR)/%.o: src/%.cpp Makefile | $(OBJDIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule: remove object files
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	rm -rf $(OBJDIR)
	@echo "$(YELLOW)Object files removed.$(RESET)"

# Full clean rule: remove object files and the executable
fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	rm -f $(TARGET)
	@echo "$(RED)Executable removed.$(RESET)"

# Rebuild rule: clean everything and rebuild
re: fclean all

# Phony targets (not actual files)
.PHONY: all clean fclean re test

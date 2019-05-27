# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dadavyde <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/17 14:33:17 by dadavyde          #+#    #+#              #
#    Updated: 2019/05/17 14:33:21 by dadavyde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = clang++
C_FLAGS = -Wall -Wextra -Werror -std=c++11

SOURCES = sources/main.cpp\
        sources/OperandFactory.cpp\
        sources/Parser.cpp\
        sources/Lexer.cpp\
        sources/AbstractVm.cpp\
        sources/exceptions.cpp\
        sources/Instruction.cpp\

HEADERS = includes/IOperand.hpp\
        includes/Operand.hpp\
        includes/OperandFactory.hpp\
        includes/Parser.hpp\
        includes/Lexer.hpp\
        includes/AbstractVm.hpp\
        includes/exceptions.hpp\
        includes/Instruction.hpp\
        includes/structs.hpp

INCLUDES = -I includes/

OBJ = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.cpp=.o)))
OBJDIR = obj/

NAME = avm

BG			=	"\033[32;1m"
BR			=	"\033[31;1m"

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HEADERS) $(SOURCES)
	$(CLANG)  $(OBJ) -o $@
	@echo ${BG}"[ ✓ ] $@"

$(OBJDIR)%.o: sources/%.cpp
	@$(CLANG)  $(C_FLAGS) -c $< -o $@ $(INCLUDES)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -f $(OBJ)
	rm -rf $(OBJDIR)
	@echo ${BR}"[ ✗ ] $(OBJS)"

fclean: clean
	@echo $(OBJ)
	rm -f $(NAME)
	@echo ${BR}"[ ✗ ] $(NAME)"

re: fclean all

.PHONY: all fclean clean re

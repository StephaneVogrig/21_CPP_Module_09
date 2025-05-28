# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 03:03:35 by svogrig           #+#    #+#              #
#    Updated: 2025/05/28 16:31:47 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		?=	btc
DEBUG_NAME	:=	$(NAME)_debug

# sources ---------------------------------------------------------------------#

SRC 		?=	main.cpp \
				BitcoinExchange.cpp

# objects ---------------------------------------------------------------------#

# OBJ_DIR		:=	.build/
# OBJ			:=	$(SRC:%.cpp=$(OBJ_DIR)%.o)
OBJ_DIR_RELEASE :=  .build/release/
OBJ_DIR_DEBUG   :=  .build/debug/
OBJ_DIR			?=	$(OBJ_DIR_RELEASE)
OBJ				:=	$(SRC:%.cpp=$(OBJ_DIR)%.o)

DEPS			:=	$(OBJ:.o=.d)

# compilation -----------------------------------------------------------------#

CXX			:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror
DEBUGFLAGS	:=	-DDEBUG -std=c++98 -g
#------------------------------------------------------------------------------#
# rules                                                                        #
#------------------------------------------------------------------------------#

all:
	@$(MAKE) -j makeall --no-print-directory

clean:
	@rm -rf $(OBJ_DIR_RELEASE) $(OBJ_DIR_DEBUG)

fclean: clean
	@rm -rf $(NAME) $(DEBUG_NAME)

re: fclean all

test:
	@$(MAKE) -j all --no-print-directory
	./$(NAME)
	@rm $(NAME)

makeall: $(NAME)

debug:
	@$(MAKE) -j all --no-print-directory NAME=$(DEBUG_NAME) OBJ_DIR=$(OBJ_DIR_DEBUG)

#------------------------------------------------------------------------------#
# compilation                                                                  #
#------------------------------------------------------------------------------#

$(OBJ_DIR_RELEASE)%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@
	@echo "compiled $<"

$(OBJ_DIR_DEBUG)%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -MMD -c $< -o $@
	@echo "compiled $<"

-include $(DEPS)

#------------------------------------------------------------------------------#
# linkage                                                                      #
#------------------------------------------------------------------------------#

$(NAME): $(OBJ)
	@$(CXX) $(OBJ) -o $(NAME)
	@echo "created $(NAME)"

#------------------------------------------------------------------------------#
# specifications                                                               #
#------------------------------------------------------------------------------#

.PHONY: all \
		clean \
		fclean \
		re \
		debug

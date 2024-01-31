# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 22:11:19 by vduchi            #+#    #+#              #
#    Updated: 2023/08/24 17:45:36 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

-include mk_files/directories.mk

-include mk_files/sources_parser.mk
-include mk_files/sources_execute.mk
-include mk_files/sources_built_ins.mk
-include mk_files/sources_general.mk

#=-=-=-=-=-=-=- COLORS DEFINITION =-=-=-=-=-=-=-=-=-#

DEL_LINE		=	\033[2K
ITALIC			=	\033[3m
BOLD			=	\033[1m
DEF_COLOR		=	\033[0;39m
GRAY			=	\033[0;90m
RED				=	\033[0;91m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
BLUE			=	\033[0;94m
MAGENTA			=	\033[0;95m
CYAN			=	\033[0;96m
WHITE			=	\033[0;97m
BLACK			=	\033[0;99m
ORANGE			=	\033[38;5;209m
BROWN			=	\033[38;2;184;143;29m
DARK_GRAY		=	\033[38;5;234m
MID_GRAY		=	\033[38;5;245m
DARK_GREEN		=	\033[38;2;75;179;82m
DARK_YELLOW		=	\033[38;5;143m

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

NAME			=	minishell

LIBFT_PATH		=	libft/libft.a
RD_PATH			=	readline/libreadline.a

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

CFLAGS			+= 	-Wall -Werror -Wextra -DREADLINE_LIBRARY -g -O3 $(addprefix -I , $(INC_DIR)) #-fsanitize=address
LDFLAGS			= 	-L libft -L readline -lft -lreadline -lncurses
DFLAGS_MS		=	-MMD -MP -MF $(DEP_DIR_MS)/$*.d
DFLAGS_BI		=	-MMD -MP -MF $(DEP_DIR_BI)/$*.d
DFLAGS_EXEC		=	-MMD -MP -MF $(DEP_DIR_EXEC)/$*.d
DFLAGS_PARSER	=	-MMD -MP -MF $(DEP_DIR_PARSER)/$*.d

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

CC				=	gcc
RM				=	rm -rf
MKDIR			=	mkdir -p

#=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-#

$(OBJ_DIR_BI)/%.o	:	$(SRC_DIR_BI)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS_BI) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_BI)/%,%, $<)   \tcompiled!$(DEF_COLOR)"

$(OBJ_DIR_MS)/%.o	:	$(SRC_DIR_MS)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS_MS) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_MS)/%,%, $<)  \tcompiled!$(DEF_COLOR)"

$(OBJ_DIR_EXEC)/%.o	:	$(SRC_DIR_EXEC)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS_EXEC) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_EXEC)/%,%, $<)   \tcompiled!$(DEF_COLOR)"

$(OBJ_DIR_PARSER)/%.o	:	$(SRC_DIR_PARSER)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS_PARSER) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_PARSER)/%,%, $<)   \tcompiled!$(DEF_COLOR)"

$(OBJ_DIR_TESTER)/%.o	:	$(SRC_DIR_TESTER)/%.c
	@$(CC) -c $< $(CFLAGS) $(DFLAGS_TESTER) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_TESTER)/%,%, $<)   \tcompiled!$(DEF_COLOR)"

all				:	directories
	@$(MAKE) -C libft
	@$(MAKE) $(NAME)

$(NAME)			::
	@echo "$(MAGENTA)\nChecking minishell...$(DEF_COLOR)"

$(NAME)			::	$(LIBFT_PATH) $(RD_PATH) $(OBJS_MS) $(OBJS_EXEC) $(OBJS_BI) $(OBJS_PARSER)
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	@echo "$(ORANGE)Compiling minishell exec...$(DEF_COLOR)"

$(NAME)			::
	@echo "$(GREEN)Minishell executable ready!$(DEF_COLOR)"

$(RD_PATH)		:
	@echo "$(ORANGE)\nCompiling readline library...$(DEF_COLOR)"
	@cd readline; ./configure --prefix=$(shell pwd)/readline/library; make; make install;
	@echo "$(GREEN)Readline library ready!$(DEF_COLOR)"

directories	:
	@$(MKDIR) $(OBJS_DIR)
	@$(MKDIR) $(DEPS_DIR)
	@$(MKDIR) $(OBJ_DIR_MS)
	@$(MKDIR) $(DEP_DIR_MS)
	@$(MKDIR) $(OBJ_DIR_BI)
	@$(MKDIR) $(DEP_DIR_BI)
	@$(MKDIR) $(OBJ_DIR_EXEC)
	@$(MKDIR) $(DEP_DIR_EXEC)
	@$(MKDIR) $(OBJ_DIR_PARSER)
	@$(MKDIR) $(DEP_DIR_PARSER)


clean			:
	@$(RM) $(OBJS_DIR)
	@$(RM) $(DEPS_DIR)

fclean			:	clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@-cd readline; make distclean -sik;
	@$(RM) readline/library
	@echo "$(BLUE)\nMinishell cleaned!$(DEF_COLOR)"

re				:	fclean all

-include $(DEPS_MS)
-include $(DEPS_BI)
-include $(DEPS_EXEC)
-include $(DEPS_PARSER)

.PHONY: all clean fclean re

#
#valgrind:
#	valgrind --leak-check=yes --show-leak-kinds=all "nombre del executable" "nombre de argumentos"
#	valgrind --leak-check=yes --track-origins=yes "nombre del executable" "nombre de argumentos"
#
#	gcc $(CFLAGS) -fsanitize=address -g -O3 -fno-omit-frame-pointer $(LDFLAGS) $(SRCS) -o $@

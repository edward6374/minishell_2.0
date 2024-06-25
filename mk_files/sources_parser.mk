# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_parser.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 19:06:12 by vduchi            #+#    #+#              #
#    Updated: 2024/06/19 12:48:06 by mehernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PARSER	=	srcs/parser/parser.c
SRCS_PARSER	+=	srcs/parser/checker.c
SRCS_PARSER	+=	srcs/parser/open_file.c
SRCS_PARSER	+=	srcs/parser/change_node.c
SRCS_PARSER	+=	srcs/parser/delete_quotes.c
SRCS_PARSER	+=	srcs/parser/word_detector.c
SRCS_PARSER	+=	srcs/parser/find_commands.c
SRCS_PARSER	+=	srcs/parser/list_commands.c
SRCS_PARSER	+=	srcs/parser/expand_variable.c
SRCS_PARSER	+=	srcs/parser/pipe_separation.c
SRCS_PARSER	+=	srcs/parser/list_word_detector.c
SRCS_PARSER	+=	srcs/parser/list_command_utils.c
SRCS_PARSER	+=	srcs/parser/expand_variable_utils.c

OBJS_PARSER	=	$(patsubst $(SRC_DIR_PARSER)/%, $(OBJ_DIR_PARSER)/%, $(SRCS_PARSER:.c=.o))
DEPS_PARSER	=	$(patsubst $(SRC_DIR_PARSER)/%, $(DEP_DIR_PARSER)/%, $(SRCS_PARSER:.c=.d))


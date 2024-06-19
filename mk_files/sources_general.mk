# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_general.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehernan <mehernan@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:46:18 by vduchi            #+#    #+#              #
#    Updated: 2024/06/19 12:48:02 by mehernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MS		=	srcs/general/main.c
SRCS_MS		+=	srcs/general/take_env.c
SRCS_MS		+=	srcs/general/gen_utils.c
SRCS_MS		+=	srcs/general/free_funcs.c
SRCS_MS		+=	srcs/general/free_structs.c
SRCS_MS		+=	srcs/general/signal.c
SRCS_MS		+=	srcs/general/init_pwd.c

OBJS_MS		=	$(patsubst $(SRC_DIR_MS)/%, $(OBJ_DIR_MS)/%, $(SRCS_MS:.c=.o))
DEPS_MS		=	$(patsubst $(SRC_DIR_MS)/%, $(DEP_DIR_MS)/%, $(SRCS_MS:.c=.d))

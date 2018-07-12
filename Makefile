# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    test                                             .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/06/19 13:41:44 by xamartin     #+#   ##    ##    #+#        #
#    Updated: 2018/07/09 17:07:34 by tduverge    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY = all, clean, fclean, re


#COMPILATION

CC = gcc
LIBFT = libft/
ASM = asm
CW = corewar
INC = includes/corewar.h includes/op.h includes/asm.h
CFLAGS = -Wall -Werror -Wextra -g


#PATH

ASM_SCRS_PATH = ./srcs_asm/
ASM_OBJS_PATH = ./srcs_asm/


ASM_FILES = main_asm.c\

ASM_SRCS = $(addprefix $(ASM_SRCS_PATH), $(ASM_FILES))
ASM_OBJS = $(addprefix $(ASM_OBJS_PATH), $(ASM_FILES:.c=.o))


CW_SRCS_PATH = ./srcs_cw/
CW_OBJS_PATH = ./srcs_cw/

CW_FILES = main_cw.c\
		   init_champ.c\
		   access_reg.c\
		   generate_memory.c\
		   lets_go.c\
		   lets_dump.c\


CW_SRCS = $(addprefix $(CW_SRCS_PATH), $(CW_FILES))
CW_OBJS = $(addprefix $(CW_OBJS_PATH), $(CW_FILES:.c=.o))



#RULES

all: $(ASM) $(CW)


$(ASM): $(ASM_OBJS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(ASM_OBJS) -L $(LIBFT) -lft

$(CW): $(CW_OBJS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(CW_OBJS) -L $(LIBFT) -lft


$(CW_OBJS_PATH)%.o: $(CW_SRCS_PATH)%.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<

$(ASM_OBJS_PATH)%.o: $(ASM_SRCS_PATH)%.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	make -C libft clean
	rm -f $(CW_OBJS)
	rm -f $(ASM_OBJS)

fclean: clean
	rm -f libft/libft.a
	rm -f $(CW) $(ASM)

re: fclean all

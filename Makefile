# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    test                                             .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/06/19 13:41:44 by xamartin     #+#   ##    ##    #+#        #
#    Updated: 2018/07/16 22:03:14 by tduverge    ###    #+. /#+    ###.fr      #
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
		   lets_go.c\
		   lets_dump.c\
		   init/parsing.c\
		   init/init_champ.c\
		   init/generate_memory.c\
		   read_write/access_reg.c\
		   read_write/access_pc.c\
		   read_write/recup_args.c\
		   read_write/print_mem.c\
		   ft_upcode/ft_live.c\
		   ft_upcode/ft_ld.c\
		   ft_upcode/ft_st.c\
		   ft_upcode/ft_add.c\
		   ft_upcode/ft_sub.c\
		   ft_upcode/ft_and.c\
		   ft_upcode/ft_or.c\
		   ft_upcode/ft_xor.c\
		   ft_upcode/ft_zjmp.c\
		   ft_upcode/ft_ldi.c\
		   ft_upcode/ft_sti.c\
		   ft_upcode/ft_fork.c\
		   ft_upcode/ft_lld.c\
		   ft_upcode/ft_lldi.c\
		   ft_upcode/ft_lfork.c\
		   ft_upcode/ft_aff.c\


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

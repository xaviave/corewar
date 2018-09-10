# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    test                                             .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: xamartin <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/06/19 13:41:44 by xamartin     #+#   ##    ##    #+#        #
#    Updated: 2018/09/10 21:36:18 by lotoussa    ###    #+. /#+    ###.fr      #
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
NCURSES_FLAG = -lncurses
CFLAGS = -Wall -Wextra -Werror


#PATH

ASM_SCRS_PATH = ./srcs_asm/
ASM_OBJS_PATH = ./srcs_asm/


ASM_FILES = main_asm.c\
		   check_ins.c\
		   detail.c\
		   ft_anyway.c\
		   ft_check.c\
		   ft_count_size.c\
		   ft_count_size_ld_st.c\
		   ft_extend_check.c\
		   ft_extract_base.c\
		   ft_first.c\
		   ft_free.c\
		   ft_nb_par_one.c\
		   ft_nb_par_two.c\
		   ft_parsing.c\
		   ft_print_size.c\
		   ft_reform.c\
		   ft_suite_parsing.c\
		   ft_third.c\
		   tools.c\
		   ft_bytecode.c\
		   ft_size_par_exception.c\
		   ft_write_details.c\
		   new_size_tab.c

ASM_SRCS = $(addprefix $(ASM_SRCS_PATH), $(ASM_FILES))
ASM_OBJS = $(addprefix $(ASM_OBJS_PATH), $(ASM_FILES:.c=.o))


CW_SRCS_PATH = ./srcs_cw/
CW_OBJS_PATH = ./srcs_cw/

CW_FILES = main_cw.c\
		   lets_go.c\
		   lets_graph.c\
		   lets_dump.c\
		   one_cycle.c\
		   init/all_init_is_love.c\
		   init/generate_memory.c\
		   init/init_champ.c\
		   init/parsing.c\
		   tools/access_pc.c\
		   tools/access_reg.c\
		   tools/check_cor.c\
		   tools/ft_error.c\
		   tools/kill_them_all.c\
		   tools/list_len.c\
		   tools/recup_direct.c\
		   tools/recup_indirect.c\
		   graph/init_window.c\
		   graph/legend.c\
		   graph/print_dump.c\
		   graph/print_mem.c\
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
	$(CC) $(CFLAGS) $(NCURSES_FLAG) -o $@ $(CW_OBJS) -L $(LIBFT) -lft


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

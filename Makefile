# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/06/19 13:41:44 by xamartin     #+#   ##    ##    #+#        #
#    Updated: 2018/10/05 13:45:28 by tduverge    ###    #+. /#+    ###.fr      #
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


ASM_FILES =	main_asm.c\
			collect/collect_header_and_label.c\
			collect/collect_comment.c\
			collect/collect_name.c\
			collect/collect_label.c\
			tools/to_the_next.c\
			tools/give_coline.c\
			tools/start_by.c\
			tools/multi_split.c\
			tools/ft_long_atoi.c\
			tools/free_all.c\
			collect/collect_instructions.c\
			record_convert_cmd/new_cmd.c\
			record_convert_cmd/get_bytecode.c\
			record_convert_cmd/record_arg.c\
			record_convert_cmd/get_size_and_adress.c\
			tools/error_instru.c\
			record_convert_cmd/convert_cmd.c \
			write/writing_output.c \
			write/write_cor.c \
			record_convert_cmd/calcul_size.c \
			checker/make_clean.c \
			record_convert_cmd/recalcul_label.c \
			checker/check_name_comment.c \
			checker/check_pre_parsing.c \
			checker/check_arg.c \
			tools/ft_strsplit_modif.c \
			checker/check_line_composition.c \
			checker/analyse_line.c\
			bad_usage/bad_usage.c


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

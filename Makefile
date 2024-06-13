# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:10:12 by mcatalan@st       #+#    #+#              #
#    Updated: 2024/06/12 08:33:57 by kseligma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
# LIBFT_D = libft/
# LIBFT = libft.a

# NSERVER = minishell


# OBJS = $(SRCS:.c=.o)

# INCLUDE = -I./
# RM = rm -f
# CFLAGS = ## -Wall -Wextra -Werror

# all: makelibft $(NSERVER)

# makelibft:
# 	@make --no-print-directory -C $(LIBFT_D)

# %.o: %.c
# 	${CC} ${CFLAGS} $(INCLUDE) -c $< -o $@

# $(NSERVER): $(OBJS) $(LIBFT_D)$(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) -g -lreadline -L/usr/lib/x86_64-linux-gnu

# clean:
# 	@make clean --no-print-directory -C $(LIBFT_D)
# 	$(RM) $(OBJS)

# fclean: clean
# 	$(RM) $(NSERVER)

# re: fclean all

# .PHONY: all clean fclean re makelibft


# MACOS
# Print MINISHELL and authors' names
MINISHELL_MSG = MINISHELL
AUTHORS_MSG = by oseivane el "calamidades" & ...kevin
MESSAGE_LEN = $$(($(shell echo $(MINISHELL_MSG) | wc -c) - 1))

PRINT_MINISHELL = @printf "$(VIOLET)%*s$(RESET)\n" $(MESSAGE_LEN) $(MINISHELL_MSG)
PRINT_AUTHORS = @echo "$(BLUE)$(AUTHORS_MSG)$(RESET)"

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
VIOLET = \033[0;35m
RESET = \033[0m

LIBFT_D = libft/
LIBFT = libft.a

READLINE_D = readline/
READLINE_A = $(READLINE_D)libhistory.a $(READLINE_D)libreadline.a
READLINE_FLAGS = -lreadline -ltermcap
READLINE_URL = http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-8.2.tar.gz
READLINE_TAR = readline.tar.gz
DEFS = -DREADLINE_LIBRARY

NAME = minishell

INCS =	includes/definitions.h \
		includes/get_next_line.h \
		includes/minishell.h \
		includes/structs.h \

SRCS =	src/env_utils1.c \
		src/env_utils2.c \
		src/errors.c \
		src/free_exit.c	\
		src/get_next_line_utils.c \
		src/get_next_line.c	\
		src/input.c	\
		src/minishell.c	\
		src/prompt.c	\
		src/signals.c	\
		src/utils.c	\
		src/builtins/ft_cd.c \
		src/builtins/ft_echo.c \
		src/builtins/ft_env.c \
		src/builtins/ft_exit.c \
		src/builtins/ft_export.c \
		src/builtins/ft_help.c \
		src/builtins/ft_pwd.c \
		src/builtins/ft_unset.c \
		src/execution/env_to_array.c \
		src/execution/execute_command_tree.c \
		src/execution/execute_pipeline.c \
		src/execution/execute_redirections.c \
		src/execution/execute_simple_command.c \
		src/execution/execution_util.c \
		src/execution/find_path.c \
		src/expansions/directories.c \
		src/expansions/expansion_quotes.c \
		src/expansions/expansion.c \
		src/expansions/parameter_expansion.c \
		src/expansions/pathname_expansion.c \
		src/expansions/wildcard_matching.c \
		src/expansions/word_splitting.c \
		src/parsing/here_doc.c \
		src/parsing/parse_connected_command.c \
		src/parsing/parse_list.c \
		src/parsing/parse_redir.c \
		src/parsing/parse_simple_command.c \
		src/parsing/parse_trimming.c \
		src/parsing/parse_word.c \
		src/parsing/parser.c \
		src/parsing/parsing_util.c \
		src/parsing/searching.c \

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

INCLUDE = -I./includes
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

#all: print_message $(READLINE_A) libft $(NAME)
#	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

all: print_message libft $(NAME)
	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

$(READLINE_D):
			@echo "$(YELLOW)Downloading READLINE...$(RESET)"
			@curl -k $(READLINE_URL) > $(READLINE_TAR)
			@tar -xf $(READLINE_TAR) && mv readline-* readline
			@rm -rf $(READLINE_TAR)
			@echo ✅;

$(READLINE_A): $(READLINE_D)
			@if [ ! -f $(READLINE_D)config.status ] ; then \
				echo "$(YELLOW)Configuring READLINE...$(RESET)" && \
				cd ./$(READLINE_D) && \
				./configure > /dev/null && \
				cd .. && \
				echo ✅; \
			fi
			@echo "$(YELLOW)Building READLINE...$(RESET)"
			@make --no-print-directory -C $(READLINE_D) > /dev/null
			@echo ✅

libft:
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make --no-print-directory -C $(LIBFT_D)

print_message:
	$(PRINT_MINISHELL)
	$(PRINT_AUTHORS)

%.o: %.c
#	@echo "$(YELLOW)Compiling...$(RESET)"
	@${CC} ${CFLAGS} $(OFLAGS) $(DEFS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_D)$(LIBFT) $(READLINE_A) $(INCS)
	@echo "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(DEFS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) $(READLINE_A) $(READLINE_FLAGS)
	@echo "$(GREEN)Linked!$(RESET)✅"
-include $(DEPS)

debug:
	valgrind --suppressions=readline.supp --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell

clean:
	@make clean --no-print-directory -C $(LIBFT_D)
	@$(RM) $(OBJS) $(DEPS)
	@echo "$(RED)Cleaned minishell!$(RESET)✅"

fclean:
	@make fclean --no-print-directory -C $(LIBFT_D)
	@$(RM) $(NAME) $(DEPS) $(OBJS) $(READLINE_A)
	@echo "$(RED)Fcleaned minishell!$(RESET)✅"

jesusg:
	@echo "$(VIOLET)Jesus is watching you...$(RESET)👀"
	@$(RM) -r $(OBJS_DIR) $(OBJS) $(DEPS)
	@echo "$(RED)Jesus has cleaned your soul!$(RESET)✅"

re: fclean all

.PHONY: all clean fclean re libft readline jesusg config debug

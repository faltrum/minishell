# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:10:12 by mcatalan@st       #+#    #+#              #
#    Updated: 2024/06/20 10:46:04 by kseligma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = src:src/parsing:src/expansions:src/execution:src/builtins:src_bonus:src_bonus/parsing:src_bonus/expansions:src_bonus/execution:src_bonus/builtins

# Messages
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

# Libs
LIBFT_D = libft/
LIBFT = libft.a
READLINE_D = readline/
READLINE_A = $(READLINE_D)libhistory.a $(READLINE_D)libreadline.a
READLINE_FLAGS = -lreadline -ltermcap
READLINE_URL = http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-8.2.tar.gz
READLINE_TAR = readline.tar.gz
DEFS = -DREADLINE_LIBRARY

# Minishell
NAME = minishell
NAME_B = minishell_bonus

# Object files
OBJ_DIR = objs

OBJ =	env_utils1.o				\
		env_utils2.o				\
		errors.o					\
		free_exit.o					\
		input.o						\
		minishell.o					\
		prompt.o					\
		signals.o					\
		utils.o						\
		ft_cd.o						\
		ft_echo.o					\
		ft_env.o					\
		ft_exit.o					\
		ft_export.o					\
		ft_export_util.o			\
		ft_pwd.o					\
		ft_unset.o					\
		env_to_array.o				\
		execute_command_tree.o		\
		execute_pipeline.o			\
		execute_redirections.o		\
		execute_simple_command.o	\
		execution_util.o			\
		find_path.o					\
		directories.o				\
		expansion_quotes.o			\
		expansion.o					\
		parameter_expansion.o		\
		pathname_expansion.o		\
		wildcard_matching.o			\
		word_splitting.o			\
		here_doc.o					\
		here_doc_util.o				\
		parse_connected_command.o	\
		parse_list.o				\
		parse_redir.o				\
		parse_simple_command.o		\
		parse_trimming.o			\
		parse_word.o				\
		parser.o					\
		parsing_util.o				\
		searching.o					\

OBJ_B =	env_utils1_bonus.o				\
		env_utils2_bonus.o				\
		errors_bonus.o					\
		free_exit_bonus.o				\
		input_bonus.o					\
		minishell_bonus.o				\
		prompt_bonus.o					\
		signals_bonus.o					\
		utils_bonus.o					\
		ft_cd_bonus.o					\
		ft_echo_bonus.o					\
		ft_env_bonus.o					\
		ft_exit_bonus.o					\
		ft_export_bonus.o				\
		ft_export_util_bonus.o			\
		ft_pwd_bonus.o					\
		ft_unset_bonus.o				\
		env_to_array_bonus.o			\
		execute_command_tree_bonus.o	\
		execute_pipeline_bonus.o		\
		execute_redirections_bonus.o	\
		execute_simple_command_bonus.o	\
		execution_util_bonus.o			\
		find_path_bonus.o				\
		directories_bonus.o				\
		expansion_quotes_bonus.o		\
		expansion_bonus.o				\
		parameter_expansion_bonus.o		\
		pathname_expansion_bonus.o		\
		wildcard_matching_bonus.o		\
		word_splitting_bonus.o			\
		here_doc_bonus.o				\
		here_doc_util_bonus.o			\
		parse_connected_command_bonus.o	\
		parse_list_bonus.o				\
		parse_redir_bonus.o				\
		parse_simple_command_bonus.o	\
		parse_trimming_bonus.o			\
		parse_word_bonus.o				\
		parser_bonus.o					\
		parsing_util_bonus.o			\
		searching_bonus.o				\

OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

OBJS_B = $(addprefix $(OBJ_DIR)/, $(OBJ_B))

DEPS = $(OBJS:.o=.d) $(OBJS_B:.o=.d)

# Utils
INCLUDE = -I./includes
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

# Mandatory linking
all: $(OBJ_DIR) print_message libft $(NAME)
	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

$(NAME): $(OBJS) $(LIBFT_D)$(LIBFT) $(READLINE_A) Makefile
	@echo "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) $(DEFS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) $(READLINE_A) $(READLINE_FLAGS)
	@echo "$(GREEN)Linked!$(RESET)✅"

# Bonus linking
bonus: $(OBJ_DIR) print_message libft $(NAME_B)

$(NAME_B): $(OBJS_B) $(LIBFT_D)$(LIBFT) $(READLINE_A) Makefile
	@echo "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) $(DEFS) $(OBJS_B) -o $@ $(LIBFT_D)$(LIBFT) $(READLINE_A) $(READLINE_FLAGS)
	@echo "$(GREEN)Linked!$(RESET)✅"

# Compilation
$(OBJ_DIR)/%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(DEFS) $(INCLUDE) -MMD -c $< -o $@

# Readline
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

# Libft
libft:
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make --no-print-directory -C $(LIBFT_D)

#Utils
print_message:
	$(PRINT_MINISHELL)
	$(PRINT_AUTHORS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEPS)

debug: all
	valgrind --suppressions=readline.supp --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell

clean:
	@make clean --no-print-directory -C $(LIBFT_D)
	@$(RM) $(OBJS) $(OBJS_B) $(DEPS) $(READLINE_A)
	@echo "$(RED)Object files, dependency files, libraries removed!$(RESET)✅"

fclean: clean
	@$(RM) $(NAME) $(NAME_B)
	@echo "$(RED)Executable removed$(RESET)✅"

jesusg:
	@echo "$(VIOLET)Jesus is watching you...$(RESET)👀"
	@$(RM) -r $(OBJS) $(DEPS)
	@echo "$(RED)Jesus has cleaned your soul!$(RESET)✅"

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re libft readline jesusg config debug bonus re_bonus $(OBJ_DIR)

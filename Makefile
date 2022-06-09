NAME=minishell
CC=cc
CFLAGS+=-Wall -Wextra -Werror -g -MMD

SRC_FILES=main.c
SRC_DIR=src
SRC=$(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ_DIR=obj
OBJ=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
DEP=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.d))

PARSER_FILES=parse.c \
			split.c \
			validation.c \
			build_tree.c \
			pipeline.c \
			command.c \
			redirection.c \
			utils.c \
			quoting.c \
			syntax_errors.c \
			free_utils.c \
			free_utils2.c \
			errors.c
PARSER_DIR=src/parser
SRC+=$(addprefix $(PARSER_DIR)/,$(PARSER_FILES))
PARSER_OBJ_DIR=obj/parser
OBJ+=$(addprefix $(PARSER_OBJ_DIR)/,$(PARSER_FILES:.c=.o))
DEP+=$(addprefix $(PARSER_OBJ_DIR)/,$(PARSER_FILES:.c=.d))

EXPANSION_FILES=expansion.c \
				expansion_utils.c \
				parameter_expansion.c \
				parameter_expansion_utils.c \
				word_splitting.c \
				quote_removal.c \
				filename_expansion.c \
				filename_expansion_utils.c \
				word_utils.c \
				word_utils2.c
EXPANSION_DIR=src/parser/expansion
EXPANSION_OBJ_DIR=obj/parser/expansion
OBJ+=$(addprefix $(EXPANSION_OBJ_DIR)/,$(EXPANSION_FILES:.c=.o))
DEP+=$(addprefix $(EXPANSION_OBJ_DIR)/,$(EXPANSION_FILES:.c=.d))

VAR_FILES=variables.c \
		get_envp.c \
		destroy_vlist.c \
		vlist_utils.c \
		initialize.c

VAR_DIR=src/variables
SRC+=$(addprefix $(VAR_DIR)/,$(VAR_FILES))
VAR_OBJ_DIR=obj/variables
OBJ+=$(addprefix $(VAR_OBJ_DIR)/,$(VAR_FILES:.c=.o))
DEP+=$(addprefix $(VAR_OBJ_DIR)/,$(VAR_FILES:.c=.d))

PIPE_FILES=builtin_brige.c \
		cmd.c \
		cmd_utils.c \
		exit_status.c \
		free.c \
		pipeline_work.c \
		pipeline_work_utils.c \
		redirs_logic.c \
		return_values.c \
		simple_redir.c \
		several_commands.c \
		several_commands_utils.c \
		dup_fd_for_work.c \
		no_command.c \
		start.c 

PIPE_DIR=src/commands_logic
SRC+=$(addprefix $(PIPE_DIR)/,$(PIPE_FILES))
PIPE_OBJ_DIR=obj/commands_logic
OBJ+=$(addprefix $(PIPE_OBJ_DIR)/,$(PIPE_FILES:.c=.o))
DEP+=$(addprefix $(PIPE_OBJ_DIR)/,$(PIPE_FILES:.c=.d))

BUILTIN_FILES=cd.c \
		echo.c \
		env.c \
		export.c \
		export_utils.c \
		pwd.c \
		unset.c \
		exit.c \
		exit_utils.c 

BUILTIN_DIR=src/builtin
SRC+=$(addprefix $(BUILTIN_DIR)/,$(BUILTIN_FILES))
BUILTIN_OBJ_DIR=obj/builtin
OBJ+=$(addprefix $(BUILTIN_OBJ_DIR)/,$(BUILTIN_FILES:.c=.o))
DEP+=$(addprefix $(BUILTIN_OBJ_DIR)/,$(BUILTIN_FILES:.c=.d))

GNL_FILES=get_next_line.c \
		get_next_line_utils.c 

GNL_DIR=src/get_next_line
SRC+=$(addprefix $(GNL_DIR)/,$(GNL_FILES))

GNL_OBJ_DIR=obj/get_next_line
OBJ+=$(addprefix $(GNL_OBJ_DIR)/,$(GNL_FILES:.c=.o))

SIG_FILES=signal.c \
		  signals_handler.c

SIG_DIR=src/signals
SRC+=$(addprefix $(SIG_DIR)/,$(SIG_FILES))

SIG_OBJ_DIR=obj/signals
OBJ+=$(addprefix $(SIG_OBJ_DIR)/,$(SIG_FILES:.c=.o))

INC_DIR=include
CPPFLAGS+=-I$(INC_DIR)

LIBFT_DIR=libft
LIBFT_NAME=ft
LIBFT=$(LIBFT_DIR)/lib$(LIBFT_NAME).a
CPPFLAGS+=-I$(LIBFT_DIR)
LDFLAGS+=-L$(LIBFT_DIR)
LDLIBS+=-l$(LIBFT_NAME)

LDLIBS+=-lreadline

all: objdirs libft $(NAME)

bonus: all

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

-include $(DEP)

objdirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(PARSER_OBJ_DIR)
	@mkdir -p $(VAR_OBJ_DIR)
	@mkdir -p $(EXPANSION_OBJ_DIR)
	@mkdir -p $(PIPE_OBJ_DIR)
	@mkdir -p $(BUILTIN_OBJ_DIR)
	@mkdir -p $(GNL_OBJ_DIR)
	@mkdir -p $(SIG_OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(PARSER_OBJ_DIR)/%.o: $(PARSER_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(VAR_OBJ_DIR)/%.o: $(VAR_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

libft:
	@make -C libft bonus

clean:
	@make -C libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re libft bonus objdirs

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 03:46:13 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 12:04:02 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <dirent.h>

typedef struct s_cmdtree
{
	int		type;
	void	*arg1;
	void	*arg2;
}	t_cmdtree;

# define OR 0
# define AND 1
# define GROUP 2
# define PIPELINE 3

t_cmdtree	*parse(char *s);
char		**split_on_tokens(const char *line, const int *quotes);
int			validate(char **splitted);
t_cmdtree	*arr_to_tree(char **splitted, size_t *ret_len);

typedef struct s_redir
{
	int		type;
	char	*arg;
}	t_redir;

# define INPUT 0
# define OUTPUT 1
# define HERE_DOC 2
# define APPEND 3

t_redir		**parse_redirs(char **splitted, size_t *len);

typedef struct s_cmd
{
	char		**argv;
	t_redir		**redirs;
}	t_cmd;

t_cmd		**parse_pipeline(char **splitted, size_t *ret_len);
t_cmd		*parse_command(char **splitted, size_t *ret_len);
typedef struct s_word
{
	char	*s;
	int		*q;
}	t_word;

int			expand_pipeline(t_cmd **pipeline);
int			expand_redirs(t_redir **redirs);
int			param_exp(t_word **word);
t_word		**split_words(const t_word *word);
t_word		**remove_quotes(t_word **arr);
t_word		**filename_exp(t_word **words);
char		**words_to_strings(t_word **words);

void		**concatenate_arrays(void **a, void **b);
void		**append_to_arr(void **a, void *b);
t_word		*create_word(const char *s);
t_word		**word_to_arr(t_word *word);
t_word		*append_str(t_word *word, const char *s, const int *q);
t_word		*wordndup(const t_word *word, size_t n);
t_word		*worddup(const t_word *word);
size_t		param_len(const t_word *word, size_t i);
size_t		calc_len_until_param(const t_word *word, size_t i);
size_t		arr_len(void **arr);
t_word		**concatenate_words(t_word **a, t_word **b);
t_word		**append_word(t_word **words, t_word *a);
int			pattern_matches(const char *pattern, const char *name);
DIR			*open_cwd(void);

int			*get_quoting(const char *s);
int			check_quotes_match(const int *quotes, size_t n);

int			is_operator(const char *token);
int			is_control_operator(const char *token);
int			is_redir_operator(const char *token);
int			is_logical_operator(const char *token);

int			unexp_token(const char *token);
int			unexp_eof(void);
int			ambiguous_redir(const char *redir_arg);

void		*perror_and_null(void);
void		*perror_free_word_arr_null(t_word **word_arr);
void		*perror_free_2dim_arr_null(void	**arr);
void		*perror_free_word_null(t_word *word);

void		*free_2dim_arr(void **arr);
void		*free_tree(t_cmdtree *tree);
void		*free_pipeline(t_cmd **pipeline);
void		*free_redirs(t_redir **redirs);
void		*free_redir(t_redir *redir);
void		*free_cmd(t_cmd *cmd);
void		*free_word(t_word *word);
void		*free_word_arr(t_word **words);

#endif

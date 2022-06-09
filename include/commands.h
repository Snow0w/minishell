/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:51:10 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:51:23 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H
# include <parser.h>
# include <unistd.h>

int		set_exit_status(int new_value);
int		*get_exit_status(void);

size_t	get_cmd_number(t_cmd **cmd);

void	*str_split_free(char **split);

int		err_execve_ret(char *spl);
int		check_cmd_access(char *cmd);
int		access_value_ret(int access_value, char *spl);
int		err_access_one(int access_value, char *cmd, char **envp);
int		err_execve_one(char *cmd, char **envp);
int		err_malloc_env_free(char **envp);
int		err_cmd_not_found(char **envp, char **spl, char *cmd);
int		err_cmd_not_found_ret(char *cmd);
int		wrong_name_in_path(char **envp, char **spl, int pos);

int		call_cmd(char **spl_cmd);

int		check_builtin(t_cmd *cmd);
int		simple_builtin_work(t_cmd **cmd, int status);

int		err_open_ret(char *spl);

int		simple_append_redir(char *file);
int		simple_output_redir(char *file);
int		simple_input_redir(char *file);
int		simple_here_doc_redir(char *here, int *fd);

int		pipeline_work(t_cmdtree *tree);
int		main_redir(t_redir **redirs, int *fd);
int		start(t_cmdtree *tree);
int		simple_redir_builtin(t_redir **redirs, int *fd);
int		prev_dup(int *fd);
int		put_fd_back(int *fd);
int		close_unused_pipes(int pipes[2][2], size_t i);

void	start_circle_pipes(t_cmd **cmd, int pip[2][2], size_t i, size_t num);
int		close_unused_pipes(int pipes[2][2], size_t i);
int		err_pipe_open(int pipes[2][2], size_t i);
int		err_fork_create(int pipes[2][2], size_t i);

int		builtin_work_without_redir(t_cmd *cmd, int status);

int		*get_dup_fd(void);
int		*get_here_doc_pip(void);

int		no_command_work(t_cmd **cmd);

int		simple_call_one_proc(t_cmd **cmd, int minishell);

int		minishell_recursive(t_cmd **cmd);
int		check_minishell_recursive(t_cmd *cmd);

int		open_pipes_sev_com(int pipes[2][2], size_t i, size_t num);
int		waiter(pid_t final_pid, int num);

int		common_err_msg(char *str);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:55 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:42:15 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <builtin.h>
#include <commands.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <get_next_line.h>
#include <signals.h>
#include <sys/wait.h>

int	simple_input_redir(char *file)
{
	int	fd_file;

	fd_file = open(file, O_RDONLY);
	if (fd_file == -1)
		return (err_open_ret(file));
	if (dup2(fd_file, STDIN_FILENO) == -1)
	{
		close(fd_file);
		return (err_open_ret(file));
	}
	close(fd_file);
	return (0);
}

int	simple_output_redir(char *file)
{
	int	fd_file;

	fd_file = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_file == -1)
		return (err_open_ret(file));
	if (dup2(fd_file, STDOUT_FILENO) == -1)
	{
		close(fd_file);
		return (err_open_ret(file));
	}
	close(fd_file);
	return (0);
}

int	simple_append_redir(char *file)
{
	int	fd_file;

	fd_file = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_file == -1)
		return (err_open_ret(file));
	if (dup2(fd_file, STDOUT_FILENO) == -1)
	{
		close(fd_file);
		return (err_open_ret(file));
	}
	close(fd_file);
	return (0);
}

static int	logic_here_doc(char *here, int *fd)
{
	char	*str;
	size_t	len;

	signals_redir();
	len = ft_strlen(here);
	write(fd[1], "> ", 2);
	str = get_next_line(fd[0]);
	while (str && !(!ft_strncmp(str, here, len) && len + 1 == ft_strlen(str)))
	{
		write(get_here_doc_pip()[1], str, ft_strlen(str));
		free(str);
		write(fd[1], "> ", 2);
		str = get_next_line(fd[0]);
	}
	if (str)
		free(str);
	close(get_here_doc_pip()[1]);
	close(get_here_doc_pip()[0]);
	exit(0);
}

int	simple_here_doc_redir(char *here, int *fd)
{
	pid_t	pid;
	int		status;

	if (pipe(get_here_doc_pip()) == -1)
		return (std_func_err());
	signals_ignore();
	pid = fork();
	if (pid == -1)
		return (std_func_err());
	if (pid == 0)
		return (logic_here_doc(here, fd));
	close(get_here_doc_pip()[1]);
	if (dup2(get_here_doc_pip()[0], STDIN_FILENO) == -1)
	{
		close(get_here_doc_pip()[0]);
		return (std_func_err());
	}
	close(get_here_doc_pip()[0]);
	if (waitpid(pid, &status, 0) == -1)
		return (std_func_err());
	if (WIFSIGNALED(status))
		return (1);
	return (WEXITSTATUS(status));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:02:59 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:47:37 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <variables.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <parser.h>
#include <unistd.h>
#include <stdlib.h>
#include <commands.h>
#include <signals.h>
#include <builtin.h>

char	*get_readline(char *s)
{
	if (s)
		free(s);
	s = readline("minishell> ");
	if (s && *s)
		add_history(s);
	return (s);
}

int	main(int argc, char **argv, char **envp)
{
	char		*s;
	t_cmdtree	*cmdtree;
	extern FILE	*rl_outstream;

	s = NULL;
	signals_init();
	initialize_variables(envp);
	rl_outstream = stderr;
	(void)argv;
	(void)argc;
	s = get_readline(s);
	while (s)
	{
		cmdtree = parse(s);
		if (cmdtree)
		{
			*tree_to_exit_delete() = cmdtree;
			start(cmdtree);
			free_tree(cmdtree);
		}
		signals_init();
		s = get_readline(s);
	}
	rl_clear_history();
	return (0);
}

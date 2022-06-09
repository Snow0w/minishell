/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:44:33 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:44:36 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <variables.h>
#include <libft.h>
#include <stdlib.h>
#include <parser.h>

static size_t	calc_name_len(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		++i;
	return (i);
}

void	initialize_variables(char **envp)
{
	char	*name;
	char	*value;
	size_t	i;
	size_t	name_len;
	int		len;

	i = 0;
	while (envp[i])
	{
		name_len = calc_name_len(envp[i]);
		name = ft_strndup(envp[i], name_len + 1);
		len = ft_strlen(&envp[i][name_len + 1]);
		if (!len)
			value = NULL;
		else
			value = ft_strndup(&envp[i][name_len + 1], len + 1);
		set_variable(name, value);
		++i;
	}
}

t_cmdtree	**tree_to_exit_delete(void)
{
	static t_cmdtree	*tree;

	return (&tree);
}

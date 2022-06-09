/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:44:25 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:46:07 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <variables.h>
#include <libft.h>
#include <stdlib.h>

size_t	vlist_len(void)
{
	size_t	len;
	t_vlist	*list;

	list = *get_vlist();
	len = 0;
	while (list)
	{
		if (list->value)
			len++;
		list = list->next;
	}
	return (len);
}

static t_vlist	*search_next_no_empty(t_vlist *list)
{
	while (list)
	{
		if (list->value)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	paste_line_envp(char **env, size_t i, t_vlist *list)
{
	size_t	len_name;
	size_t	len_value;

	len_name = ft_strlen(list->name);
	len_value = ft_strlen(list->value);
	env[i] = malloc(sizeof(char) * (len_name + len_value + 2));
	if (!(env[i]))
		exit(1);
	ft_strlcpy(env[i], list->name, len_name + 1);
	ft_strlcat(env[i], "=", len_name + 2);
	ft_strlcat(env[i], list->value, len_name + len_value + 2);
}

char	**get_envp_for_child_process(void)
{
	char	**env;
	t_vlist	*list;
	size_t	len;
	size_t	i;

	len = vlist_len();
	if (!len)
		return (NULL);
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		exit(1);
	i = 0;
	list = *get_vlist();
	while (list && i < len)
	{
		list = search_next_no_empty(list);
		paste_line_envp(env, i, list);
		list = list->next;
		i++;
	}
	env[len] = NULL;
	return (env);
}

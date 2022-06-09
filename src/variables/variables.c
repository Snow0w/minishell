/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:44:34 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:44:36 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <variables.h>
#include <libft.h>

t_vlist	**get_vlist(void)
{
	static t_vlist	*vlist;

	return (&vlist);
}

static char	*empty_string(void)
{
	char	*s;

	s = malloc(sizeof(*s));
	if (!s)
		return (NULL);
	s[0] = 0;
	return (s);
}

char	*get_variable(char *name)
{
	t_vlist	*vlist;
	char	*out;

	vlist = find_vlist(get_vlist(), name);
	if (!vlist)
		return (empty_string());
	if (!(vlist->value))
		return (empty_string());
	out = ft_strndup(vlist->value, ft_strlen(vlist->value) + 1);
	return (out);
}

void	set_variable(char *name, char *value)
{
	t_vlist	*vlist;

	vlist = find_vlist(get_vlist(), name);
	if (!vlist)
		push_vlist(get_vlist(), create_vlist(name, value));
	else
	{
		if (vlist->value)
			free(vlist->value);
		vlist->value = value;
	}
}

//return 0 if variable and it's value exist
int	is_var_plus_value_exist(char *name)
{
	t_vlist	*vlist;

	vlist = find_vlist(get_vlist(), name);
	if (!vlist)
		return (1);
	if (!(vlist->value))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kirill <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:44:34 by kirill            #+#    #+#             */
/*   Updated: 2022/05/23 22:44:57 by kirill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <variables.h>
#include <libft.h>
#include <stdlib.h>

t_vlist	*create_vlist(char *name, char *value)
{
	t_vlist	*vlist;

	vlist = malloc(sizeof(*vlist));
	if (!vlist)
		exit(1);
	vlist->name = name;
	vlist->value = value;
	vlist->next = NULL;
	return (vlist);
}

void	push_vlist(t_vlist **vlist, t_vlist *new)
{
	t_vlist	*cur;

	if (!*vlist)
		*vlist = new;
	else
	{
		cur = *vlist;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

void	free_vlist(t_vlist *vlist)
{
	if (vlist->name)
		free(vlist->name);
	if (vlist->value)
		free(vlist->value);
	free(vlist);
}

void	delete_vlist(t_vlist **vlist, char *name)
{
	t_vlist	*prev;
	t_vlist	*cur;

	prev = NULL;
	cur = *vlist;
	if (!cur)
		return ;
	while (cur && !ft_streq(cur->name, name))
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
		return ;
	prev->next = cur->next;
	free_vlist(cur);
}

t_vlist	*find_vlist(t_vlist **vlist, char *name)
{
	t_vlist	*cur;

	cur = *vlist;
	while (cur && !ft_streq(cur->name, name))
		cur = cur->next;
	return (cur);
}

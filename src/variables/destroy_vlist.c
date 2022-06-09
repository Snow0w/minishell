/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_vlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:34:37 by omanie            #+#    #+#             */
/*   Updated: 2022/05/25 15:34:38 by omanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <variables.h>
#include <libft.h>
#include <stdlib.h>

void	destroy_vlist(void)
{
	t_vlist	*vlist;
	t_vlist	*prev;

	vlist = *get_vlist();
	while (vlist)
	{
		prev = vlist;
		vlist = vlist->next;
		free_vlist(prev);
	}
}

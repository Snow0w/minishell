/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 03:11:39 by bgohan            #+#    #+#             */
/*   Updated: 2022/03/29 20:53:48 by omanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# include <stddef.h>

typedef struct s_vlist
{
	char			*name;
	char			*value;
	struct s_vlist	*next;
}	t_vlist;

t_vlist	**get_vlist(void);
t_vlist	*create_vlist(char *name, char *value);
void	push_vlist(t_vlist **vlist, t_vlist *new);
void	delete_vlist(t_vlist **vlist, char *name);
t_vlist	*find_vlist(t_vlist **vlist, char *name);

size_t	values_len(char **values);

void	free_vlist(t_vlist *vlist);
#endif

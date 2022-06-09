/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 06:38:30 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:57:51 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

size_t	arr_len(void **arr)
{
	size_t	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		++i;
	return (i);
}

/*
	Frees a
*/
void	**concatenate_arrays(void **a, void **b)
{
	void	**new_arr;
	size_t	i;
	size_t	j;

	new_arr = malloc(sizeof(*new_arr) * (arr_len(a) + arr_len(b) + 1));
	if (!new_arr)
		return (perror_free_2dim_arr_null(a));
	i = 0;
	j = 0;
	if (a)
	{
		while (a[j])
			new_arr[i++] = a[j++];
	}
	j = 0;
	while (b[j])
		new_arr[i++] = b[j++];
	new_arr[i] = 0;
	if (a)
		free(a);
	return (new_arr);
}

void	**append_to_arr(void **a, void *b)
{
	void	**ans;
	size_t	i;

	ans = malloc(sizeof(*ans) * (arr_len(a) + 2));
	if (!ans)
		return (perror_and_null());
	i = 0;
	while (a && a[i])
	{
		ans[i] = a[i];
		++i;
	}
	ans[i++] = b;
	ans[i] = 0;
	if (a)
		free(a);
	return (ans);
}

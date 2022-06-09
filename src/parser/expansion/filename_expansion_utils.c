/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:43:42 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:58:43 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

/*
	Frees a and b
*/
t_word	**concatenate_words(t_word **a, t_word **b)
{
	t_word	**new_arr;
	size_t	i;
	size_t	j;

	new_arr = malloc(sizeof(*new_arr) * \
							(arr_len((void **)a) + arr_len((void **)b) + 1));
	if (!new_arr)
		return (perror_free_word_arr_null(a));
	i = 0;
	j = 0;
	while (a && a[j])
			new_arr[i++] = a[j++];
	j = 0;
	while (b && b[j])
		new_arr[i++] = b[j++];
	new_arr[i] = 0;
	if (a)
		free(a);
	if (b)
		free(b);
	return (new_arr);
}

/*
	Frees words
*/
t_word	**append_word(t_word **words, t_word *a)
{
	t_word	**arr;
	t_word	**ans;

	if (!a)
		return (free_word_arr(words));
	arr = malloc(sizeof(*arr) * 2);
	if (!arr)
		return (perror_free_word_arr_null(words));
	arr[0] = a;
	arr[1] = 0;
	ans = concatenate_words(words, arr);
	return (ans);
}

DIR	*open_cwd(void)
{
	char	*cwd;
	DIR		*dirp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror_and_null());
	dirp = opendir(cwd);
	free(cwd);
	if (!dirp)
		return (perror_and_null());
	return (dirp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:39:42 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 12:04:24 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdio.h>

void	*perror_and_null(void)
{
	perror("minishell");
	return (NULL);
}

void	*perror_free_word_arr_null(t_word **word_arr)
{
	free_word_arr(word_arr);
	return (perror_and_null());
}

void	*perror_free_2dim_arr_null(void	**arr)
{
	free_2dim_arr(arr);
	return (perror_and_null);
}

void	*perror_free_word_null(t_word *word)
{
	free_word(word);
	return (perror_and_null());
}

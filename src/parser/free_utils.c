/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:38:11 by bgohan            #+#    #+#             */
/*   Updated: 2022/05/18 22:06:19 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

void	*free_2dim_arr(void **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

void	*free_tree(t_cmdtree *tree)
{
	if (!tree)
		return (NULL);
	if (tree->type == OR || tree->type == AND)
	{
		free_tree(tree->arg1);
		free_tree(tree->arg2);
	}
	else if (tree->type == GROUP)
	{
		free_tree(tree->arg1);
		free_redirs(tree->arg2);
	}
	else
	{
		free_pipeline(tree->arg1);
	}
	free(tree);
	return (NULL);
}

void	*free_pipeline(t_cmd **pipeline)
{
	size_t	i;

	if (!pipeline)
		return (NULL);
	i = 0;
	while (pipeline[i])
		free_cmd(pipeline[i++]);
	free(pipeline);
	return (NULL);
}

void	*free_redirs(t_redir **redirs)
{
	size_t	i;

	if (!redirs)
		return (NULL);
	i = 0;
	while (redirs[i])
		free_redir(redirs[i++]);
	free(redirs);
	return (NULL);
}

void	*free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	free_2dim_arr((void **)cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgohan <bgohan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:22:52 by bgohan            #+#    #+#             */
/*   Updated: 2022/06/02 11:53:47 by bgohan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <libft.h>
#include <stdlib.h>

static void	append_to_tree(t_cmdtree **tree, t_cmdtree *node)
{
	if (!*tree)
	{
		*tree = node;
		return ;
	}
	if (node->type == OR || node->type == AND)
	{
		node->arg1 = *tree;
		*tree = node;
	}
	else
		(*tree)->arg2 = node;
}

static t_cmdtree	*create_node(const char *s)
{
	t_cmdtree	*node;

	if (ft_streq(s, ")"))
		return (NULL);
	node = malloc(sizeof(*node));
	if (!node)
		return (perror_and_null());
	if (ft_streq(s, "||"))
		node->type = OR;
	else if (ft_streq(s, "&&"))
		node->type = AND;
	else if (ft_streq(s, "("))
		node->type = GROUP;
	else
		node->type = PIPELINE;
	node->arg1 = NULL;
	node->arg2 = NULL;
	return (node);
}

static t_cmdtree	*process_group(char **splitted, size_t *ret_len)
{
	t_cmdtree	*node;
	size_t		len;

	node = create_node(splitted[0]);
	if (!node)
		return (NULL);
	node->arg1 = arr_to_tree(&splitted[1], &len);
	if (!node->arg1)
		return (free_tree(node));
	*ret_len = 2 + len;
	node->arg2 = parse_redirs(&splitted[len + 2], &len);
	if (!node->arg2)
		return (free_tree(node));
	*ret_len += len;
	return (node);
}

static t_cmdtree	*process_pipeline(char **splitted, size_t *ret_len)
{
	t_cmdtree	*node;

	node = create_node(splitted[0]);
	if (!node)
		return (NULL);
	node->arg1 = parse_pipeline(splitted, ret_len);
	if (!node->arg1)
		return (free_tree(node));
	return (node);
}

t_cmdtree	*arr_to_tree(char **splitted, size_t *ret_len)
{
	t_cmdtree	*tree;
	t_cmdtree	*node;
	size_t		len;
	size_t		i;

	tree = NULL;
	i = 0;
	while (splitted[i] && !ft_streq(splitted[i], ")"))
	{
		len = 1;
		if (ft_streq(splitted[i], "("))
			node = process_group(&splitted[i], &len);
		else if (!is_control_operator(splitted[i]))
			node = process_pipeline(&splitted[i], &len);
		else
			node = create_node(splitted[i]);
		if (!node)
			return (free_tree(tree));
		append_to_tree(&tree, node);
		i += len;
	}
	if (ret_len)
		*ret_len = i;
	return (tree);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:13:45 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/29 15:13:51 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Free map and print an error's description
*/
void	free_from_map(t_env *data, char *str)
{
	free_map_array(data);
	print_error(str);
}

/*
** Free node(s) of each collectible
*/
void	free_coll_nodes(t_env *data, t_coll *node)
{
	if (node)
	{
		if (node && node->next)
		{
			free_coll_nodes(data, node->next);
			node->next = NULL;
		}
		if (!node->next)
		{
			free(node);
			node = NULL;
		}
	}
}

/*
** Free node(s) of each exit
*/
void	free_exit_nodes(t_env *data, t_exit *node)
{
	if (node)
	{
		if (node && node->next)
		{
			free_exit_nodes(data, node->next);
			node->next = NULL;
		}
		if (!node->next)
		{
			free(node);
			node = NULL;
		}
	}
}

/*
** Free map, exit and collectible nodes, and print an error's description
*/
void	free_after_map(t_env *data, char *str)
{
	free_map_array(data);
	free_exit_nodes(data, data->map.exit_pos);
	free_coll_nodes(data, data->map.coll_pos);
	print_error(str);
}

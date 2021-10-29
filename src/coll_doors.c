/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:19:26 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/29 15:19:29 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Save player position and check that there is only one player in the map
*/
void	save_player_pos(t_env *data, int x, int y)
{
	if (data->map.player_pos_x == -1)
	{
		data->map.player_pos_x = x;
		data->map.player_pos_y = y;
		data->map_array[y][x] = '0';
	}
	else
		free_after_map(data,
			"there is more than one player in map description");
}

int	enjoy_coll(t_env *data, int *x_y, int i, t_coll **ptr)
{
	if (!*ptr)
	{
		*ptr = (t_coll *)malloc(sizeof(t_coll));
		if (!(*ptr))
			return (0);
		(*ptr)->coll_nb = i;
		(*ptr)->x = x_y[0];
		(*ptr)->y = x_y[1];
		(*ptr)->next = NULL;
		data->map.coll_pos = *ptr;
	}
	else if (!(*ptr)->next)
	{
		((*ptr)->next = (t_coll *)malloc(sizeof(t_coll)));
		if (!((*ptr)->next))
			return (0);
		(*ptr) = (*ptr)->next;
		(*ptr)->coll_nb = i + 1;
		(*ptr)->x = x_y[0];
		(*ptr)->y = x_y[1];
		(*ptr)->next = NULL;
	}
	return (1);
}

/*
** Create or add a collectible position node and save it
*/
t_coll	*save_coll_pos(t_env *data, int x, int y)
{
	t_coll	*ptr;
	int		i;
	int		xy[2];

	xy[0] = x;
	xy[1] = y;
	ptr = data->map.coll_pos;
	i = 1;
	while (ptr && ptr->next)
	{
		ptr = ptr->next;
		i++;
	}
	if (!enjoy_coll(data, xy, i, &ptr))
		return (NULL);
	data->map_array[y][x] = '0';
	return (ptr);
}

int	enjoy_exit(t_env *data, int *x_y, int i, t_exit **ptr)
{
	if (!*ptr)
	{
		*ptr = (t_exit *)malloc(sizeof(t_exit));
		if (!(*ptr))
			return (0);
		(*ptr)->exit_nb = i;
		(*ptr)->x = x_y[0];
		(*ptr)->y = x_y[1];
		(*ptr)->next = NULL;
		data->map.exit_pos = *ptr;
	}
	else if (!(*ptr)->next)
	{
		((*ptr)->next = (t_exit *)malloc(sizeof(t_exit)));
		if (!((*ptr)->next))
			return (0);
		(*ptr) = (*ptr)->next;
		(*ptr)->exit_nb = i + 1;
		(*ptr)->x = x_y[0];
		(*ptr)->y = x_y[1];
		(*ptr)->next = NULL;
	}
	return (1);
}

/*
** Create or add an exit position node and save it
*/
t_exit	*save_exit_pos(t_env *data, int x, int y)
{
	t_exit	*ptr;
	int		i;
	int		xy[2];

	xy[0] = x;
	xy[1] = y;
	ptr = data->map.exit_pos;
	i = 1;
	while (ptr && ptr->next)
	{
		ptr = ptr->next;
		i++;
	}
	if (!enjoy_exit(data, xy, i, &ptr))
		return (NULL);
	data->map_array[y][x] = '0';
	return (ptr);
}

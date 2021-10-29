/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:09:43 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/18 19:10:12 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	engine_handler(t_env *data)
{
	data->ptr.mlx = mlx_init();
	if (!data->ptr.mlx)
		free_after_map(data, "mlx_init() failed");
	data->ptr.win = mlx_new_window(data->ptr.mlx, data->map.win_width,
			data->map.win_height, "so_long");
	if (!data->ptr.win)
		free_engine(data, "mlx_new_window() failed");
	data->ptr.img = mlx_new_image(data->ptr.mlx, data->map.win_width,
			data->map.win_height);
	if (!data->ptr.img)
		free_engine(data, "mlx_new_image() failed");
	data->img.addr = mlx_get_data_addr(data->ptr.img, &data->img.bpp,
			&data->img.size_line, &data->img.endian);
	if (!data->img.addr)
		free_engine(data, "mlx_get_data_address() failed (img)");
	init_text(data);
	render_it(data);
	mlx_key_hook(data->ptr.win, key_handler, data);
	mlx_hook(data->ptr.win, DESTROYNOTIFY, 1L << 17, red_cross_exit, data);
	mlx_loop(data->ptr.mlx);
}

int	ft_is_coll(t_env *data, int x, int y)
{
	t_coll	*tmp;

	tmp = data->map.coll_pos;
	while (tmp && (tmp->x != x || tmp->y != y))
		tmp = tmp->next;
	if (!tmp)
		return (0);
	return (1);
}

void	destroy_coll(t_env *data, int x, int y)
{
	t_coll	*tmp;
	t_coll	*prevone;
	t_coll	*nextone;

	prevone = data->map.coll_pos;
	tmp = data->map.coll_pos;
	if (tmp->x == x && tmp->y == y)
	{
		data->map.coll_pos = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp && (tmp->x != x || tmp->y != y))
	{	
		prevone = tmp;
		tmp = tmp->next;
	}
	nextone = tmp->next;
	free(tmp);
	tmp = NULL;
	prevone->next = nextone;
}

int	ft_is_exit(t_env *data, int x, int y)
{
	t_exit	*tmp;

	tmp = data->map.exit_pos;
	while (tmp && (tmp->x != x || tmp->y != y))
		tmp = tmp->next;
	if (!tmp)
		return (0);
	return (1);
}

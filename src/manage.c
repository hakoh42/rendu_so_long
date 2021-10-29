/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:34:18 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/29 15:34:21 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_env *data, int x, int y)
{
	if (data->map_array[y][x] == '0')
	{
		data->map.player_pos_x = x;
		data->map.player_pos_y = y;
		if (ft_is_coll(data, x, y))
			destroy_coll(data, x, y);
		else if (ft_is_exit(data, x, y))
			game_finished(data);
		data->count++;
		ft_printf("steps count = %d\r", data->count);
	}
}

int	key_handler(int keycode, t_env *data)
{
	if (keycode == ESC_KEY)
		final_free(data);
	if (keycode == W_KEY)
	{
		move_player(data, data->map.player_pos_x, data->map.player_pos_y - 1);
		render_it(data);
	}
	else if (keycode == A_KEY)
	{
		move_player(data, data->map.player_pos_x - 1, data->map.player_pos_y);
		render_it(data);
	}
	else if (keycode == S_KEY)
	{
		move_player(data, data->map.player_pos_x, data->map.player_pos_y + 1);
		render_it(data);
	}
	else if (keycode == D_KEY)
	{
		move_player(data, data->map.player_pos_x + 1, data->map.player_pos_y);
		render_it(data);
	}
	return (keycode);
}

int	get_color(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	return (*(int *)dst);
}

void	game_finished(t_env *data)
{
	if (!data->map.coll_pos)
	{
		ft_printf("CONGRATS! You ended this level with %d steps\n", data->count);
		final_free(data);
	}
}

int	red_cross_exit(t_env *data)
{
	final_free(data);
	return (42);
}

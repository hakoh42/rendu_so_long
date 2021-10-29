/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:34:54 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/29 15:34:56 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_it(t_env *data)
{
	draw(data, 0, 0, 0);
	draw_player(data, 0, 0, 0);
	mlx_put_image_to_window(data->ptr.mlx, data->ptr.win, data->ptr.img, 0, 0);
}

void	print_or_not(t_env *data, int j, int i, int color)
{
	if (color > 0)
		my_mlx_pixel_put(data, j, i, color);
}

void	draw_player(t_env *data, int y, int i, int j)
{
	int			x;

	while (i < data->map.win_height)
	{
		x = 0;
		j = 0;
		while (j < data->map.win_width)
		{
			if (x == data->map.player_pos_x && y == data->map.player_pos_y)
				print_or_not(data, j, i, get_color(&data->player,
						j % RATIO_WIDTH, i % RATIO_HEIGHT));
			else if (ft_is_coll(data, x, y))
				print_or_not(data, j, i, get_color(&data->coll,
						j % RATIO_WIDTH, i % RATIO_HEIGHT));
			else if (ft_is_exit(data, x, y))
				print_or_not(data, j, i, get_color(&data->exit,
						j % RATIO_WIDTH, i % RATIO_HEIGHT));
			j++;
			if (j % RATIO_WIDTH == 0)
				x++;
		}
		i++;
		if (i % RATIO_HEIGHT == 0)
			y++;
	}
}

void	draw(t_env *data, int y, int i, int j)
{
	int	x;

	while (i < data->map.win_height)
	{
		x = 0;
		j = 0;
		while (j < data->map.win_width)
		{
			if (data->map_array[y][x] == '1')
				my_mlx_pixel_put(data, j, i, get_color(&data->wall,
						j % RATIO_WIDTH, i % RATIO_HEIGHT));
			else
				my_mlx_pixel_put(data, j, i, get_color(&data->floor,
						j % RATIO_WIDTH, i % RATIO_HEIGHT));
			j++;
			if (j % RATIO_WIDTH == 0)
				x++;
		}
		i++;
		if (i % RATIO_HEIGHT == 0)
			y++;
	}
}

void	my_mlx_pixel_put(t_env *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.size_line + x * (data->img.bpp / 8));
	*(unsigned int *)dst = color;
}

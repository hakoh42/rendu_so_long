/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:43:26 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/29 15:43:29 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_text(t_env *data)
{
	data->text.wall = mlx_xpm_file_to_image(data->ptr.mlx, WALL_TEXT,
			&data->text.wall_x, &data->text.wall_y);
	if (!data->text.wall)
		free_engine(data, "mlx_xpm_file_to_image() failed (wall)");
	data->wall.addr = mlx_get_data_addr(data->text.wall, &data->wall.bpp,
			&data->wall.size_line, &data->wall.endian);
	if (!data->wall.addr)
		free_engine(data, "mlx_get_data_address() failed (wall)");
	data->text.floor = mlx_xpm_file_to_image(data->ptr.mlx, FLOOR_TEXT,
			&data->text.floor_x, &data->text.floor_y);
	if (!data->text.floor)
		free_engine(data, "mlx_xpm_file_to_image() failed (floor)");
	data->floor.addr = mlx_get_data_addr(data->text.floor, &data->floor.bpp,
			&data->floor.size_line, &data->floor.endian);
	if (!data->floor.addr)
		free_engine(data, "mlx_get_data_address() failed (floor)");
	data->text.player = mlx_xpm_file_to_image(data->ptr.mlx, PLAYER_TEXT,
			&data->text.player_x, &data->text.player_y);
	if (!data->text.player)
		free_engine(data, "mlx_xpm_file_to_image() failed (player)");
	data->player.addr = mlx_get_data_addr(data->text.player, &data->player.bpp,
			&data->player.size_line, &data->player.endian);
	init_next(data);
}

void	init_next(t_env *data)
{
	if (!data->player.addr)
		free_engine(data, "mlx_get_data_address() failed (player)");
	data->text.coll = mlx_xpm_file_to_image(data->ptr.mlx, COLL_TEXT,
			&data->text.coll_x, &data->text.coll_y);
	if (!data->text.player)
		free_engine(data, "mlx_xpm_file_to_image() failed (collectible)");
	data->coll.addr = mlx_get_data_addr(data->text.coll, &data->coll.bpp,
			&data->coll.size_line, &data->coll.endian);
	if (!data->coll.addr)
		free_engine(data, "mlx_get_data_address() failed (collectible)");
	data->text.exit = mlx_xpm_file_to_image(data->ptr.mlx, DOOR_TEXT,
			&data->text.exit_x, &data->text.exit_y);
	if (!data->text.exit)
		free_engine(data, "mlx_xpm_file_to_image() failed (exit_door)");
	data->exit.addr = mlx_get_data_addr(data->text.exit, &data->exit.bpp,
			&data->exit.size_line, &data->exit.endian);
	if (!data->exit.addr)
		free_engine(data, "mlx_get_data_address() failed (exit_door)");
}

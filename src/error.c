/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 21:08:11 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/16 19:34:09 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Free all malocated data and print an error's description
*/
void	free_engine(t_env *data, char *str)
{
	free_map_array(data);
	free_coll_nodes(data, data->map.coll_pos);
	free_exit_nodes(data, data->map.exit_pos);
	if (data->ptr.img)
		mlx_destroy_image(data->ptr.mlx, data->ptr.img);
	if (data->text.wall)
		mlx_destroy_image(data->ptr.mlx, data->text.wall);
	if (data->text.floor)
		mlx_destroy_image(data->ptr.mlx, data->text.floor);
	if (data->text.player)
		mlx_destroy_image(data->ptr.mlx, data->text.player);
	if (data->text.exit)
		mlx_destroy_image(data->ptr.mlx, data->text.exit);
	if (data->text.coll)
		mlx_destroy_image(data->ptr.mlx, data->text.coll);
	if (data->ptr.win)
		mlx_destroy_window(data->ptr.mlx, data->ptr.win);
	mlx_destroy_display(data->ptr.mlx);
	free(data->ptr.mlx);
	print_error(str);
}

/*
** Free all before quit
*/
void	final_free(t_env *data)
{
	free_map_array(data);
	free_coll_nodes(data, data->map.coll_pos);
	free_exit_nodes(data, data->map.exit_pos);
	if (data->ptr.img)
		mlx_destroy_image(data->ptr.mlx, data->ptr.img);
	if (data->text.wall)
		mlx_destroy_image(data->ptr.mlx, data->text.wall);
	if (data->text.floor)
		mlx_destroy_image(data->ptr.mlx, data->text.floor);
	if (data->text.player)
		mlx_destroy_image(data->ptr.mlx, data->text.player);
	if (data->text.exit)
		mlx_destroy_image(data->ptr.mlx, data->text.exit);
	if (data->text.coll)
		mlx_destroy_image(data->ptr.mlx, data->text.coll);
	if (data->ptr.win)
		mlx_destroy_window(data->ptr.mlx, data->ptr.win);
	mlx_destroy_display(data->ptr.mlx);
	free(data->ptr.mlx);
	exit(0);
}

/*
** Print the current error and exit the program
*/
void	print_error(char *str)
{
	ft_printf("Error\n%s\n", str);
	exit(0);
}

/*
** Free map_buffer and line and print an error's description
*/
void	free_from_parsing(int fd, char *map_buffer, char *line, char *str)
{
	close(fd);
	free(map_buffer);
	free(line);
	print_error(str);
}

/*
** Free map_array
*/
void	free_map_array(t_env *data)
{
	int	len;

	len = array_len(data->map_array);
	ft_free_split(len, data->map_array);
}

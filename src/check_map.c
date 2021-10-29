/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:23:15 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/29 15:23:18 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Check validity of the map
*/
void	check_map(t_env *data, char **map)
{
	char	*top;
	char	*bottom;

	if (array_len(map) < 3)
		free_from_map(data, "map is too short");
	top = map[0];
	bottom = map[array_len(map) - 1];
	if (!check_map_tops(top) || !check_map_tops(bottom))
		free_from_map(data, "map isn't surrounded by '1'");
	if (!check_map_rows(data, map, 0))
		free_after_map(data,
			"map isn't surrounded by '1' or there is an invalid map char");
	if (!data->map.exit_pos)
		free_after_map(data, "there isn't exit door in map_file");
	if (!data->map.coll_pos)
		free_after_map(data, "there isn't collectible in map_file");
	if (data->map.player_pos_x == -1)
		free_after_map(data, "there isn't player in map_file");
	data->map.win_width = RATIO_WIDTH * data->map.width_map;
	data->map.win_height = RATIO_HEIGHT * data->map.height_map;
}

/*
** Check if the first and the last rows are composed only by '1'
*/
int	check_map_tops(char *map_line)
{
	int	i;

	i = 0;
	while (map_line && map_line[i])
	{
		if (!ft_is_in_str(map_line[i], "1"))
			return (0);
		i++;
	}
	return (1);
}

/*
** Check validity of each line of file
*/
int	check_map_rows(t_env *data, char **map, int i)
{
	int	j;

	while (map && map[i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_is_in_str(map[i][j], MAP_CHAR) ||
				!well_surrounded(data, map[i]))
				return (0);
			if (map[i][j] == 'P')
				save_player_pos(data, j, i);
			if (map[i][j] == 'E')
				if (!save_exit_pos(data, j, i))
					free_after_map(data,
						"malloc() failed during exit door saving");
			if (map[i][j] == 'C')
				if (!save_coll_pos(data, j, i))
					free_after_map(data,
						"malloc() failed during collectibles saving");
		}
		i++;
	}
	data->map.height_map = i;
	return (1);
}

/*
** Check that each row start end finish by '1' and have the good lenght
*/
int	well_surrounded(t_env *data, char *map_row)
{
	int	i;

	i = 0;
	while (map_row[i])
	{
		if (map_row[i] && map_row[i] != '1')
			return (0);
		while (map_row[i] && ft_is_in_str(map_row[i], MAP_CHAR))
			i++;
		if (map_row[i - 1] != '1')
			return (0);
	}
	if (data->map.width_map == -1)
		data->map.width_map = i;
	if (i != data->map.width_map)
		free_after_map(data, "only rectangular map allowed");
	return (1);
}

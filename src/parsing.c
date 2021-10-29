/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 21:08:41 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/17 16:31:54 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** parsing handler
*/
void	parsing_handler(t_env *data, int ac, char **av)
{
	init_env(data);
	check_args(ac, av);
	parse_file(data, av[1], NULL);
}

/*
** Initialisation of each variable in t_env structure
*/
void	init_env(t_env *data)
{
	ft_bzero(data, sizeof(t_env));
	data->map.player_pos_x = -1;
	data->map.width_map = -1;
}

/*
** Check the Usage and the input file extension
*/
void	check_args(int ac, char **av)
{
	int	len;

	if (ac < 2)
		print_error("Usage : ./so_long map_file_name.ber");
	len = ft_strlen(av[1]);
	if (len < 5 || ft_strcmp(av[1] + len - 4, ".ber") != 0)
		print_error("map_file should be ended by '.ber'");
}

/*
** Open, read and check the validity of the input file
*/
void	parse_file(t_env *data, char *file_name, char *map_buffer)
{
	int		gnl_ret;
	char	*line;

	data->fd = open(file_name, O_RDONLY);
	if (data->fd < 0)
		print_error("Open() failed on map_file");
	gnl_ret = get_next_line(data->fd, &line);
	while (gnl_ret >= 0)
	{
		parse_line(data, line, &map_buffer);
		free(line);
		line = NULL;
		if (!gnl_ret)
			break ;
		gnl_ret = get_next_line(data->fd, &line);
	}
	if (gnl_ret == -1)
		free_from_parsing(data->fd, map_buffer, line,
			"Error during file reading [in gnl]");
	data->map_array = ft_split(map_buffer, '|');
	if (!data->map_array)
		free_from_parsing(data->fd, map_buffer, line,
			"Malloc() Error during parsing [split_map_buffer]");
	parse_file_friend(data, map_buffer, line);
}

void	parse_file_friend(t_env *data, char *map_buffer, char *line)
{
	free(map_buffer);
	free(line);
	close(data->fd);
	check_map(data, data->map_array);
}

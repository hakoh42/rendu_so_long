/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:25:50 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/29 15:25:52 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Check each line of map_file and save map in a buffer
*/
void	parse_line(t_env *data, char *line, char **map_buffer)
{
	int	i;

	i = 0;
	if (!line)
		print_error("map_file invalid");
	if (!line[i])
	{
		if (data->map.map_started && !data->map.ended)
			data->map.ended = 1;
		return ;
	}
	if (ft_is_in_str(line[i], MAP_CHAR))
	{
		if (!data->map.map_started)
			data->map.map_started = 1;
		else if (data->map.ended)
			free_from_parsing(data->fd, *map_buffer, line, "map invalid");
		*map_buffer = map_line_cat(*map_buffer, line);
		if (!(*map_buffer))
			free_from_parsing(data->fd, *map_buffer, line,
				"Malloc error during map saving");
	}
	else
		else_case(data, map_buffer, line);
}

void	else_case(t_env *data, char **map_buffer, char *line)
{
	if (!data->map.map_started)
	{
		close(data->fd);
		print_error("There is an invalid char in your map_file");
	}
	free_from_parsing(data->fd, *map_buffer, line,
		"There is an invalid char in your map_file");
}

/*
** Like an strcat that malloc our new_string and free the old one
*/
char	*map_line_cat(char *map_buf, char *line)
{
	int			i;
	int			j;
	char		*str;

	i = 0;
	if (map_buf)
		i = ft_strlen(map_buf);
	j = ft_strlen(line);
	str = (char *)malloc(sizeof(char) * (i + j + 2));
	if (!str)
		return (NULL);
	if (map_buf)
		ft_strcpy(str, map_buf);
	j = 0;
	while (line && line[j])
	{
		str[i + j] = line[j];
		j++;
	}
	str[i + j] = '|';
	str[i + j + 1] = '\0';
	free(map_buf);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 21:02:58 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/16 19:49:36 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

# define RATIO_WIDTH 64
# define RATIO_HEIGHT 64
# define MAP_CHAR "01CEP"
# define WALL_TEXT "./textures/bricks.xpm"
# define FLOOR_TEXT "./textures/sand.xpm"
# define PLAYER_TEXT "./textures/crab.xpm"
# define COLL_TEXT "./textures/collectible.xpm"
# define DOOR_TEXT "./textures/door.xpm"
# define A_KEY 97
# define D_KEY 100
# define S_KEY 115
# define W_KEY 119
# define ESC_KEY 65307
# define DESTROYNOTIFY 17

typedef struct s_coll
{
	int				coll_nb;
	int				x;
	int				y;
	struct s_coll	*next;
}	t_coll;

typedef struct s_exit
{
	int				exit_nb;
	int				x;
	int				y;
	struct s_exit	*next;
}	t_exit;

typedef struct s_event
{
	int			key_esc;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
}	t_event;

typedef struct s_mlxptr
{
	void			*mlx;
	void			*win;
	void			*img;
}	t_mlxptr;

typedef struct s_img
{
	char			*addr;
	int				endian;
	int				bpp;
	int				size_line;
}	t_img;

typedef struct s_mapdata
{
	char			map_started;
	char			ended;
	int				height_map;
	int				width_map;
	int				win_width;
	int				win_height;
	int				player_pos_x;
	int				player_pos_y;
	t_exit			*exit_pos;
	t_coll			*coll_pos;
}	t_mapdata;

typedef struct s_text
{
	void			*wall;
	int				wall_x;
	int				wall_y;
	void			*floor;
	int				floor_x;
	int				floor_y;
	void			*player;
	int				player_x;
	int				player_y;
	void			*coll;
	int				coll_x;
	int				coll_y;
	void			*exit;
	int				exit_x;
	int				exit_y;
}	t_text;

typedef struct s_env
{
	t_mapdata		map;
	char			**map_array;
	t_mlxptr		ptr;
	t_event			event;
	t_img			img;
	t_img			wall;
	t_img			floor;
	t_img			player;
	t_img			coll;
	t_img			exit;
	t_text			text;
	int				count;
	int				fd;
}	t_env;

/*
** error.c
*/
void		free_engine(t_env *data, char *str);
void		final_free(t_env *data);
void		print_error(char *str);
void		free_from_parsing(int fd, char *map_buffer, char *line, char *str);
void		free_map_array(t_env *data);

/*
** free.c
*/
void		free_from_map(t_env *data, char *str);
void		free_coll_nodes(t_env *data, t_coll *node);
void		free_exit_nodes(t_env *data, t_exit *node);
void		free_after_map(t_env *data, char *str);

/*
** parsing.c
*/
void		parsing_handler(t_env *data, int ac, char **av);
void		init_env(t_env *data);
void		check_args(int ac, char **av);
void		parse_file(t_env *data, char *file_name, char *map_buffer);
void		parse_file_friend(t_env *data, char *map_buffer, char *line);

/*
** parse_line.c
*/
void		parse_line(t_env *data, char *line, char **map_buffer);
void		else_case(t_env *data, char **map_buffer, char *line);
char		*map_line_cat(char *map_buf, char *line);

/*
** check_map.c
*/
void		check_map(t_env *data, char **map);
int			check_map_tops(char *map_line);
int			check_map_rows(t_env *data, char **map, int i);
int			well_surrounded(t_env *data, char *map_row);

/*
** coll_doors.c
*/
void		save_player_pos(t_env *data, int x, int y);
int			enjoy_coll(t_env *data, int *x_y, int i, t_coll **ptr);
t_coll		*save_coll_pos(t_env *data, int x, int y);
int			enjoy_exit(t_env *data, int *x_y, int i, t_exit **ptr);
t_exit		*save_exit_pos(t_env *data, int x, int y);

/*
** engine.c
*/
void		engine_handler(t_env *data);
int			ft_is_coll(t_env *data, int x, int y);
void		destroy_coll(t_env *data, int x, int y);
int			ft_is_exit(t_env *data, int x, int y);

/*
** textures.c
*/
void		init_text(t_env *data);
void		init_next(t_env *data);

/*
** manage.c
*/
void		move_player(t_env *data, int x, int y);
int			key_handler(int keycode, t_env *data);
int			get_color(t_img *img, int x, int y);
void		game_finished(t_env *data);
int			red_cross_exit(t_env *data);

/*
** render.c
*/
void		render_it(t_env *data);
void		print_or_not(t_env *data, int j, int i, int color);
void		draw_player(t_env *data, int y, int i, int j);
void		draw(t_env *data, int y, int i, int j);
void		my_mlx_pixel_put(t_env *data, int x, int y, int color);

#endif
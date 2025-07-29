/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:46:26 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 23:20:06 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include "log_msg.h"
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.14159265358979323846

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_data;

typedef struct s_position
{
	int			x;
	int			y;
}				t_position;

typedef struct s_camera
{
	t_vector	dir;
	t_vector	plane;
	t_vector	ray_dir;
}				t_camera;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_position	map_square;
	t_vector	ray_dir;
	int			step_x;
	int			step_y;
	double		size_ray;
	double		tall_of_wall;
	int			text_x;
	int			text_y;
	int			tall_of_wall_y1;
	int			tall_of_wall_y2;
	int			hit_side;
	double		dist_to_side_x;
	double		dist_to_side_y;
	double		delta_dist_x;
	double		delta_dist_y;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			pixel;
	int			game_h;
	int			game_w;
	int			color_floor;
	int			color_ceiling;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	t_data		north_img;
	t_data		south_img;
	t_data		east_img;
	t_data		west_img;
	char		*line;
	char		**colors;
	int			ceiling;
	int			floor;
	int			start_map;
	char		*temp_map;
	char		spawn;
	char		**map;
	int			empty_line;
	t_data		frame;
	t_player	player;
	int			step_y;
}				t_game;

void			parse_file(t_game *cub3d, char *file);
void			parse_line(t_game *cub3d, char *line, int i);
void			check_color(t_game *cub3d, char *color, int face);
void			check_texture(t_game *cub3d, char *file, int face);

int				have_numbers(char *str);
int				have_all_params(t_game *cub3d);
void			check_filename(t_game *cub3d, char *file, int mode);
void			check_texture_file(t_game *cub3d, char *file, int fd);
char			*get_value(char *line, int i, int mode);

void			parse_map(t_game *cub3d, int fd);
int				is_surrounded_by_walls(t_game *cub3d, int direction, int i,
					int j);
void			check_map(t_game *cub3d, int i, int j);
void			parse_map_line(t_game *cub3d, char *line);
int				is_empty_line(t_game *cub3d, char *line);

void			rotate_vector(t_vector *v, double angle);
void			set_direction(t_game *cub3d);
void			set_player_position(t_game *cub3d, int i, int j);

void			calculate_delta(t_game *g);
void			dda(t_game *g);
void			calculate_distance(t_game *g);
void			calculate_height_wall(t_game *game);

t_vector		mult_vector(t_vector *v, double n);
t_vector		add_vector(t_vector *v1, t_vector *v2);
double			perpendicular_dist_x(t_player *p, int step_x);
double			perpendicular_dist_y(t_player *p, int step_y);

double			dist_to_wall_y(t_player *p);
double			dist_to_wall_x(t_player *p);

void			render_collumn_pixel(t_game *cub3d);
void			calculate_current_ray(t_game *cub3d);
int				rayscasting(t_game *g);
int				render_game(t_game *cub3d);

void			map_position_square(t_player *player);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
int				create_background(t_game *g);

void			move_positionx(t_game *game, t_vector *dir, int direction);
void			move_positiony(t_game *game, t_vector *dir, int direction);
void			rotate_right(t_game *game);
void			rotate_left(t_game *game);
int				read_keys(int keypress, t_game *game);

int				exit_error(t_game *cub3d, char *msg);
void			free_split(char **split);
void			clean_parse(t_game *cub3d);
void			invalid_xpm_error(t_game *game, char *msg);
int				end_game(t_game *game);

void			init_game(t_game *cub3d);
void			init_player(t_player *player);
void			init_textures(t_game *cub3d, int size);
void			get_screen_size(t_game *cub3d, void *mlx, void *win, int split);

int				obtain_color(t_game *cub3d);
void			find_out_text_x(t_player *player);

#endif

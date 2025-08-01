/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:37:21 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 22:42:20 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	map_position_square(t_player *player)
{
	player->map_square.x = floor(player->pos.x);
	player->map_square.y = floor(player->pos.y);
}

void	my_mlx_pixel_put(t_game *cub3d, int x, int y, int color)
{
	char	*dst;

	dst = cub3d->frame.addr + (y * cub3d->frame.line_len + x * (cub3d->frame.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

static inline int	create_floor(t_game *g)
{
	int	x;
	int	y;

	y = g->game_h / 2;
	x = 0;
	while (y < g->game_h)
	{
		x = 0;
		while (x < g->game_w)
		{
			my_mlx_pixel_put(g, x, y, g->floor);
			x++;
		}
		y++;
	}
	return (0);
}

static inline int	create_ceiling(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < g->game_h)
	{
		x = 0;
		while (x < g->game_w)
		{
			my_mlx_pixel_put(g, x, y, g->ceiling);
			x++;
		}
		y++;
	}
	return (0);
}

int	create_background(t_game *g)
{
	create_ceiling(g);
	create_floor(g);
	return (0);
}

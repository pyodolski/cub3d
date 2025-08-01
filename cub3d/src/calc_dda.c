/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_dda.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:54:04 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 22:42:14 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

double	get_distance(t_game *g, int less_zero, int is_x)
{
	if (is_x && less_zero)
		return ((g->player.pos.x - g->player.map_square.x)
			* g->player.delta_dist_x);
	else if (is_x && !less_zero)
		return ((g->player.map_square.x + 1.0 - g->player.pos.x)
			* g->player.delta_dist_x);
	else if (!is_x && less_zero)
		return ((g->player.pos.y - g->player.map_square.y)
			* g->player.delta_dist_y);
	else
		return ((g->player.map_square.y + 1.0 - g->player.pos.y)
			* g->player.delta_dist_y);
}

void	calculate_delta(t_game *g)
{
	g->player.delta_dist_x = fabs(1 / g->player.ray_dir.x);
	g->player.delta_dist_y = fabs(1 / g->player.ray_dir.y);
	if (g->player.ray_dir.x < 0)
	{
		g->player.dist_to_side_x = get_distance(g, YES, YES);
		g->player.step_x = -1;
	}
	else
	{
		g->player.dist_to_side_x = get_distance(g, NO, YES);
		g->player.step_x = 1;
	}
	if (g->player.ray_dir.y < 0)
	{
		g->player.dist_to_side_y = get_distance(g, YES, NO);
		g->player.step_y = -1;
	}
	else
	{
		g->player.dist_to_side_y = get_distance(g, NO, NO);
		g->player.step_y = 1;
	}
}

void	dda(t_game *g)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (g->player.dist_to_side_x < g->player.dist_to_side_y)
		{
			g->player.dist_to_side_x += g->player.delta_dist_x;
			g->player.map_square.x += g->player.step_x;
			g->player.hit_side = 0;
		}
		else
		{
			g->player.dist_to_side_y += g->player.delta_dist_y;
			g->player.map_square.y += g->player.step_y;
			g->player.hit_side = 1;
		}
		if (g->map[g->player.map_square.y][g->player.map_square.x] == '1')
			hit = 1;
	}
}

void	calculate_distance(t_game *g)
{
	t_player	*p;

	p = &g->player;
	if (p->hit_side == 0)
		p->size_ray = perpendicular_dist_x(p, p->step_x);
	else
		p->size_ray = perpendicular_dist_y(p, p->step_y);
}

void	calculate_height_wall(t_game *game)
{
	t_player	*p;

	p = &game->player;
	p->tall_of_wall = fabs(((double)game->game_h / p->size_ray));
	p->tall_of_wall_y1 = (game->game_h / 2.00) - (p->tall_of_wall / 2.00);
	p->tall_of_wall_y2 = (game->game_h / 2.00) + (p->tall_of_wall / 2.00);
	if (p->tall_of_wall_y1 < 0)
		p->tall_of_wall_y1 = 0;
	if (p->tall_of_wall_y2 > game->game_h)
		p->tall_of_wall_y2 = game->game_h - 1;
	find_out_text_x(p);
}

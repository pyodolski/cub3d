/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:09:25 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 23:09:38 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static double	delta_x(t_vector *vector)
{
	return (1 / vector->x);
}

static double	delta_y(t_vector *vector)
{
	return (1 / vector->y);
}

double	dist_to_wall_x(t_player *p)
{
	double	dist_to_side_x;

	if (p->ray_dir.x < 0)
	{
		dist_to_side_x = (p->pos.x - p->map_square.x) * delta_x(&p->ray_dir);
		p->map_square.x += -1;
	}
	else
	{
		dist_to_side_x = (p->map_square.x + 1 - p->pos.x) \
			* delta_x(&p->ray_dir);
		p->map_square.x += 1;
	}
	return (dist_to_side_x);
}

double	dist_to_wall_y(t_player *p)
{
	double	dist_to_side_y;

	if (p->ray_dir.y < 0)
	{
		dist_to_side_y = (p->pos.y - p->map_square.y) * delta_y(&p->ray_dir);
		p->map_square.y += -1;
	}
	else
	{
		dist_to_side_y = (p->map_square.y + 1 - p->pos.y) \
			* delta_y(&p->ray_dir);
		p->map_square.y += 1;
	}
	return (dist_to_side_y);
}

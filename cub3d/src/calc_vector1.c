/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:58:08 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 22:42:14 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_vector	add_vector(t_vector *v1, t_vector *v2)
{
	t_vector	new;

	new.x = v1->x + v2->x;
	new.y = v1->y + v2->y;
	return (new);
}

t_vector	mult_vector(t_vector *v, double n)
{
	t_vector	new;

	new.x = v->x *n;
	new.y = v->y *n;
	return (new);
}

double	perpendicular_dist_x(t_player *p, int step_x)
{
	double	n;

	n = fabs(p->map_square.x - p->pos.x + ((1 - step_x) / 2));
	n /= p->ray_dir.x;
	return (n);
}

double	perpendicular_dist_y(t_player *p, int step_y)
{
	double	n;

	n = fabs(p->map_square.y - p->pos.y + ((1 - step_y) / 2));
	n /= p->ray_dir.y;
	return (n);
}

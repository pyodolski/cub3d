/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:58:09 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 22:42:20 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	set_player_position(t_game *cub3d, int i, int j)
{
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (cub3d->map[i][j] == cub3d->spawn)
			{
				cub3d->player.pos.x = j + 0.5;
				cub3d->player.pos.y = i + 0.5;
				cub3d->map[i][j] = '0';
				set_direction(cub3d);
				return ;
			}
		}
	}
}

void	rotate_vector(t_vector *v, double angle)
{
	double	x;
	double	y;

	x = v->x;
	y = v->y;
	v->x = x * cos(angle) - y * sin(angle);
	v->y = x * sin(angle) + y * cos(angle);
}

void	set_direction(t_game *cub3d)
{
	if (cub3d->spawn == 'S')
	{
		cub3d->player.dir.y = ONE;
		cub3d->player.plane.x = -PLANE;
	}
	else if (cub3d->spawn == 'E')
	{
		cub3d->player.dir.x = ONE;
		cub3d->player.dir.y = ZERO;
		cub3d->player.plane.x = ZERO;
		cub3d->player.plane.y = PLANE;
	}
	else if (cub3d->spawn == 'W')
	{
		cub3d->player.dir.x = -ONE;
		cub3d->player.dir.y = ZERO;
		cub3d->player.plane.x = ZERO;
		cub3d->player.plane.y = -PLANE;
	}
}

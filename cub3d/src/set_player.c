/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:58:09 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 17:21:07 by jupyo            ###   ########.fr       */
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
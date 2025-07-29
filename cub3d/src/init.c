/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:52:26 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 17:21:03 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_game(t_game *cub3d)
{
	cub3d->ceiling = -1;
	cub3d->floor = -1;
	init_player(&cub3d->player);
}

void	init_player(t_player *player)
{
	player->dir.x = ZERO;
	player->dir.y = -ONE;
	player->plane.x = PLANE;
	player->plane.y = ZERO;
}

void	get_screen_size(t_game *cub3d, void *mlx, void *win, int split)
{
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1, 1, "tmp");
	mlx_get_screen_size(mlx, &cub3d->game_w, &cub3d->game_h);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
	if (split == 2 || split == 3 || split == 4)
	{
		cub3d->game_w /= split;
		cub3d->game_h /= split;
	}
}
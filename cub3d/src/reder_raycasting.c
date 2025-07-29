/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reder_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:32:44 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 18:11:29 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	render_game(t_game *cub3d)
{
	cub3d->mlx = mlx_init();
	cub3d->window = mlx_new_window(cub3d->mlx, cub3d->game_w, cub3d->game_h,
			WIN_TITLE);
	init_textures(cub3d, TEXTURE_SIZE);
	rayscasting(cub3d);
	mlx_key_hook(cub3d->window, read_keys, cub3d);
	mlx_hook(cub3d->window, 17, 1L << 0, end_game, cub3d);
	mlx_loop(cub3d->mlx);
	return (0);
}

int	rayscasting(t_game *cub3d)
{
	if (cub3d->frame.img)
		mlx_destroy_image(cub3d->mlx, cub3d->frame.img);
	cub3d->frame.img = mlx_new_image(cub3d->mlx, cub3d->game_w, cub3d->game_h);
	cub3d->frame.addr = mlx_get_data_addr(cub3d->frame.img, &cub3d->frame.bpp,
			&cub3d->frame.line_len, &cub3d->frame.endian);
	create_background(cub3d);
	while (cub3d->pixel < cub3d->game_w)
	{
		map_position_square(&cub3d->player);
		calculate_current_ray(cub3d);
		calculate_delta(cub3d);
		dda(cub3d);
		calculate_distance(cub3d);
		calculate_height_wall(cub3d);
		render_collumn_pixel(cub3d);
		cub3d->pixel++;
	}
	mlx_clear_window(cub3d->mlx, cub3d->window);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->frame.img, 0, 0);
	cub3d->pixel = 0;
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:59:50 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 22:42:16 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	read_keys(int keypress, t_game *game)
{
	if (keypress == KEY_ESC)
		end_game(game);
	if (keypress == W)
		move_positiony(game, &game->player.dir, 1);
	if (keypress == S)
		move_positiony(game, &game->player.dir, -1);
	if (keypress == A)
		move_positionx(game, &game->player.dir, -1);
	if (keypress == D)
		move_positionx(game, &game->player.dir, 1);
	if (keypress == LEFT)
		rotate_left(game);
	if (keypress == RIGHT)
		rotate_right(game);
	return (0);
}

void	move_positionx(t_game *game, t_vector *dir, int direction)
{
	t_player	*p;
	t_vector	temp;

	temp.x = dir->x;
	temp.y = dir->y;
	rotate_vector(&temp, PI / 2);
	p = &game->player;
	p->pos.y += MOV * temp.y * direction;
	p->pos.x += MOV * temp.x * direction;
	if (game->map[(int)p->pos.y][(int)p->pos.x] != '0')
	{
		p->pos.y -= MOV * temp.y * direction;
		p->pos.x -= MOV * temp.x * direction;
		return ;
	}
	rayscasting(game);
}

void	move_positiony(t_game *game, t_vector *dir, int direction)
{
	t_player	*p;

	p = &game->player;
	p->pos.y += MOV * dir->y * direction;
	p->pos.x += MOV * dir->x * direction;
	if (game->map[(int)p->pos.y][(int)p->pos.x] != '0')
	{
		p->pos.y -= MOV * dir->y * direction;
		p->pos.x -= MOV * dir->x * direction;
		return ;
	}
	rayscasting(game);
}

void	rotate_left(t_game *game)
{
	t_player	*p;
	double		olddirx;
	double		oldplanex;

	p = &game->player;
	olddirx = p->dir.x;
	p->dir.x = p->dir.x * cos(ROT) - p->dir.y * sin(-ROT);
	p->dir.y = olddirx * sin(-ROT) + p->dir.y * cos(-ROT);
	oldplanex = p->plane.x;
	p->plane.x = p->plane.x * cos(-ROT) - p->plane.y * sin(-ROT);
	p->plane.y = oldplanex * sin(-ROT) + p->plane.y * cos(-ROT);
	rayscasting(game);
}

void	rotate_right(t_game *game)
{
	t_player	*p;
	double		olddirx;
	double		oldplanex;

	p = &game->player;
	olddirx = p->dir.x;
	p->dir.x = p->dir.x * cos(ROT) - p->dir.y * sin(ROT);
	p->dir.y = olddirx * sin(ROT) + p->dir.y * cos(ROT);
	oldplanex = p->plane.x;
	p->plane.x = p->plane.x * cos(ROT) - p->plane.y * sin(ROT);
	p->plane.y = oldplanex * sin(ROT) + p->plane.y * cos(ROT);
	rayscasting(game);
}

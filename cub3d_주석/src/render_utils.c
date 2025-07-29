/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:22:44 by anvieira          #+#    #+#             */
/*   Updated: 2025/07/29 18:53:19 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	map_position_square(t_player *player)
{
	player->map_square.x = floor(player->pos.x);
	player->map_square.y = floor(player->pos.y);
}

void	my_mlx_pixel_put(t_game *cub3d, int x, int y, int color)
// 저수준 픿셀 색상 렌더링 함수
{
	char *dst;

	dst = cub3d->frame.addr +
		(y * cub3d->frame.line_len +
			x *
				(cub3d->frame.bpp
				// 이미지 시작 주소 몇 번째 줄이고 몇 번째 픽셀인지
				/ 8));
	*(unsigned int *)dst = color;
	//  32bpp (4바이트)일 때 x=1, y=0이면 offset은 4바이트
}

inline static int	create_floor(t_game *g)
{
	int	x;
	int	y;

	y = g->game_h / 2;
	// y값을 화면 높이의 절반부터 시작해서 아래로 반복함 → 하단 절반이 바닥
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
	// 중 루프를 통해 모든 (x, y) 픽셀 좌표에 대해 바닥색 픽셀을 그리기
	// my_mlx_pixel_put() 함수는 픽셀 한 점에 색을 입히는 함수
}

static inline int	create_ceiling(t_game *g)
{
	int	x;
	int	y;

	y = 0; // 맨 위에서 시작 해서 절반 까지 상단 절반이 천장
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

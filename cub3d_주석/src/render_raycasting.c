/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 04:39:10 by anvieira          #+#    #+#             */
/*   Updated: 2025/07/29 19:00:33 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	render_collumn_pixel(t_game *cub3d)
{
	int		x;
	int		y;
	double	step_y;
	double	pos;

	step_y = fabs((double)TEXTURE_SIZE / cub3d->player.tall_of_wall);
	pos = (cub3d->player.tall_of_wall_y1 - (cub3d->game_h / 2)
			+ (cub3d->player.tall_of_wall / 2)) * step_y;
	y = cub3d->player.tall_of_wall_y1;
	x = cub3d->pixel;
	while (y < cub3d->player.tall_of_wall_y2 && y < cub3d->game_h)
	{
		cub3d->player.text_y = (int)pos & (TEXTURE_SIZE - 1);
		pos += step_y;
		my_mlx_pixel_put(cub3d, x, y, obtain_color(cub3d));
		y++;
	}
}

void	calculate_current_ray(t_game *cub3d)
// 재 수직선(pixel)에 대한 광선(ray)의 방향을 계산 DDA 벽 충돌 탐지
{
	double ray;
	t_vector ray_pixel;

	ray = 2 * ((double)cub3d->pixel / (cub3d->game_w - 1)) - 1;
	// 현재 그리는 픽셀(세로줄)이 화면에서 좌우 어느 위치인지 비율로 나타내는 값
	// -1, 0 1
	ray_pixel = mult_vector(&cub3d->player.plane, ray);
	// 플레이어의 시야를 나타내는 plane 벡터를 ray만큼 곱함으로써,
	// 화면 좌우 어느 쪽으로 광선을 발사할지 결정
	// 카메라 평면 상의 현재 픽셀 방향 벡터
	cub3d->player.ray_dir = add_vector(&cub3d->player.dir, &ray_pixel);
	// 플레이어의 시선 방향(dir) + 해당 픽셀 기준 카메라 평면 벡터(ray_pixel)를 더해
	// 최종 광선 방향(ray_dir)을 계산
}

int	rayscasting(t_game *cub3d)
{
	if (cub3d->frame.img)
		mlx_destroy_image(cub3d->mlx, cub3d->frame.img);
	// 이전 프레임의 이미지를 제거해서 메모리 누수를 방지
	// 새로운 프레임을 그리기 전, 기존 이미지 객체를 해제
	cub3d->frame.img = mlx_new_image(cub3d->mlx, cub3d->game_w, cub3d->game_h);
	// 새로운 이미지 생성
	cub3d->frame.addr = mlx_get_data_addr(cub3d->frame.img,
											&cub3d->frame.bpp,
											// 이미지의 픽셀 접근을 위한 주소 정보를 가져옴
											&cub3d->frame.line_len,
											&cub3d->frame.endian);
	create_background(cub3d);
	// 배경(천장 과 바닥 색상)을 그림
	while (cub3d->pixel < cub3d->game_w)
	// 화면 너비만큼 루프를 돌명서 한 줄씩 세로로 벽을 그림
	// 현재 열 0-> 너비까지 반복
	{
		// 한줄에 대해 수행하는 레이캐스팅 과정
		map_position_square(&cub3d->player);
		// 현재 플레이어의 위치를 기준으로 플레이어가 어느 맵 블록에 있는 계산
		calculate_current_ray(cub3d);
		// 시선 각도를 계산 시야각에 따라 방향을 약간씩 조정해 방향을 만듦
		calculate_delta(cub3d);
		// DDA 알고리즘을 위한 거리 보정값 계산
		dda(cub3d);
		// 벽을 만날 때까지 한 칸씩 나아가면 충돌 감지
		calculate_distance(cub3d);
		// 벽과 플레이어 사이의 정확한 거리 계산을 수행
		calculate_height_wall(cub3d);
		// 거리 기반으로 현재 픽셀(column)에 그릴 벽의 높이(pixel 단위) 를 계산
		render_collumn_pixel(cub3d);
		// 벽을 실제로 화면에 렌더링 해당 벽 텍스처의 해당 부분을 이미지 버퍼에 복사
		cub3d->pixel++;
		// 다음으로 이동하여 반복
	}
	mlx_clear_window(cub3d->mlx, cub3d->window);
	// 이전 프레임 모두 제거
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->frame.img, 0, 0);
	// 최종 프레임 화면에 출력
	cub3d->pixel = 0;
	// 다음 프레임을 위해 픽셀 값 초기화
	return (0);
}

int	render_game(t_game *cub3d)
{
	// 게임 상태 저장하고 있는 구조체
	cub3d->mlx = mlx_init();
	cub3d->window = mlx_new_window(cub3d->mlx, cub3d->game_w, cub3d->game_h,
			WIN_TITLE);
	init_textures(cub3d, TEXTURE_SIZE);
	// .xpm	텍스쳐 파일을 로딩하여 이미지로 변환
	// 벽이나 바닥 등에 매핑
	rayscasting(cub3d);
	// 레이캐스팅 알고리즘으로 벽을 그리는 함수
	// 플레이어 시점에서 벽까지 가상의 광선을 쏘아
	// 거리와 방향에 따라 벽을 계산하고 화면에 그림
	mlx_key_hook(cub3d->window, read_keys, cub3d);
	// 키보드 입력을 감지하여 처리하는 훅을 성정
	mlx_hook(cub3d->window, 17, 1L << 0, end_game, cub3d);
	// 윈도우 닫기 버튼을 눌렀을 떄 호출되는 이벤트 설정
	mlx_loop(cub3d->mlx);
	// 루프
	return (0);
}

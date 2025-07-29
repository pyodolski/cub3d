/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:00:23 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 16:12:21 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	parse_file(t_game *cub3d, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error(cub3d, ERR_CUB_OPEN);
	cub3d->line = get_next_line(fd);
	while (cub3d->line)
	{
		parse_line(cub3d, cub3d->line, 0);
		if (cub3d->start_map)
			break ;
		free(cub3d->line);
		cub3d->line = get_next_line(fd);
	}
	if (!have_all_params(cub3d))
		exit_error(cub3d, ERR_PARAMS);
	parse_map(cub3d, fd);
	close(fd);
}

void	parse_line(t_game *cub3d, char *line, int i)
{
	while (ft_isspace(line[i]))
		i++;
	if (ft_strncmp(line + i, "NO", 2) == 0)
		check_texture(cub3d, get_value(line, i + 2, TEXTURE), NORTH);
	else if (ft_strncmp(line + i, "SO", 2) == 0)
		check_texture(cub3d, get_value(line, i + 2, TEXTURE), SOUTH);
	else if (ft_strncmp(line + i, "EA", 2) == 0)
		check_texture(cub3d, get_value(line, i + 2, TEXTURE), EAST);
	else if (ft_strncmp(line + i, "WE", 2) == 0)
		check_texture(cub3d, get_value(line, i + 2, TEXTURE), WEST);
	else if (ft_strncmp(line + i, "F", 1) == 0)
		check_color(cub3d, get_value(line, i + 1, COLOR), FLOOR);
	else if (ft_strncmp(line + i, "C", 1) == 0)
		check_color(cub3d, get_value(line, i + 1, COLOR), CEILING);
	else if (line[i] == '0' || line[i] == '1')
		cub3d->start_map = YES;
	else if (line[i] != '\0')
		exit_error(cub3d, ERR_INVALID);
}

void	check_texture(t_game *cub3d, char *file, int face)
{
	check_texture_file(cub3d, file, 0);
	if (face == NORTH && !cub3d->north)
		cub3d->north = ft_strdup(file);
	else if (face == SOUTH && !cub3d->south)
		cub3d->south = ft_strdup(file);
	else if (face == EAST && !cub3d->east)
		cub3d->east = ft_strdup(file);
	else if (face == WEST && !cub3d->west)
		cub3d->west = ft_strdup(file);
	else
		exit_error(cub3d, ERR_XPM_CALL);
}
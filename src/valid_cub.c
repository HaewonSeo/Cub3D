/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:22:47 by haseo             #+#    #+#             */
/*   Updated: 2021/05/22 17:15:55 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	valid_element_lines(char *word, int cnt_word)
{
	if (ft_strncmp(word, "R\0", 2) == 0 && cnt_word != 3)
		ft_exit("[ERROR] Invalid R line format");
	else if (ft_strncmp(word, "NO\0", 3) == 0 && cnt_word != 2)
		ft_exit("[ERROR] Invalid NO line format");
	else if (ft_strncmp(word, "SO\0", 3) == 0 && cnt_word != 2)
		ft_exit("[ERROR] Invalid SO line format");
	else if (ft_strncmp(word, "WE\0", 3) == 0 && cnt_word != 2)
		ft_exit("[ERROR] Invalid WE line format");
	else if (ft_strncmp(word, "EA\0", 3) == 0 && cnt_word != 2)
		ft_exit("[ERROR] Invalid EA line format");
	else if (ft_strncmp(word, "S\0", 2) == 0 && cnt_word != 2)
		ft_exit("[ERROR] Invalid S linee format");
	else if (ft_strncmp(word, "F\0", 2) == 0 && cnt_word != 2)
		ft_exit("[ERROR] Invalid F line format");
	else if (ft_strncmp(word, "C\0", 2) == 0 && cnt_word != 2)
		ft_exit("[ERROR] Invalid C line format");
}

void	valid_cub(t_cub *cub)
{
	if (!cub->ele.render_x || !cub->ele.render_y)
		ft_exit("[ERROR] Empty rendering size");
	if (!cub->ele.xpm_path[NORTH] || !cub->ele.xpm_path[SOUTH] ||
	!cub->ele.xpm_path[WEST] || !cub->ele.xpm_path[EAST]
	|| !cub->ele.xpm_path[SPR])
		ft_exit("[ERROR] Empty texture path");
	if (cub->ele.floor == -1 || cub->ele.ceiling == -1)
		ft_exit("[ERROR] Empty color");
	if (!cub->map_width || !cub->map_height)
		ft_exit("[ERROR] Invalid map size");
	if (!cub->player.spawning_orientation)
		ft_exit("[ERROR] Empty player spawning orientation");
	valid_map_horizontal(cub);
	valid_map_vertical(cub);
}

void	valid_map_horizontal(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->map_height)
	{
		if (cub->map[y][0] != ' ' && cub->map[y][0] != WALL)
			ft_exit("[ERROR] Map is not surronded by wall(WEST)");
		if (cub->map[y][cub->map_width - 1] != ' ' &&
				cub->map[y][cub->map_width - 1] != WALL)
			ft_exit("[ERROR] Map is not surronded by wall(EAST)");
		x = 0;
		while (++x < cub->map_width)
		{
			if (cub->map[y][x] == ' ')
			{
				if (cub->map[y][x - 1] != ' ' && cub->map[y][x - 1] != WALL)
					ft_exit("[ERROR] Map is not surronded by wall(EAST)");
				else if (x + 1 < cub->map_width &&
					cub->map[y][x + 1] != ' ' && cub->map[y][x + 1] != WALL)
					ft_exit("[ERROR] Map is not surronded by wall(WEST)");
			}
		}
	}
}

void	valid_map_vertical(t_cub *cub)
{
	int	x;
	int	y;

	x = -1;
	while (++x < cub->map_width)
	{
		if (cub->map[0][x] != ' ' && cub->map[0][x] != WALL)
			ft_exit("[ERROR] Map is not surronded by wall(NORTH)");
		if (cub->map[cub->map_height - 1][x] != ' ' &&
				cub->map[cub->map_height - 1][x] != WALL)
			ft_exit("[ERROR] Map is not surronded by wall(SOUTH)");
		y = 0;
		while (++y < cub->map_height)
		{
			if (cub->map[y][x] == ' ')
			{
				if (cub->map[y - 1][x] != ' ' && cub->map[y - 1][x] != WALL)
					ft_exit("[ERROR] Map is not surronded by wall(SOUTH)");
				else if (y + 1 < cub->map_height &&
					cub->map[y + 1][x] != ' ' && cub->map[y + 1][x] != WALL)
					ft_exit("[ERROR] Map is not surronded by wall(NORTH)");
			}
		}
	}
}

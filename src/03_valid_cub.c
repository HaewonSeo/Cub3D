/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_valid_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:22:47 by haseo             #+#    #+#             */
/*   Updated: 2021/05/14 08:17:26 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

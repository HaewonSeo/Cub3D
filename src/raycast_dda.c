/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 19:04:12 by haseo             #+#    #+#             */
/*   Updated: 2021/05/21 22:50:15 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_ray(t_cub *cub, t_player *player, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)cub->width - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x * -1;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x * -1;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	calc_step_sidedist(t_player *player, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) *
								ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) *
								ray->delta_dist_y;
	}
}

void	perform_dda(t_cub *cub, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = (ray->step_x == 1) ? EAST : WEST;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = (ray->step_y == 1) ? NORTH : SOUTH;
		}
		if (cub->map[ray->map_y][ray->map_x] == WALL)
			ray->hit = 1;
	}
}

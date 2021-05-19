/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 19:04:47 by haseo             #+#    #+#             */
/*   Updated: 2021/05/19 19:17:12 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		raycast(t_cub *cub)
{
	set_background(cub);
	raycast_wall(cub);
	raycast_sprite(cub, &cub->player);
	render(cub);
	return (0);
}

void	set_background(t_cub *cub)
{
	int x;
	int y;

	y = -1;
	while (++y < cub->map_height)
	{
		x = -1;
		while (++x < cub->map_width)
		{
			if (y > cub->map_height / 2)
				cub->buf[y][x] = cub->ele.floor;
			else
				cub->buf[y][x] = cub->ele.ceiling;
		}
	}
}

void	raycast_wall(t_cub *cub)
{
	int x;

	x = -1;
	while (++x < cub->map_width)
	{
		init_ray(cub, &cub->player, &cub->ray, x);
		calc_step_sidedist(&cub->player, &cub->ray);
		perform_dda(cub, &cub->ray);
		calc_wall_distance(&cub->player, &cub->ray);
		calc_wall_height(cub, &cub->ray);
		set_wall_tex_x(&cub->player, &cub->ray);
		set_wall_tex_y(cub, &cub->ray, x);
		cub->z_buf[x] = cub->ray.perp_wall_dist;
	}
}

void	raycast_sprite(t_cub *cub, t_player *player)
{
	int i;
	int stripe;

	sort_sprite(cub);
	i = -1;
	while (++i < cub->num_sprite)
	{
		transform_sprite(cub, player, &cub->s_ray, i);
		calc_sprite_height(cub, &cub->s_ray);
		calc_sprite_width(cub, &cub->s_ray);
		stripe = cub->s_ray.draw_start_x;
		while (stripe < cub->s_ray.draw_end_x)
		{
			set_sprite_tex_y(cub, &cub->s_ray, stripe);
			stripe++;
		}
	}
}

void	render(t_cub *cub)
{
	int x;
	int y;

	y = -1;
	while (++y < cub->map_height)
	{
		x = -1;
		while (++x < cub->map_width)
			cub->img.data[cub->map_width * y + x] = cub->buf[y][x];
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.ptr, 0, 0);
}

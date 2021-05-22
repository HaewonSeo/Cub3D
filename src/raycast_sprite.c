/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 19:03:50 by haseo             #+#    #+#             */
/*   Updated: 2021/05/22 14:56:32 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	sort_sprite(t_cub *cub)
{
	int			i;
	int			j;
	int			max;
	t_sprite	tmp;

	i = 0;
	max = 0;
	while (i < cub->num_sprite - 1)
	{
		max = i;
		j = i + 1;
		while (j < cub->num_sprite)
		{
			if (cub->sprite[j].distance > cub->sprite[i].distance)
				max = j;
			j++;
		}
		if (max > i)
		{
			tmp = cub->sprite[i];
			cub->sprite[i] = cub->sprite[max];
			cub->sprite[max] = tmp;
		}
		i++;
	}
}

void	trans_sprite(t_cub *cub, t_player *player, t_sprite_ray *s_ray, int i)
{
	double v_move;

	v_move = 0.0;
	s_ray->x = cub->sprite[i].x - player->pos_x;
	s_ray->y = cub->sprite[i].y - player->pos_y;
	s_ray->inv_det = 1.0 /
		(player->plane_x * player->dir_y - player->dir_x * player->plane_y);
	s_ray->transform_x = s_ray->inv_det *
		(player->dir_y * s_ray->x - player->dir_x * s_ray->y);
	s_ray->transform_y = s_ray->inv_det *
		(-player->plane_y * s_ray->x + player->plane_x * s_ray->y);
	s_ray->screen_x = (int)((cub->width / 2) *
						(1 - s_ray->transform_x / s_ray->transform_y));
	s_ray->v_move_screen = (int)(v_move / s_ray->transform_y);
}

void	calc_sprite_height(t_cub *cub, t_sprite_ray *s_ray)
{
	int v_div;

	v_div = 1;
	s_ray->height = (int)fabs((cub->height / s_ray->transform_y) / v_div);
	s_ray->draw_start_y =
		cub->height / 2 - s_ray->height / 2 + s_ray->v_move_screen;
	if (s_ray->draw_start_y < 0)
		s_ray->draw_start_y = 0;
	s_ray->draw_end_y =
		cub->height / 2 + s_ray->height / 2 + s_ray->v_move_screen;
	if (s_ray->draw_end_y >= cub->height)
		s_ray->draw_end_y = cub->height - 1;
}

void	calc_sprite_width(t_cub *cub, t_sprite_ray *s_ray)
{
	int u_div;

	u_div = 1;
	s_ray->width = (int)fabs((cub->height / s_ray->transform_y) / u_div);
	s_ray->draw_start_x = s_ray->screen_x - s_ray->width / 2;
	if (s_ray->draw_start_x < 0)
		s_ray->draw_start_x = 0;
	s_ray->draw_end_x = s_ray->screen_x + s_ray->width / 2;
	if (s_ray->draw_end_x >= cub->width)
		s_ray->draw_end_x = cub->width - 1;
}

void	set_sprite_tex_y(t_cub *cub, t_sprite_ray *s_ray, int x)
{
	int y;
	int draw;
	int color;

	s_ray->tex_x = (int)((256 * (x - (s_ray->screen_x - s_ray->width / 2)) *
									TEX_WIDTH / s_ray->width) / 256);
	if (x > 0 && x < cub->width &&
		s_ray->transform_y > 0 && s_ray->transform_y < cub->z_buf[x])
	{
		y = s_ray->draw_start_y;
		while (y < s_ray->draw_end_y)
		{
			draw = (y - s_ray->v_move_screen) * 256 -
					cub->height * 128 + s_ray->height * 128;
			s_ray->tex_y = ((draw * TEX_HEIGHT) / s_ray->height) / 256;
			color = cub->ele.tex[SPR][TEX_WIDTH * s_ray->tex_y + s_ray->tex_x];
			if ((color & 0x00FFFFFF) != 0)
				cub->buf[y][x] = color;
			y++;
		}
	}
}

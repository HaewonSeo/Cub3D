/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 19:04:59 by haseo             #+#    #+#             */
/*   Updated: 2021/05/21 23:12:08 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	start_game(t_cub *cub)
{
	cub->img.ptr = mlx_new_image(cub->mlx, cub->width, cub->height);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.ptr,
			&cub->img.bpp, &cub->img.size_line, &cub->img.endian);
	cub->win = mlx_new_window(cub->mlx, cub->width, cub->height, TITLE);
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, MLX_KEYMASK, &handle_key, cub);
	mlx_loop_hook(cub->mlx, &raycast, cub);
	mlx_loop(cub->mlx);
}

int		handle_key(int key, t_cub *cub)
{
	if (key == KEY_W || key == KEY_UP)
		move_forward_backward(cub, &cub->player, cub->player.move_speed);
	if (key == KEY_S || key == KEY_DOWN)
		move_forward_backward(cub, &cub->player, -cub->player.move_speed);
	if (key == KEY_A)
		move_left_right(cub, &cub->player, cub->player.move_speed);
	if (key == KEY_D)
		move_left_right(cub, &cub->player, -cub->player.move_speed);
	if (key == KEY_LEFT)
		rotate_player(&cub->player, -cub->player.rot_speed);
	if (key == KEY_RIGHT)
		rotate_player(&cub->player, cub->player.rot_speed);
	if (key == KEY_ESC)
		ft_exit("[EXIT] Exit key pressed");
	return (0);
}

void	move_forward_backward(t_cub *cub, t_player *player, double move_speed)
{
	char x;
	char y;

	x = cub->map[(int)player->pos_y]
				[(int)(player->pos_x + player->dir_x * move_speed)];
	y = cub->map[(int)(player->pos_y + player->dir_y * move_speed)]
				[(int)player->pos_x];
	/* sqrt() >= 0 ?*/
	// if (x != WALL)
	if (x != WALL && sqrt((pow(cub->s_ray.x, 2) + pow(cub->s_ray.y, 2)) >= 0.2))
		player->pos_x += player->dir_x * move_speed;
	// if (y != WALL)
	if (y != WALL && sqrt((pow(cub->s_ray.x, 2) + pow(cub->s_ray.y, 2)) >= 0.2))
		player->pos_y += player->dir_y * move_speed;
}

void	move_left_right(t_cub *cub, t_player *player, double move_speed)
{
	char x;
	char y;

	x = cub->map[(int)player->pos_y][(int)(player->pos_x + player->dir_y * move_speed)];
	y = cub->map[(int)(player->pos_y + -player->dir_x * move_speed)][(int)player->pos_x];
	if (x != WALL)
		player->pos_x += player->dir_y * move_speed;
	if (y != WALL)
		player->pos_y += -player->dir_x * move_speed;
}

void	rotate_player(t_player *player, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed)
					- player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed)
					+ player->dir_y * cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed)
					- player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed)
					+ player->plane_y * cos(rot_speed);
}

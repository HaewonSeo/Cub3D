/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_set_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:47:50 by haseo             #+#    #+#             */
/*   Updated: 2021/05/20 22:31:26 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_cub(t_cub *cub)
{
	int i;

	if (!(cub->buf = ft_calloc(cub->ele.render_y, sizeof(int **))))
		ft_exit("[ERROR] Fail to malloc buf(map_height)");
	i = -1;
	while (++i < cub->ele.render_y)
	{
		if (!(cub->buf[i] = ft_calloc(cub->ele.render_x, sizeof(int *))))
			ft_exit("[ERROR] Fail to malloc buf(map_width)");
	}
	if (!(cub->z_buf = ft_calloc(cub->ele.render_x, sizeof(double *))))
		ft_exit("[ERROR] Fail to malloc z_buf");
	cub->mlx = mlx_init();
	load_texture(cub);
	init_sprite(cub);
	calc_sprite_distance(cub);
}

void	load_texture(t_cub *cub)
{
	int		i;
	t_img	img;

	i = NORTH;
	while (i <= SPR)
	{
		load_image_from_xpm(cub, cub->ele.tex[i], cub->ele.xpm_path[i], &img);
		free(cub->ele.xpm_path[i]);
		i++;
	}
}

void	load_image_from_xpm(t_cub *cub, int *tex, char *xpm_path, t_img *img)
{
	int		x;
	int		y;

	img->ptr = mlx_xpm_file_to_image(cub->mlx, xpm_path,
									&img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(
					img->ptr, &img->bpp, &img->size_line, &img->endian);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			tex[img->width * y + x] =
				img->data[img->width * y + (img->width - x - 1)];
	}
	mlx_destroy_image(cub->mlx, img->ptr);
}

void	init_sprite(t_cub *cub)
{
	int x;
	int y;
	int i;

	if (!(cub->sprite = malloc(sizeof(t_sprite) * cub->num_sprite)))
		ft_exit("[ERROR] Fail to malloc sprite");
	i = 0;
	y = -1;
	while (++y < cub->map_height)
	{
		x = -1;
		while (++x < cub->map_width)
		{
			if (cub->map[y][x] == SPRITE)
			{
				/* 0.5f ? */
				cub->sprite[i].x = 0.5f + x;
				cub->sprite[i].y = 0.5f + y;
				i++;
			}
		}
	}
}

void	calc_sprite_distance(t_cub *cub)
{
	int i;

	i = 0;
	while (i < cub->num_sprite)
	{
		cub->sprite[i].distance = pow(cub->player.pos_x - cub->sprite[i].x, 2)
				+ pow(cub->player.pos_y - cub->sprite[i].y, 2);
		i++;
	}
}

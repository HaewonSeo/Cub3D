/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_save_screenshot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:53:23 by haseo             #+#    #+#             */
/*   Updated: 2021/05/21 11:44:24 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	save_screenshot(t_cub *cub)
{
	int	fd;
	int	size;

	set_background(cub);
	raycast_wall(cub);
	raycast_sprite(cub, &cub->player);
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 00755);
	if (fd < 0)
		ft_exit("[ERROR] Fail to open screenshot.bmp");
	size = 54 + 3 * cub->width * cub->height;
	write_bmp_header(cub, fd, size);
	write_bmp_data(cub, fd);
	ft_putstr("[SUCCESS] Create screenshot.bmp\n");
}

void	write_bmp_header(t_cub *cub, int fd, int size)
{
	unsigned char	header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	put_int_value(&header[2], size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	put_int_value(&header[18], cub->width);
	put_int_value(&header[22], cub->height);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

void	put_int_value(unsigned char *ptr, int value)
{
	ptr[0] = (unsigned char)(value);
	ptr[1] = (unsigned char)(value >> 8);
	ptr[2] = (unsigned char)(value >> 16);
	ptr[3] = (unsigned char)(value >> 24);
}

void	write_bmp_data(t_cub *cub, int fd)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					pad;

	i = cub->height;
	pad = (4 - (cub->width * 3) % 4) % 4;
	while (i >= 0)
	{
		j = 0;
		while (j < cub->width)
		{
			write(fd, &(cub->buf[i][j]), 3);
			if (pad > 0)
				write(fd, &zero, pad);
			j++;
		}
		i--;
	}
}

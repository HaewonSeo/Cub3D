/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_read_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:40:51 by haseo             #+#    #+#             */
/*   Updated: 2021/05/10 22:14:25 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	read_cub_element_lines(t_cub *cub)
{
	char	*line;
	int		type;
	char	**word;

	while (get_next_line(cub->fd, &line) > 0)
	{
		if (line[0] == '\0')
			continue;
		if (!(word = ft_split(line, ' ')))
			ft_exit("[ERROR] Fail to split lines");
		type = store_element(cub, word);
		ft_free2d(word);
		if (type == MAP)
			break;
		free(line);
	}
	cub->map_lines = ft_lstnew(ft_strdup(line));
	free(line);
}

int		store_elements(t_cub *cub, char **word)
{
	if (ft_strcmp(word[0], "R") == 0)
		store_resolution(cub, word[1], word[2]);
	else if (ft_strcmp(word[0], "NO") == 0)
		store_texture(cub, word[1], NORTH);
	else if (ft_strcmp(word[0], "SO") == 0)
		store_texture(cub, word[1], SOUTH);
	else if (ft_strcmp(word[0], "WE") == 0)
		store_texture(cub, word[1], WEST);
	else if (ft_strcmp(word[0], "EA") == 0)
		store_texture(cub, word[1], EAST);
	else if (ft_strcmp(word[0], "S") == 0)
		store_texture(cub, word[1], SPR);
	else if (ft_strcmp(word[0], "F") == 0)
		store_color(cub, word[1], FLOOR);
	else if (ft_strcmp(word[0], "C") == 0)
		store_color(cub, word[1], CEILING);
	else
		return (MAP);
	return (0);
}

void	store_resolution(t_cub *cub, char *x, char *y)
{
	if (!x || !y)
		ft_exit("[ERROR] Empty resolution size");
	if (!ft_isdigit_str(x) || !ft_isdigit_str(y))
		ft_exit("[ERROR] Invalid resoultion size format");
	cub->ele.render_x = ft_atoi(x);
	cub->ele.render_y = ft_atoi(y);
	cub->ele.render_x = (cub->ele.render_x > 1920) ? 1920 : cub->ele.render_x;
	cub->ele.render_x = (cub->ele.render_x < 848) ? 848 : cub->ele.render_x;
	cub->ele.render_y = (cub->ele.render_y > 1080) ? 1080 : cub->ele.render_y;
	cub->ele.render_y = (cub->ele.render_y < 480) ? 480 : cub->ele.render_y;
}

void	store_texture(t_cub *cub, char *xpm_path, int type)
{
	int		fd;

	if (!xpm_path)
		ft_exit("[ERROR] Empty xpm path");
	if (!ft_isformat(xpm_path, ".xpm"))
		ft_exit("[ERROR] Invalid xpm path format");
	if ((fd = open(xpm_path, O_RDONLY)) == -1)
		ft_exit("[ERROR] Fail to open .xpm file");
	close(fd);
	cub->ele.xpm_path[type] = ft_strdup(xpm_path);
}

void	store_color(t_cub *cub, char *rgb_color, int type)
{
	char	**rgb;
	int		hex;
	int		tmp;
	int		i;

	if (!(rgb = ft_split(rgb_color, ',')))
		ft_exit("[ERROR] Fail to split RGB");
	i = -1;
	hex = 0;
	while (++i < 3)
	{
		if (!rgb[i])
			ft_exit("[ERROR] Empty RGB value");
		if (!ft_isdigit_str(rgb[i]))
			ft_exit("[ERROR] Invalid RGB format");
		tmp = ft_atoi(rgb[i]);
		if (tmp > 255 || tmp < 0)
			ft_exit("[ERROR] Invalid RGB range");
		hex = hex * 256 + tmp;
	}
	if (type == FLOOR)
		cub->ele.floor = hex;
	else if (type == CEILING)
		cub->ele.ceiling = hex;
	ft_free2d(rgb);
}

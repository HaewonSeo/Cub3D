/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 01:20:44 by haseo             #+#    #+#             */
/*   Updated: 2021/05/22 14:15:26 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	read_cub_map_lines(t_cub *cub)
{
	char *line;

	while (get_next_line(cub->fd, &line) > 0)
	{
		if (line[0] == '\0')
			break ;
		ft_lstadd_back(&cub->map_lines, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	free(line);
	init_map(cub, cub->map_lines);
	store_map(cub, cub->map_lines);
	ft_lstclear(&cub->map_lines, free);
}

void	init_map(t_cub *cub, t_list *map_lines)
{
	int	i;

	cub->map_width = ft_lstmaxwidth(map_lines);
	cub->map_height = ft_lstsize(map_lines);
	if (!(cub->map = malloc(sizeof(char *) * (cub->map_height + 1))))
		ft_exit("[ERROR] Fail to malloc map(height)");
	cub->map[cub->map_height] = NULL;
	i = 0;
	while (map_lines)
	{
		if (!(cub->map[i] = malloc(sizeof(char) * (cub->map_width + 1))))
			ft_exit("[ERROR] Fail to malloc map(width)");
		ft_memset(cub->map[i], ' ', cub->map_width);
		cub->map[i][cub->map_width] = '\0';
		i++;
		map_lines = (map_lines)->next;
	}
}

void	store_map(t_cub *cub, t_list *map_lines)
{
	int		i;
	int		j;
	char	*content;
	int		len_content;

	i = -1;
	while (++i < cub->map_height)
	{
		content = (char *)((map_lines)->content);
		len_content = (int)ft_strlen(content);
		j = -1;
		while (++j < len_content)
		{
			if (!ft_strchr("012NSEW \n", content[j]))
				ft_exit("[ERROR] Invalid map content(012NSEW)");
			cub->map[i][j] = content[j];
			if (ft_strchr("NSEW", content[j]))
				init_player(cub, i, j);
			else if (content[j] == SPRITE)
				cub->num_sprite++;
		}
		map_lines = (map_lines)->next;
	}
}

void	init_player(t_cub *cub, int i, int j)
{
	int degree;

	degree = 0;
	if (cub->player.spawning_orientation)
		ft_exit("[ERROR] Invalid map content(multiple player)");
	cub->player.spawning_orientation = cub->map[i][j];
	cub->player.pos_x = 0.5f + j;
	cub->player.pos_y = 0.5f + i;
	cub->player.dir_x = -1.0;
	cub->player.dir_y = 0.0;
	cub->player.plane_x = 0.0;
	cub->player.plane_y = 0.66;
	cub->player.move_speed = 0.20;
	cub->player.rot_speed = 0.13;
	if (cub->player.spawning_orientation == 'N')
		degree = 270;
	else if (cub->player.spawning_orientation == 'S')
		degree = 90;
	else if (cub->player.spawning_orientation == 'E')
		degree = 0;
	else if (cub->player.spawning_orientation == 'W')
		degree = 180;
	rotate_player(&(cub->player), degree * (PI / 180));
}

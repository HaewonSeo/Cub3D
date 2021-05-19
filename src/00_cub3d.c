/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:40:44 by haseo             #+#    #+#             */
/*   Updated: 2021/05/19 19:33:19 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		main(int argc, char *argv[])
{
	t_cub	cub;
	int		save;

	valid_arg(argc, argv, &save);
	init_cub(&cub, argv[1]);
	read_cub_element_lines(&cub);
	read_cub_map_lines(&cub);
	valid_cub(&cub);
	set_cub(&cub);
	if (save)
		take_screenshot(&cub);
	else
		run_program(&cub);
	return (0);
}

void	valid_arg(int argc, char *argv[], int *save)
{
	if (!(argc == 2 || argc == 3))
		ft_exit("[Usage] ./cub3d cub_file [--save]");
	if (argc == 2)
		*save = 0;
	else if (ft_strcmp(argv, "--save") == 0)
		*save = 1;
	else
		ft_exit("[Usage] ./cub3d cub_file [--save]");
}

void	init_cub(t_cub *cub, char *arg)
{
	ft_memset(cub, 0, sizeof(t_cub));
	cub->ele.floor = -1;
	cub->ele.ceiling = -1;
	if (!ft_isformat(arg, ".cub"))
		ft_exit("[ERROR] invalid .cub file format");
	if ((cub->fd = open(arg, O_RDONLY)) == -1)
		ft_exit("[ERROR] fail to open .cub file");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:40:44 by haseo             #+#    #+#             */
/*   Updated: 2021/05/22 14:33:50 by haseo            ###   ########.fr       */
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
		save_screenshot(&cub);
	else
		start_game(&cub);
	return (0);
}

void	valid_arg(int argc, char *argv[], int *save)
{
	if (!(argc == 2 || argc == 3))
		ft_exit("[Usage] ./cub3d cub_file [--save]");
	if (argc == 2)
		*save = 0;
	else if (ft_strncmp(argv[2], "--save\0", 7) == 0)
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
		ft_exit("[ERROR] Invalid .cub file format");
	if ((cub->fd = open(arg, O_RDONLY)) == -1)
		ft_exit("[ERROR] Fail to open .cub file");
}

int		exit_game(void)
{
	ft_exit("[Bye] Red button is pressed");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:40:26 by haseo             #+#    #+#             */
/*   Updated: 2021/05/21 12:27:53 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>

# if defined(__linux__)
#  include "../minilibx-linux/mlx.h"
#  include "./keycode_linux.h"
#  define MLX_KEYMASK		1L<<0
# elif defined(__APPLE__) && defined(__MACH__)
#  include "../minilibx_opengl_20191021/mlx.h"
#  include "./keycode_macos.h"
#  define MLX_KEYMASK		0
# endif

# define TITLE				"cub3D"
# define NORTH				0
# define SOUTH				1
# define EAST				2
# define WEST				3
# define SPR				4
# define FLOOR				5
# define CEILING			6
# define MAP				7
# define EMPTY				'0'
# define WALL				'1'
# define SPRITE				'2'
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17
# define TEX_WIDTH			64
# define TEX_HEIGHT 		64
# define PI					3.1415926535897

typedef struct		s_img
{
	void			*ptr;
	int				*data;
	int				size_line;
	int				bpp;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			distance;
}					t_sprite;

typedef struct		s_sprite_ray
{
	double			x;
	double			y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				v_move_screen;
	int				height;
	int				width;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				tex_x;
	int				tex_y;
}					t_sprite_ray;

typedef struct		s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start_y;
	int				draw_end_y;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
}					t_ray;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
	char			spawning_orientation;
}					t_player;

typedef struct		s_element
{
	int				render_x;
	int				render_y;
	char			*xpm_path[5];
	int				tex[5][TEX_HEIGHT * TEX_WIDTH];
	int				floor;
	int				ceiling;
}					t_element;

typedef struct		s_cub
{
	void			*mlx;
	void			*win;
	int				fd;
	t_element		ele;
	int				width;
	int				height;
	t_list			*map_lines;
	char			**map;
	int				map_width;
	int				map_height;
	t_player		player;
	int				**buf;
	double			*z_buf;
	t_img			img;
	int				num_sprite;
	t_sprite		*sprite;
	t_ray			ray;
	t_sprite_ray	s_ray;
}					t_cub;

/*
**	00_cub3d.c
*/

void				valid_arg(int argc, char *argv[], int *save);
void				init_cub(t_cub *cub, char *arg);

/*
**	01_read_elements.c
*/

void				read_cub_element_lines(t_cub *cub);
int					store_elements(t_cub *cub, char **info);
void				store_resolution(t_cub *cub, char *width, char *height);
void				store_texture(t_cub *cub, char *xpm_path, int flag);
void				store_color(t_cub *cub, char *rgb_with_comma, int flag);

/*
**	02_read_map.c
*/

void				read_cub_map_lines(t_cub *cub);
void				init_map(t_cub *cub, t_list *map_lines);
void				store_map(t_cub *cub, t_list *map_lines);
void				init_player(t_cub *cub, int i, int j);

/*
**	03_valid_cub.c
*/

void				valid_cub(t_cub *cub);
void				valid_map_horizontal(t_cub *cub);
void				valid_map_vertical(t_cub *cub);

/*
**	04_set_cub.c
*/

void				set_cub(t_cub *cub);
void				load_texture(t_cub *cub);
void				load_image_from_xpm
						(t_cub *cub, int *texture, char *path, t_img *img);
void				init_sprite(t_cub *cub);
void				calc_sprite_distance(t_cub *cub);

/*
**	05_start_game.c
*/

void				start_game(t_cub *cub);
int					handle_key(int key, t_cub *cub);
void				move_forward_backward
						(t_cub *cub, t_player *p, double move_speed);
void				move_left_right(t_cub *cub, t_player *p, double move_speed);
void				rotate_player(t_player *p, double rot_speed);

/*
**	06_raycast.c
*/

int					raycast(t_cub *cub);
void				set_background(t_cub *cub);
void				raycast_wall(t_cub *cub);
void				raycast_sprite(t_cub *cub, t_player *p);
void				render(t_cub *cub);

/*
**	07_raycast_dda.c
*/

void				init_ray(t_cub *cub, t_player *p, t_ray *ray, int x);
void				calc_step_sidedist(t_player *p, t_ray *ray);
void				perform_dda(t_cub *cub, t_ray *ray);

/*
**	08_raycast_wall.c
*/

void				calc_wall_distance(t_player *p, t_ray *ray);
void				calc_wall_height(t_cub *cub, t_ray *ray);
void				set_wall_tex_x(t_player *player, t_ray *ray);
void				set_wall_tex_y(t_cub *cub, t_ray *ray, int x);
/*
**	09_raycast_sprite.c
*/

void				sort_sprite(t_cub *cub);
void				transform_sprite(t_cub *cub,
							t_player *p, t_sprite_ray *s_ray, int i);
void				calc_sprite_height(t_cub *cub, t_sprite_ray *s_ray);
void				calc_sprite_width(t_cub *cub, t_sprite_ray *s_ray);
void				set_sprite_tex_y(t_cub *cub, t_sprite_ray *s_ray, int x);

/*
**	10_save_screenshot.c
*/

void				save_screenshot(t_cub *cub);
void				write_bmp_header(t_cub *cub, int fd, int size);
void				put_int_value(unsigned char *start, int value);
void				write_bmp_data(t_cub *cub, int fd);

#endif

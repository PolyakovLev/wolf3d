/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <daharwoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 19:50:57 by ramory-l          #+#    #+#             */
/*   Updated: 2019/02/13 19:19:08 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# include "get_next_line.h"
# include <SDL2/SDL.h>
# include <SDL2_image/SDL_image.h>
# include <stdio.h>

# define SCREENPIX app->screen->pixels
# define IMAGE app->image
# define SNF sky_n_floor
# define IMG1 (((Uint32 *)IMAGE[SNF->floor_texture]->pixels)
# define IMG1_1 [64 * SNF->floor_tex_y + SNF->floor_tex_x]
# define IMG2 ((Uint32 *)IMAGE[7]->pixels)
# define SCREENF ((Uint32 *)SCREENPIX)[y * 640 + app->x]
# define SCREENS ((Uint32 *)SCREENPIX)[(WINDOW_HEIGHT - y) * 640 + app->x]
# define DRAWFLOOR SCREENF = IMG1 IMG1_1 >> 1) & 8355711
# define DRAWSKY SCREENS = IMG2[2048 * SNF->floor_tex_y + SNF->floor_tex_x]
# define SNFW SNF->weight

typedef struct		s_app
{
	SDL_Window		*window;
	SDL_Surface		*image[10];
	SDL_Surface		*screen;
	int				**map;
	int				map_size[2];
	int				tex_num;
	int				tex_x;
	int				tex_y;
	int				x;
}					t_app;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	int				close_request;
	int				step_x;
	int				step_y;
	SDL_Event		event;
	double			move_speed;
	double			rot_speed;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				side;
}					t_player;

typedef struct		s_camera
{
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			olddir_x;
	double			oldplane_x;
	double			frame_time;
	double			time;
	double			old_time;
	int				hit;
	double			wall_x;
}					t_camera;

typedef	struct		s_up_bottom
{
	double			dist_wall;
	double			dist_player;
	double			current_dist;
	double			fl_xwall;
	double			fl_ywall;
	double			weight;
	double			cur_fl_x;
	double			cur_fl_y;
	int				floor_tex_x;
	int				floor_tex_y;
	int				board_pattern;
	int				floor_texture;
}					t_up_bottom;

int					init(t_app *app, t_player *player, t_camera *camera);
int					create_window(t_app *app);
int					create_screen(t_app *app);
int					load_images(t_app *app);
int					lock_images(t_app *app);
int					**ft_create_map(char *map, int *size);
void				start_game(t_app *app, t_player *player, t_camera *camera);
void				player_input(t_player *player,
									t_camera *camera, t_app *app);
void				draw(t_app *app, t_player *player, t_camera *camera);
void				clean_up(t_app *app);

#endif

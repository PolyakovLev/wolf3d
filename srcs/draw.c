/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:16:15 by ramory-l          #+#    #+#             */
/*   Updated: 2019/02/13 21:02:46 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_floor_n_sky(t_app *app, t_player *player,
					t_camera *camera, t_up_bottom *sky_n_floor)
{
	int y;

	y = camera->draw_end + 1;
	SNF->dist_wall = player->perp_wall_dist;
	SNF->dist_player = 0.0;
	if (camera->draw_start < 0)
		camera->draw_end = WINDOW_HEIGHT;
	while (y < WINDOW_HEIGHT)
	{
		SNF->current_dist = WINDOW_HEIGHT / (2.0 * y - WINDOW_HEIGHT);
		SNF->weight = (SNF->current_dist - SNF->dist_player) / \
										(SNF->dist_wall - SNF->dist_player);
		SNF->cur_fl_x = SNFW * SNF->fl_xwall + (1.0 - SNFW) * player->pos_x;
		SNF->cur_fl_y = SNFW * SNF->fl_ywall + (1.0 - SNFW) * player->pos_y;
		SNF->floor_tex_x = (int)(SNF->cur_fl_x * 64) % 64;
		SNF->floor_tex_y = (int)(SNF->cur_fl_y * 64) % 64;
		SNF->board_pattern = ((int)(SNF->cur_fl_x + SNF->cur_fl_y)) % 2;
		SNF->floor_texture = 3;
		DRAWFLOOR;
		DRAWSKY;
		y++;
	}
}

void	pixel_put_sky_n_floor(t_app *app, t_player *player, t_camera *camera)
{
	t_up_bottom		sky_n_floor;

	if (player->side == 0 && camera->raydir_x > 0)
	{
		sky_n_floor.fl_xwall = player->map_x;
		sky_n_floor.fl_ywall = player->map_y + camera->wall_x;
	}
	else if (player->side == 0 && camera->raydir_x < 0)
	{
		sky_n_floor.fl_xwall = player->map_x + 1.0;
		sky_n_floor.fl_ywall = player->map_y + camera->wall_x;
	}
	else if (player->side == 1 && camera->raydir_y > 0)
	{
		sky_n_floor.fl_xwall = player->map_x + camera->wall_x;
		sky_n_floor.fl_ywall = player->map_y;
	}
	else
	{
		sky_n_floor.fl_xwall = player->map_x + camera->wall_x;
		sky_n_floor.fl_ywall = player->map_y + 1.0;
	}
	init_floor_n_sky(app, player, camera, &sky_n_floor);
}

void	pixel_put_textures(t_app *app, t_player *player, t_camera *camera)
{
	int d;
	int y;

	y = camera->draw_start;
	while (y < camera->draw_end)
	{
		d = y * 256 - WINDOW_HEIGHT * 128 + camera->line_height * 128;
		app->tex_y = ((d * 64) / camera->line_height) / 256;
		if (player->side == 0)
			((Uint32 *)app->screen->pixels)[y * 640 + app->x] = \
		((Uint32 *)IMAGE[app->tex_num]->pixels)[64 * app->tex_y + app->tex_x];
		else if ((Uint32 *)IMAGE[app->tex_num + 1])
			((Uint32 *)SCREENPIX)[y * 640 + app->x] = \
	((Uint32 *)IMAGE[app->tex_num + 1]->pixels)[64 * app->tex_y + app->tex_x];
		else
			((Uint32 *)SCREENPIX)[y * 640 + app->x] = \
	((Uint32 *)IMAGE[app->tex_num - 1]->pixels)[64 * app->tex_y + app->tex_x];
		y++;
	}
}

void	pixel_put_map(t_app *app, t_player *player)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < app->map_size[0] - 1)
	{
		j = 0;
		while (j < app->map_size[1] - 1)
		{
			if (app->map[i][j] == 0)
				((Uint32 *)SCREENPIX)[j * 640 + i] = 0x13DC6D;
			j++;
		}
		i++;
	}
	((Uint32 *)SCREENPIX)[(int)player->pos_y * 640 + \
				(int)player->pos_x] = 0xFC1206;
}

void	draw(t_app *app, t_player *player, t_camera *camera)
{
	SDL_Rect rect;

	app->tex_num = app->map[player->map_x][player->map_y] - 1;
	if (player->side == 0)
		camera->wall_x = player->pos_y + \
				player->perp_wall_dist * camera->raydir_y;
	else
		camera->wall_x = player->pos_x + \
				player->perp_wall_dist * camera->raydir_x;
	camera->wall_x -= floor((camera->wall_x));
	app->tex_x = (int)(camera->wall_x * (double)(64));
	if (player->side == 0 && camera->raydir_x > 0)
		app->tex_x = 64 - app->tex_x - 1;
	if (player->side == 1 && camera->raydir_y < 0)
		app->tex_x = 64 - app->tex_x - 1;
	pixel_put_textures(app, player, camera);
	pixel_put_sky_n_floor(app, player, camera);
	pixel_put_map(app, player);
	rect.h = 260;
	rect.w = 260;
	rect.x = WINDOW_WIDTH / 2 - 130;
	rect.y = WINDOW_HEIGHT - 150;
	SDL_BlitSurface(IMAGE[8], NULL, app->screen, &rect);
}

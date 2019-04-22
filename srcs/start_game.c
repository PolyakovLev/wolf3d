/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 19:25:29 by ramory-l          #+#    #+#             */
/*   Updated: 2019/02/13 21:02:56 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	make_projection(t_player *player, t_camera *camera)
{
	if (player->side == 0)
		player->perp_wall_dist = (player->map_x - player->pos_x +
								(1 - player->step_x) / 2) / camera->raydir_x;
	else
		player->perp_wall_dist = (player->map_y - player->pos_y +
								(1 - player->step_y) / 2) / camera->raydir_y;
	camera->line_height = (int)(WINDOW_HEIGHT / player->perp_wall_dist);
	camera->draw_start = -camera->line_height / 2 + WINDOW_HEIGHT / 2;
	if (camera->draw_start < 0)
		camera->draw_start = 0;
	camera->draw_end = camera->line_height / 2 + WINDOW_HEIGHT / 2;
	if (camera->draw_end >= WINDOW_HEIGHT)
		camera->draw_end = WINDOW_HEIGHT - 1;
}

void	init_vars(t_app *app, t_player *player, t_camera *camera)
{
	camera->camera_x = 2 * app->x / (double)WINDOW_WIDTH - 1;
	camera->raydir_x = camera->dir_x + camera->plane_x * camera->camera_x;
	camera->raydir_y = camera->dir_y + camera->plane_y * camera->camera_x;
	player->map_x = (int)player->pos_x;
	player->map_y = (int)player->pos_y;
	player->delta_dist_x = fabs(1 / camera->raydir_x);
	player->delta_dist_y = fabs(1 / camera->raydir_y);
	camera->hit = 0;
}

void	check_hit(t_app *app, t_player *player, t_camera *camera)
{
	while (camera->hit == 0)
	{
		if (player->side_dist_x < player->side_dist_y)
		{
			player->side_dist_x += player->delta_dist_x;
			player->map_x += player->step_x;
			player->side = 0;
		}
		else
		{
			player->side_dist_y += player->delta_dist_y;
			player->map_y += player->step_y;
			player->side = 1;
		}
		if (app->map[player->map_x][player->map_y] > 0)
			camera->hit = 1;
	}
}

void	find_wall(t_player *player, t_camera *cam)
{
	if (cam->raydir_x < 0)
	{
		player->step_x = -1;
		player->side_dist_x = (player->pos_x - player->map_x) * \
								player->delta_dist_x;
	}
	else
	{
		player->step_x = 1;
		player->side_dist_x = (player->map_x + 1.0 - player->pos_x) *
							player->delta_dist_x;
	}
	if (cam->raydir_y < 0)
	{
		player->step_y = -1;
		player->side_dist_y = (player->pos_y - player->map_y) *
							player->delta_dist_y;
	}
	else
	{
		player->step_y = 1;
		player->side_dist_y = (player->map_y + 1.0 - player->pos_y) *
							player->delta_dist_y;
	}
}

void	start_game(t_app *app, t_player *player, t_camera *camera)
{
	app->x = 0;
	SDL_UpdateWindowSurface(app->window);
	while (app->x < WINDOW_WIDTH)
	{
		init_vars(app, player, camera);
		find_wall(player, camera);
		check_hit(app, player, camera);
		make_projection(player, camera);
		player_input(player, camera, app);
		draw(app, player, camera);
		app->x++;
	}
}

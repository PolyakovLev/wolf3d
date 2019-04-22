/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 23:48:55 by ramory-l          #+#    #+#             */
/*   Updated: 2019/02/13 17:15:54 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	arrows(t_player *player, t_camera *cam, t_app *app)
{
	if (player->event.key.keysym.sym == SDLK_UP)
	{
		if (!app->map[(int)(player->pos_x + \
					cam->dir_x * 0.2)][(int)(player->pos_y)])
			player->pos_x += cam->dir_x * 0.2;
		if (!app->map[(int)(player->pos_x)][(int)(player->pos_y + \
												cam->dir_y * 0.2)])
			player->pos_y += cam->dir_y * 0.2;
	}
	if (player->event.key.keysym.sym == SDLK_DOWN)
	{
		if (!app->map[(int)(player->pos_x - \
					cam->dir_x * 0.2)][(int)(player->pos_y)])
			player->pos_x -= cam->dir_x * 0.2;
		if (!app->map[(int)(player->pos_x)][(int)(player->pos_y - \
												cam->dir_y * 0.2)])
			player->pos_y -= cam->dir_y * 0.2;
	}
	if (player->event.key.keysym.sym == SDLK_q)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	if (player->event.key.keysym.sym == SDLK_o)
		SDL_SetRelativeMouseMode(SDL_TRUE);
}

void	player_input(t_player *player, t_camera *camera, t_app *app)
{
	int		old_x;
	int		old_y;
	double	x;

	while (SDL_PollEvent(&player->event))
	{
		if (player->event.type == SDL_MOUSEMOTION)
		{
			SDL_GetRelativeMouseState(&old_x, &old_y);
			x = -(double)old_x / 100.0;
			camera->olddir_x = camera->dir_x;
			camera->dir_x = camera->dir_x * cos(x) - camera->dir_y * sin(x);
			camera->dir_y = camera->olddir_x * sin(x) + camera->dir_y * cos(x);
			camera->oldplane_x = camera->plane_x;
			camera->plane_x = camera->plane_x * cos(x) - \
									camera->plane_y * sin(x);
			camera->plane_y = camera->oldplane_x * sin(x) +
								camera->plane_y * cos(x);
		}
		if ((player->event.type == SDL_QUIT) ||
			(SDL_SCANCODE_ESCAPE == player->event.key.keysym.scancode))
			player->close_request = 1;
		if (player->event.type == SDL_KEYDOWN)
			arrows(player, camera, app);
	}
}

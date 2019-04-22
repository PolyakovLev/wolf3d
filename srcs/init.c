/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 23:40:20 by ramory-l          #+#    #+#             */
/*   Updated: 2019/02/13 20:21:56 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_player_camera(t_app *app, t_player *player, t_camera *camera)
{
	player->pos_x = 22;
	player->pos_y = 12;
	player->close_request = 0;
	camera->dir_x = -1;
	camera->dir_y = 0;
	camera->plane_x = 0;
	camera->plane_y = 0.66;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_WarpMouseInWindow(app->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

int		init(t_app *app, t_player *player, t_camera *camera)
{
	int flags;
	int initted;

	flags = IMG_INIT_JPG | IMG_INIT_PNG;
	initted = IMG_Init(flags);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		ft_putendl("Couldn't initialize SDL");
		return (1);
	}
	if ((initted & flags) != flags)
	{
		ft_putendl("IMG_Init: Failed to init required jpg and png support!");
		return (1);
	}
	if (create_window(app) || create_screen(app) ||
		load_images(app) || lock_images(app))
		return (1);
	init_player_camera(app, player, camera);
	system("afplay resources/12.mp3 &");
	return (0);
}

void	clean_up(t_app *app)
{
	if (app->screen)
		SDL_FreeSurface(app->screen);
	if (app->window)
		SDL_DestroyWindow(app->window);
	if (app->map)
		ft_delete_array(app->map, app->map_size[0]);
	system("killall -STOP afplay");
	SDL_Quit();
}

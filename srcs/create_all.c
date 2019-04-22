/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:29:54 by ramory-l          #+#    #+#             */
/*   Updated: 2019/02/13 20:25:39 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	create_window(t_app *app)
{
	app->window = SDL_CreateWindow("Wolf3D",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								WINDOW_WIDTH, WINDOW_HEIGHT,
								SDL_WINDOW_RESIZABLE);
	if (!app->window)
	{
		ft_putendl("Failed to create window");
		return (1);
	}
	return (0);
}

int	create_screen(t_app *app)
{
	app->screen = SDL_GetWindowSurface(app->window);
	if (!app->screen)
	{
		ft_putendl("error creating screen");
		return (1);
	}
	return (0);
}

int	check_images(t_app *app)
{
	int i;

	i = 0;
	while (i < 9)
	{
		if (!IMAGE[i])
		{
			ft_putendl("error creating surface");
			while (i > -1)
			{
				SDL_FreeSurface(IMAGE[i]);
				i--;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	load_images(t_app *app)
{
	IMAGE[0] = IMG_Load("resources/colorstone.png");
	IMAGE[1] = IMG_Load("resources/greystone.png");
	IMAGE[2] = IMG_Load("resources/bluestone.png");
	IMAGE[3] = IMG_Load("resources/eagle.png");
	IMAGE[4] = IMG_Load("resources/mossy.png");
	IMAGE[5] = IMG_Load("resources/wood.png");
	IMAGE[6] = IMG_Load("resources/redbrick.png");
	IMAGE[7] = IMG_Load("resources/sky.png");
	IMAGE[8] = IMG_Load("resources/wheel.png");
	return (check_images(app));
}

int	lock_images(t_app *app)
{
	int i;

	i = 0;
	while (i < 8)
	{
		SDL_LockSurface(IMAGE[i]);
		i++;
	}
	return (0);
}

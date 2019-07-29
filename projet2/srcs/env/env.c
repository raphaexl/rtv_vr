/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:52:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/29 17:19:30 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_env_display_text(SDL_Renderer *r, char *m)
{
	SDL_Texture		*t;
	SDL_Color		c;
	SDL_Rect		pos;
	static	int		initialized = 0;

	if (!initialized)
	{
		c = (SDL_Color){.r = 0xFF, .g = 0xD0, .b = 0x12, .a = 0xFF};
		pos = (SDL_Rect){.x = 0, .y = SCR_HEIGHT / 2 - 5};
		t = ft_get_render_text(r, ft_font(m, "data/fonts/angelina.TTF", 64), c);
		SDL_QueryTexture(t, NULL, NULL, &pos.w, &pos.h);
		pos.x = SCR_WIDTH / 2 - pos.w / 2;
		initialized = 1;
	}
	else
	{
		c = (SDL_Color){.r = 0x0F, .g = 0x00, .b = 0x12, .a = 0xFF};
		pos = (SDL_Rect){.x = 0, .y = 7};
		t = ft_get_render_text(r, ft_font(m, "data/fonts/angelina.TTF", 42), c);
		SDL_QueryTexture(t, NULL, NULL, &pos.w, &pos.h);
		pos.x = 233 / 2 - pos.w / 2;
	}
	SDL_RenderCopy(r, t, NULL, &pos);
	SDL_DestroyTexture(t);
}

void		ft_env_load_pos(t_env *env)
{
	env->menu.pos[0] = (SDL_Rect){.x = 5, .y = 5};
	env->menu.pos[1] = (SDL_Rect){.x = START_X + 80, .y = 20};
	env->menu.pos[2] = (SDL_Rect){.x = START_X + 140, .y = 20};
	env->menu.pos[3] = (SDL_Rect){.x = START_X + 200, .y = 20};
	env->menu.pos[4] = (SDL_Rect){.x = START_X + 260, .y = 20};
	env->menu.pos[5] = (SDL_Rect){.x = START_X + 320, .y = 20};
	env->menu.pos[6] = (SDL_Rect){.x = START_X + 380, .y = 20};
	env->menu.pos[7] = (SDL_Rect){.x = START_X + 440, .y = 20};
	env->menu.pos[8] = (SDL_Rect){.x = START_X + 500, .y = 20};
	env->menu.pos[9] = (SDL_Rect){.x = START_X + 560, .y = 20};
	env->menu.pos[10] = (SDL_Rect){.x = START_X + 620, .y = 20};
	env->menu.pos[11] = (SDL_Rect){.x = START_X + 680, .y = 20};
	env->menu.pos[12] = (SDL_Rect){.x = START_X + 740, .y = 20};
	env->menu.pos[13] = (SDL_Rect){.x = 800 + START_X, .y = 20};
	env->menu.pos[14] = (SDL_Rect){.x = 860 + START_X, .y = 20};
	env->menu.pos[15] = (SDL_Rect){.x = 80 + START_X, .y = END_Y + 50};
	env->menu.pos[16] = (SDL_Rect){.x = 80 + START_X, .y = END_Y + 10};
	env->menu.pos[17] = (SDL_Rect){.x = 140 + START_X, .y = END_Y + 10};
	env->menu.pos[18] = (SDL_Rect){.x = 200 + START_X, .y = END_Y + 10};
	env->menu.pos[19] = (SDL_Rect){.x = START_X + 140, .y = END_Y + 50};
	env->menu.pos[20] = (SDL_Rect){.x = 200 + START_X, .y = END_Y + 50};
}

void		ft_env_load_all(t_env *e)
{
	int		i;

	ft_env_load_images(e);
	ft_env_load_pos(e);
	ft_inspector_init(&e->ptr, &e->inspector);
	ft_lview_init(&e->ptr, &e->lview);
	ft_cview_init(&e->ptr, &e->cview);
	i = NB_OPTIONS;
	while (--i >= 0)
	{
		SDL_QueryTexture(e->menu.img[i], NULL, NULL, &e->menu.pos[i].w,
				&e->menu.pos[i].h);
		e->menu.keys[i] = 0;
	}
}

void	ft_env_draw(t_env *e)
{
	int		i;

	SDL_SetRenderDrawColor(e->ptr.renderer, 0x20, 0x20, 0x20, 255);
	SDL_RenderClear(e->ptr.renderer);
	i = NB_OPTIONS;
	while (--i >= 0)
		SDL_RenderCopy(e->ptr.renderer, e->menu.img[i], NULL, &e->menu.pos[i]);
	ft_env_display_text(e->ptr.renderer,
			e->selected ? e->selected->name : "NONE");/* In default mode we just draw inspector elements and raytrace with ft_draw if thread are set, or render if not*/
	if (e->in.mode == DEFAULT)
	{
		ft_inspector_apply(&e->inspector, &e->selected);/* draw the UI */
		ft_lview_apply(&e->lview, &e->select);
		ft_cview_apply(&e->cview, &e->s.cam);
	/* Raytracing*/
		if (e->optimize)
			ft_draw(e);
		else
			ft_render(&e->s, e->pixels);
	}
	ft_inspector_display(&e->ptr, &e->inspector);
	ft_lview_display(&e->ptr, &e->lview);
	ft_cview_display(&e->ptr, &e->cview);
//	ft_memcpy(e->pixels, e->s.earth->data, sizeof(Uint32) * e->s.earth->w *  e->s.earth->h);
//	ft_filter_apply(e->s.filter, e->pixels);
/* render the pixels after ray tracing */
	ft_update_renderer(&e->ptr, e->pixels);
	SDL_RenderPresent(e->ptr.renderer);
}


void		ft_env_init(t_env *e, int argc, char **argv)
{
	int		w;
	int		h;

	h = 0;
	w = W_W;
	while (--argc)
	{
		if (!ft_strcmp(argv[argc], "-o"))
			e->optimize = 1;
		else
			h = argc;
	}
	ft_scene_init(&e->s, h ? argv[h] : NULL);
	e->selected = NULL;
	e->select = e->s.light;
	h = W_H;
	ft_sdl_init(&e->ptr, "42-1337 rt");
	if (!(e->pixels = (Uint32 *)malloc(sizeof(Uint32) * w * h)))
		ft_print_error("error malloc pixels");
	ft_memset(e->pixels, 0, sizeof(Uint32) * w * h);
	ft_env_load_all(e);
	SDL_SetRenderDrawColor(e->ptr.renderer, 5, 2, 51, 5);
	SDL_RenderClear(e->ptr.renderer);
	ft_env_display_text(e->ptr.renderer,
			"Loading can Take Long :seconds, minutes, hours, days...");
	SDL_RenderPresent(e->ptr.renderer);
}

void		ft_env_quit(t_env *e)
{
	int		i;

	i = NB_OPTIONS;
	while (--i >= 0)
	{
		if (e->menu.img[i])
			SDL_DestroyTexture(e->menu.img[i]);
		e->menu.img[i] = NULL;
	}
	ft_inspector_clean(&e->inspector);
	ft_lview_clean(&e->lview);
	ft_cview_clean(&e->cview);
	if (e->pixels)
		free(e->pixels);
	e->pixels = NULL;
	e->selected = NULL;
	e->select = NULL;
	ft_scene_clear(&e->s);
	ft_sdl_quit(&e->ptr);
	e = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atabala <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:43:52 by atabala           #+#    #+#             */
/*   Updated: 2019/02/04 13:45:37 by atabala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		xiter(t_pr *fr, int x, int y, int i)
{
	while (x < fr->sw)
	{
		fr->newre = 1.5 * (x - fr->sw / 2) /
			(0.5 * fr->zoom * fr->sw) + fr->movex;
		fr->newim = (y - fr->sh / 2) / (0.5 * fr->zoom * fr->sh) + fr->movey;
		i = 0;
		while (i < fr->maxiterations)
		{
			fr->oldre = fr->newre;
			fr->oldim = fr->newim;
			fr->newre = fr->oldre * fr->oldre - fr->oldim * fr->oldim + fr->cre;
			fr->newim = 2 * fr->oldre * fr->oldim + fr->cim;
			if ((fr->newre * fr->newre + fr->newim * fr->newim) > 4)
				break ;
			i++;
		}
		if (i >= fr->maxiterations)
			fr->color = 0;
		else
			fr->color = colorchoose(i, fr);
		fr->imgdata[y * fr->sw + x] = fr->color;
		x++;
	}
}

void			julia(t_pr *fr)
{
	int y;
	int x;
	int i;

	y = 0;
	x = 0;
	i = 0;
	ft_bzero(fr->imgdata, sizeof(int) * fr->sw * fr->sh);
	while (y < fr->sh)
	{
		xiter(fr, x, y, i);
		x = 0;
		y++;
	}
	mlx_put_image_to_window(fr->mlx_ptr, fr->win_ptr,
		fr->img_ptr, 0, 0);
	controlsmenu(fr);
}

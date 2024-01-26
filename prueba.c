/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:46:54 by epenaloz          #+#    #+#             */
/*   Updated: 2024/01/26 21:11:48 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


typedef struct s_data
{
	void	*img;
	void	*address;
	int		pixel_bits;
	int		line_length;
	int		endian;
}	t_data;

void	put_pixel(t_data *img, int x, int y, int color)
{
	char	*pos;

	pos = img->address + (y * img->line_length + x * (img->pixel_bits / 8));
	*(unsigned int *)pos = color;
}	

int	main(void)
{
	void	*mlx;
	void	*window;
	t_data	img;

	mlx = mlx_init();
	

	window = mlx_new_window(mlx, 1280, 720, "escribir un pixel");
	img.img = mlx_new_image(mlx, 1280, 720);
	img.address = mlx_get_data_addr(img.img, &img.pixel_bits, &img.line_length, &img.endian);
	put_pixel(&img, 20, 180, 0x00FF0000);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}

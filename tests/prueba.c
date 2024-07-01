/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:46:54 by epenaloz          #+#    #+#             */
/*   Updated: 2024/01/27 17:33:21 by epenaloz         ###   ########.fr       */
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

int	add_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_line(int color, t_data *img, int *pos, int length, char dir)
{
	while (length > 0)
	{
		if (pos[0] >= 0 && pos[0] <= 1280 && pos[1] >= 0 && pos[1] <= 720)
		{
			put_pixel(img, pos[0], pos[1], color);
			length--;
		}
		if (dir == 'l')
			pos[0]--;
		else if (dir == 'r')
			pos[0]++;
		else if (dir == 'd')
			pos[1]++;
		else if (dir == 'u')
			pos[1]--;
		if (pos[0] == 0 || pos[1] == 0)
			break ;
	}
}

int	main(void)
{
	void	*mlx;
	void	*window;
	t_data	img;
	int		color;
	int		line[] = {40, 400};

	mlx = mlx_init();
	color = add_color(0, 255, 0, 0);

	window = mlx_new_window(mlx, 1280, 720, "escribir un pixel");
	img.img = mlx_new_image(mlx, 1280, 720);
	img.address = mlx_get_data_addr(img.img, &img.pixel_bits, &img.line_length, &img.endian);
	put_pixel(&img, 20, 180, color);
	put_line(color, &img, line, 20, 'r');
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 15:26:04 by ktakami           #+#    #+#             */
/*   Updated: 2020/12/05 17:55:20 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef	struct	s_data
{
	int data;
	int bytes;
}		t_data;

typedef struct	s_bmp
{
	t_data	filetype;
	t_data	filesize;
	t_data	prepared;
	t_data	offset;
	t_data	header;
	t_data	width;
	t_data	height;
	t_data	plane;
	t_data	color_bit;
	t_data	comptype;
	t_data	img_size;
	t_data	res_width;
	t_data	res_height;
	t_data	pallet_size;
	t_data	important_color;
}		t_bmp;

t_data	create_data(int data, int bytes)
{
	t_data d;

	d.data = data;
	d.bytes = bytes;
	return (d);
}

t_bmp	initialize(int width, int height)
{
	t_bmp	bmp_data;

	bmp_data.filetype = create_data(0x424d, 2);
	bmp_data.filesize = create_data(width*4*height+54, 4);
	bmp_data.prepared = create_data(0, 4);
	//bmp_data.offset = create_data(62, 4);
	bmp_data.offset = create_data(54, 4);
	bmp_data.header = create_data(40, 4);
	bmp_data.width	= create_data(width, 4);
	bmp_data.height	= create_data(height, 4);
	bmp_data.plane = create_data(1, 2);
	bmp_data.color_bit = create_data(32, 2);
	bmp_data.comptype = create_data(0, 4);
	//bmp_data.img_size = create_data(0x40, 4);
	bmp_data.img_size = create_data(width*4*height, 4);
	bmp_data.res_width = create_data(0, 4);
	bmp_data.res_height = create_data(0, 4);
	bmp_data.pallet_size = create_data(0, 4);
	bmp_data.important_color = create_data(0, 4);
	return (bmp_data);
}

int	ft_strlen(char *s)
{
	int len;

	len =0;
	while (*s++)
		len++;
	return (len);
}

int	get_bytes(int data)
{
	int bytes;

	bytes = 1;
	while (data / 256)
	{
		data /= 256;
		bytes += 1;
	}
	return bytes;
}

void	write_recursive(int fd, int data)
{
	char c;
	if (data / 256)
		write_recursive(fd, data / 256);
	c = data % 256;
	//printf("data: %d\n", c);
	write(fd, &c, 1);
}

void	write_data(int fd, int data, int bytes)
{
	int data_bytes;
	int c;

	write_recursive(fd, data);
	data_bytes = get_bytes(data);
	//printf("data_bytes: %d\n", data_bytes);
	c = 0;
	while ((bytes - data_bytes) > 0)
	{
		write(fd, &c, 1);
		data_bytes++;
	}
}

void	write_t_data(int fd, t_data d)
{
	write_data(fd, d.data, d.bytes);
}

void	write_bmp(int fd, t_bmp bmp)
{
	write_t_data(fd, bmp.filetype);
	write_t_data(fd, bmp.filesize);
	write_t_data(fd, bmp.prepared);
	write_t_data(fd, bmp.offset);
	write_t_data(fd, bmp.header);
	write_t_data(fd, bmp.width);
	write_t_data(fd, bmp.height);
	write_t_data(fd, bmp.plane);
	write_t_data(fd, bmp.color_bit);
	write_t_data(fd, bmp.comptype);
	write_t_data(fd, bmp.img_size);
	write_t_data(fd, bmp.res_width);
	write_t_data(fd, bmp.res_height);
	write_t_data(fd, bmp.pallet_size);
	write_t_data(fd, bmp.important_color);
}

int	main()
{
	int	width;
	int	height;
	char	*path;
	char	*data;
	int	fd;
	t_bmp	bmp;

	path = "test.bmp";
        fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG);
	if (fd < 0)
	{
		printf("error\n");
		exit(1);
	}
	//data = "## ファイルヘッダ ##\n42 4d\n7e 00 00 00\n00 00\n00 00\n3e 00 00 00\n## 情報ヘッダ ##\n28 00 00 00\n10 00 00 00\n10 00 00 00\n01 00\n01 00\n00 00 00 00\n40 00 00 00\n10 00 00 00\n10 00 00 00\n00 00 00 00\n00 00 00 00\n## パレットデータ ##\nff ff ff 00\n00 00 00 00\n\n00 00 00 00\n7f fe 00 00\n40 02 00 00\n40 02 00 00\n40 02 00 00\n40 02 00 00\n40 02 00 00\n40 02 00 00\n40 02 00 00\n40 02 00 00\n40 02 00 00\n40 02 00 00\n40 02 00 0040 02 00 00\n7f fe 00 00\n00 00 00 00";
	width = 64;
	height = 32;

	bmp = initialize(width, height);
	write_bmp(fd, bmp);
	//write_data(fd, 0xffffff, 4);
	//write_data(fd, 0x0, 4);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (i == 1 || j == 1 || i == width - 2|| j == height - 2)
			{
				write_data(fd, 0x000ff00, 4);
			}
			else
			{
				write_data(fd, 0x00ffffff, 4);
			}
		}
	}
	//write_data(fd, 0x0, 4);
	//write_data(fd, 0x7ffe, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x4002, 4);
	//write_data(fd, 0x7ffe, 4);
	//write_data(fd, 0x0, 4);

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:53:56 by tjensen           #+#    #+#             */
/*   Updated: 2022/06/09 14:53:57 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_scene.h"
#include "graphic/mrt_graphic.h"

static void	print_header(void);
static void	print_header_ascii(void);

int	main(int argc, char **argv)
{
	static t_scene	scene;

	print_header();
	if (argc != 2 || !argv[1])
	{
		print_error("usage:   ./miniRT <path/to/scene_file>\
		\nexample: ./miniRT scenes/template.rt", NULL, NULL, NULL);
		return (1);
	}
	srand(time(NULL));
	if (scene_create(&scene, argv[1]))
	{
		scene_destroy(&scene);
		return (2);
	}
	graphic(&scene);
	scene_destroy(&scene);
	return (0);
}

static void	print_header(void)
{
	int	i;

	printf("%s", COLOR_YE_1);
	i = 0;
	while (i < 120)
	{
		printf("\u2591");
		i++;
	}
	print_header_ascii();
	i = 0;
	while (i < 120)
	{
		printf("\u2591");
		i++;
	}
	printf("%s\n\n", COLOR_NO);
}

static void	print_header_ascii(void)
{
	printf("\n\u2591\u2591                ____                               ");
	printf("               ____      ____        ______                      ");
	printf("\u2591\u2591\n\u2591\u2591               /\\  _\\                ");
	printf("    __                __    /\\__ \\    /\\  _`\\     /\\__  _\\ ");
	printf("                    \u2591\u2591\n\u2591\u2591               \\ ");
	printf("\\ \\/        ___ ___    /\\_\\       ___    /\\_\\   \\/_/\\ \\ ");
	printf("  \\ \\ \\L\\ \\   \\/_/\\ \\/                     \u2591\u2591\n");
	printf("\u2591\u2591                \\ \\ \\      /' __` __`\\  \\/\\ \\ ");
	printf("   /' _ `\\  \\/\\ \\     \\ \\ \\   \\ \\ ,  /      \\ \\ \\    ");
	printf("                 \u2591\u2591\n\u2591\u2591                 \\ \\");
	printf(" \\_    /\\ \\/\\ \\/\\ \\  \\ \\ \\   /\\ \\/\\ \\  \\ \\ \\    ");
	printf(" \\_\\ \\   \\ \\ \\\\ \\      \\ \\ \\                    \u2591");
	printf("\u2591\n\u2591\u2591                  \\ \\___\\  \\ \\_\\ \\_\\ ");
	printf("\\_\\  \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\    /\\___\\   \\ \\_\\ ");
	printf("\\_\\     \\ \\_\\                   \u2591\u2591\n\u2591\u2591  ");
	printf("                 \\/___/   \\/_/\\/_/\\/_/   \\/_/   \\/_/\\/_/  ");
	printf(" \\/_/    \\/___/    \\/_/\\/ /      \\/_/                   ");
	printf("\u2591\u2591\n\u2591\u2591 %-114s \u2591\u2591\n", "");
}

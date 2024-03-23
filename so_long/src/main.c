#include "../headers/so_long.h"

int32_t main(void)
{
	t_game game;
	game = (t_game){0};
	t_screen screen;
	t_map map = create_map();
	read_map(&map);
	screen.width = (map.width + 1) * 64;
	screen.height =map.height * 64;

	if (!(game.mlx = mlx_init(screen.width, screen.height, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	t_graphics graphics = create_graphics(game.mlx);
	get_map_elements(&map);
	render_images(game.mlx, graphics, map);
	// for(size_t i = 0; i < map.width; i++)
	// 	printf("%c", map.cell_value[0][i]);
	mlx_key_hook(game.mlx, &ft_keyhooks, NULL);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
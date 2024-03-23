#include "../headers/so_long.h"

int32_t main(void)
{
	mlx_t* mlx;
	t_screen screen;
	t_map map;
	read_map(&map);
	screen.width = map.width * 64;
	screen.height = map.height * 64;

	if (!(mlx = mlx_init(screen.width, screen.height, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	t_graphics graphics = create_graphics(mlx);
	render_images(mlx, graphics, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
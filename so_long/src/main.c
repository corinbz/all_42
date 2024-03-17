#include "../headers/so_long.h"

int32_t main(void)
{
	// mlx_t* mlx;

	// // Gotta error check this stuff
	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	// {
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	
	// t_graphics graphics = create_graphics(mlx);
	// if (mlx_image_to_window(mlx, graphics.player, 0, 0) < 0)
    //     ft_error("Failed to draw image to window");
	// // mlx_loop_hook(mlx, ft_hook(assets.player, mlx), mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	t_map map = create_map();
	read_map(&map);
	return (EXIT_SUCCESS);
}
// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "../LIB/MLX42/include/MLX42/MLX42.h"
#include "../include/so_long.h"

#define WIDTH 512
#define HEIGHT 512

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
	int map_file = open("maps/map.ber", O_RDONLY);
	if (map_file < 0)
		ft_error("Failed to open map file");
	t_map *map = NULL;
	read_map(map_file, map);
	return (EXIT_SUCCESS);
}

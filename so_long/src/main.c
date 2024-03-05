// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/so_long.h"

/* ***** ALOWED FUNCTIONS *****
open, close, read, write,
malloc, free, perror,
strerror, exit
• All functions of the math
library (-lm compiler option,
man man 3 math)
• All functions of the MiniLibX
• ft_printf and any equivalent
YOU coded
*/

void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}
int32_t main(void)
{
	// mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t *mlx;
	mlx = mlx_init(WIDTH, HEIGHT, "TEST", true);
	if (!mlx)
		ft_error("mlx_init failed");
	mlx_texture_t *my_character = mlx_load_png("img/my_char.png");
	if (!my_character)
		ft_error("failed to load png");
	mlx_image_t* img = mlx_texture_to_image(mlx, my_character);
	if (!img || (mlx_image_to_window(mlx, img, 20, 20) < 0))
		ft_error("failed to make img");
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
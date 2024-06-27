#include "donut.h"

// Fill text buffer with spaces and z-buffer with max values
void initialize_buffers()
{
	memset(b, 32, 1760);
	memset(z, 127, 1760);
}

// Calculate and render the shape
void render_shape(int sA, int cA, int sB, int cB)
{
	int temp;
	int sj = 0, cj = 1024;
	for (int j = 0; j < 90; j++)
	{
		int si = 0, ci = 1024;
		for (int i = 0; i < 324; i++)
		{
			int R1 = 1, R2 = 2048, K2 = 5120 * 1024;

			// Precompute some reusable values
			int x0 = R1 * cj + R2,
				x1 = ci * x0 >> 10,
				x2 = cA * sj >> 10,
				x3 = si * x0 >> 10,
				x4 = R1 * x2 - (sA * x3 >> 10),
				x5 = sA * sj >> 10,
				x6 = K2 + R1 * 1024 * x5 + cA * x3,
				x7 = cj * si >> 10;

			// Calculate screen coordinates (x, y)
			int x = 40 + 30 * (cB * x1 - sB * x4) / x6,
				y = 12 + 15 * (cB * x4 + sB * x1) / x6;

			// Calculate luminance index N
			int N = (-cA * x7 - cB * ((-sA * x7 >> 10) + x2) - ci * (cj * sB >> 10) >> 10) - x5 >> 7;

			// Calculate buffer index
			int o = x + 80 * y;
			int8_t zz = (x6 - K2) >> 15;

			// Update buffers if the current point is closer than the previous
			if (22 > y && y > 0 && x > 0 && 80 > x && zz < z[o])
			{
				z[o] = zz;
				b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
			}

			// Rotate the angle i
			R(5, 8, ci, si)
		}

		// Rotate the angle j
		R(9, 7, cj, sj)
	}
}

// Print the frame to the console
void print_frame()
{
	for (int k = 0; k < 1761; k++)
		putchar(k % 80 ? b[k] : 10);
}

void main()
{
	// inicialize angles A, B and temp variable
	int sA = 1024, cA = 0, sB = 1024, cB = 0, temp;

	// Infinite loop to render the donut
	for (;;)
	{
		initialize_buffers();
		render_shape(sA, cA, sB, cB);
		print_frame();

		// Rotate angles A and B
		R(5, 7, cA, sA);
		R(5, 8, cB, sB);

		// Pause for a short duration
		usleep(15000);

		// Move the cursor up 23 lines to overwrite the previous frame
		printf("\x1b[23A");
	}
}

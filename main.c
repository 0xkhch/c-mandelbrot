#include <stdio.h>
#include <complex.h>

#define WIDTH 800
#define HEIGHT 800
#define ITERATIONS 50

int screen[HEIGHT][WIDTH] = {0};

int main(void) {
    //f_c(z) = z^2 + c
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // map to [-2, 1] and [-1.5, 1.5]
            double a = -2 + (double)j / WIDTH * 3;
            double b = -1.5 + (double)i / HEIGHT * 3;

            double complex c = a + b * I;
            double complex z = 0;
            for (int w = 0; w < ITERATIONS; w++) {
                z = cpow(z, 2) + c;
            }
            screen[i][j] = cabs(z) > 2 ? 0 : 1;
        }
    }

    //https://en.wikipedia.org/wiki/Netpbm
    //print screen
    FILE* file = fopen("mandelbrot.ppm", "wb");
    fprintf(file, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            static unsigned char color[3];

            if (screen[i][j] == 1) {
                // black
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            }
            else {
                // white 
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
            }
            fwrite(color, 1, 3, file);
        }
    }
    return 0;
}

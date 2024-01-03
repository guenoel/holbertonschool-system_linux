#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
/* task 1 va_list*/
#include <stdarg.h>
/* task 2 */
#include <sys/types.h>

/**
* struct pixel_s - RGB pixel
*
* @r: Red component
* @g: Green component
* @b: Blue component
*/
typedef struct pixel_s
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel_t;

/**
* struct img_s - Image
*
* @w:      Image width
* @h:      Image height
* @pixels: Array of pixels
*/
typedef struct img_s
{
	size_t w;
	size_t h;
	pixel_t *pixels;
} img_t;

/**
* struct kernel_s - Convolution kernel
*
* @size:   Size of the matrix (both width and height)
* @matrix: Kernel matrix
*/
typedef struct kernel_s
{
	size_t size;
	float **matrix;
} kernel_t;

/**
* struct blur_portion_s - Information needed to blur a portion of an image
*
* @img:      Source image
* @img_blur: Destination image
* @x:        X position of the portion in the image
* @y:        Y position of the portion in the image
* @w:        Width of the portion
* @h:        Height of the portion
* @kernel:   Convolution kernel to use
*/
typedef struct blur_portion_s
{
	img_t const *img;
	img_t *img_blur;
	size_t x;
	size_t y;
	size_t w;
	size_t h;
	kernel_t const *kernel;
} blur_portion_t;

/*Functions task 0 */
void *thread_entry(void *arg);

/*Functions task 1 */
int tprintf(char const *format, ...);

/*Functions task 2 */
void blur_portion(blur_portion_t const *portion);
void apply_convolution(const img_t *img, img_t *blur_img,
						const kernel_t *kernel, size_t x, size_t y);

/*Functions task 3 */
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel);

/*Functions task 4 */
int tprintf(char const *format, ...);

/*Functions task 5 */

/*Functions task 6 */

#endif /* MULTITHREADING_H */

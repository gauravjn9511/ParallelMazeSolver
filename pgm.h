/*
 * This file contains a minimal interface for generating PGM (Portable
 * Gray Map) images.
 */

#define BLACK 0
#define GREY 150
#define WHITE 255

typedef unsigned char pixel_t;

typedef struct image_s
{
  int rows;
  int columns;
  int pixel_size;
  pixel_t *pixels;
} image_t;

image_t *pgm_create(int rows, int columns, int pixel_size, pixel_t bg);
void pgm_destroy(image_t *img);
void pgm_set_pixel(image_t *img, int row, int col, pixel_t pixel);
void pgm_save(image_t *img, char *filename);


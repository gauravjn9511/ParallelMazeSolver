 /*
  * This code was taken from https://www8.cs.umu.se/kurser/5DV050/VT12/maze.tgz
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm.h"


void pgm_save(image_t *img, const char *filename)
{
  FILE *fp;
  if (strlen(filename) < 5 || strcmp(filename + strlen(filename) - 4, ".pgm") != 0) {
    fprintf(stderr, "Invalid filename: \"%s\"\n", filename);
    return;
  }
  fp = fopen(filename, "w");
  if (fp != NULL) {
    /* Magic number (P5) */
    fprintf(fp, "P5");
    /* White space */
    fprintf(fp, " ");
    /* Width (ASCII) */
    fprintf(fp, "%d", img->columns*img->pixel_size);
    /* White space */
    fprintf(fp, " ");
    /* Height (ASCII) */
    fprintf(fp, "%d", img->rows*img->pixel_size);
    /* White space */
    fprintf(fp, " ");
    /* Maximum value (255, ASCII) */
    fprintf(fp, "255");
    /* New line */
    fprintf(fp, "\n");
    /* Raster (row-wise, one byte per pixel) */
    fwrite(img->pixels, sizeof(pixel_t), img->rows * img->columns * img->pixel_size * img->pixel_size, fp);
    fclose(fp);
  } else {
    fprintf(stderr, "Could not open file: \"%s\"\n", filename);
    return;
  }
}


void pgm_set_pixel(image_t *img, int row, int col, pixel_t pixel)
{
  int i, j;
  for (i = 0; i < img->pixel_size; ++i) 
    for (j = 0; j < img->pixel_size; ++j)
      img->pixels[(row*img->pixel_size+i)*img->columns*img->pixel_size + (col*img->pixel_size+j)] = pixel;
}


image_t *pgm_create(int rows, int columns, int pixel_size, pixel_t bg)
{
  image_t *img;
  int i, j;
  img = (image_t*)malloc(sizeof(image_t));
  img->rows = rows;
  img->columns = columns;
  img->pixel_size = pixel_size;
  img->pixels = (pixel_t*)malloc(sizeof(pixel_t) * rows * columns * pixel_size * pixel_size);
  for (i = 0; i < rows*pixel_size; ++i)
    for (j = 0; j < columns*pixel_size; ++j)
      img->pixels[i*columns*pixel_size + j] = bg;
  return img;
}


void pgm_destroy(image_t *img)
{
  free(img->pixels);
  free(img);
}



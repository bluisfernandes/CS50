#include "helpers.h"
#include <stdio.h>
#include <math.h>


void swap(RGBTRIPLE *a, RGBTRIPLE *b);
void avarage(int i, int j, int height, int width, int *r, int *g, int *b, RGBTRIPLE image[height][width]);
void sobel(int i, int j, int height, int width, int *r, int *g, int *b, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int temp = 0;


    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            //three RGB value is the avarage of past values.
            temp = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = temp;
            image[i][j].rgbtGreen = temp;
            image[i][j].rgbtBlue = temp;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //swap each pixel with your mirrored one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //initializes values to RGB and a new image
    int r, g, b;
    RGBTRIPLE image_new[height][width];
    
    //for each pixel, calc value to RGB and input them into newimage
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //function that calc every color value
            avarage(i, j, height, width, &r, &g, &b, image);
            image_new[i][j].rgbtRed = r;
            image_new[i][j].rgbtGreen = g;
            image_new[i][j].rgbtBlue = b;

        }
    }
    
    //refresh the image to the new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            image[i][j] = image_new[i][j];

        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //initializes values to RGB and a new image
    int r, g, b;
    RGBTRIPLE image_new[height][width];

    //for each pixel, calc value to RGB and input them into newimage
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //function that calcs every color value
            sobel(i, j, height, width, &r, &g, &b, image);
            image_new[i][j].rgbtRed = r;
            image_new[i][j].rgbtGreen = g;
            image_new[i][j].rgbtBlue = b;

        }
    }
    
    //refresh the image to the new image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_new[i][j];
        }
    }
    
    return;
}



//Swap values with pointers
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}

//calculates the avarage of 3x3
void avarage(int i, int j, int height, int width, int *r, int *g, int *b, RGBTRIPLE image[height][width])
{
    int sumr = 0;
    int sumg = 0;
    int sumb = 0;
    float count = 0;

    
    for (int x = i - 1; x <= i + 1; x++)
    {
        for (int y = j - 1; y <= j + 1; y++)
        {
            if (x < 0 || y < 0 || x > height - 1 || y > width - 1)
            {
                //nothing to do here
            }
            else
            {
                sumr += image[x][y].rgbtRed;
                sumg += image[x][y].rgbtGreen;
                sumb += image[x][y].rgbtBlue;
                count++;
            }
        }
    }
   
    //refresh RGB values
    *r = (int) round(sumr / count);
    *g = (int) round(sumg / count);
    *b = (int) round(sumb / count);

    return;
}


void sobel(int i, int j, int height, int width, int *r, int *g, int *b, RGBTRIPLE image[height][width])
{
    double sum_gx_r = 0;
    double sum_gx_g = 0;
    double sum_gx_b = 0;   
    double sum_gy_r = 0;
    double sum_gy_g = 0;
    double sum_gy_b = 0;

    //Declares Sobel Operator kernels
    // int gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    // int gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    int gx[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
    int gy[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
    
    //for each pixel, calc the product with Gy and Gx 
    //then, summ the values
    for (int x = i - 1; x <= i + 1; x++)
    {
        for (int y = j - 1; y <= j + 1; y++)
        {
            if (x < 0 || y < 0 || x > height - 1 || y > width - 1)
            {

            }
            else
            {
                sum_gx_r += image[x][y].rgbtRed * gx[x - i + 1][y - j + 1];
                sum_gx_g += image[x][y].rgbtGreen * gx[x - i + 1][y - j + 1];
                sum_gx_b += image[x][y].rgbtBlue * gx[x - i + 1][y - j + 1];
                
                sum_gy_r += image[x][y].rgbtRed * gy[x - i + 1][y - j + 1];
                sum_gy_g += image[x][y].rgbtGreen * gy[x - i + 1][y - j + 1];
                sum_gy_b += image[x][y].rgbtBlue * gy[x - i + 1][y - j + 1];
             
            }
        }
    }
    // printf("count: %d\n",count);
    *r = (int) fmin(round(pow(pow(sum_gx_r, 2) + pow(sum_gy_r, 2), 0.5)), 255);
    *g = (int) fmin(round(pow(pow(sum_gx_g, 2) + pow(sum_gy_g, 2), 0.5)), 255);
    *b = (int) fmin(round(pow(pow(sum_gx_b, 2) + pow(sum_gy_b, 2), 0.5)), 255);
    
    //printf("%d,%d|  %f  \t%f  \t%d\n",i,j, sum_gx_r, sum_gy_r, *r);
    
    return;
}
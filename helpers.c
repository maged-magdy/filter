#include "helpers.h"
#include <math.h>

void swap(RGBTRIPLE *x,RGBTRIPLE *y)
{
    RGBTRIPLE temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0;i < height; i++)
    {
        for(int j = 0;j < width;j++)
        {
            float avg = (float)(image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen) / 3;
            avg = round(avg);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen= avg;
            image[i][j].rgbtRed = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height ; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            float sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            float sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            float sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            swap(&image[i][j],&image[i][width-j-1]);
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for(int i=0 ;i<height ;i++)
    {
        for(int j=0; j<width ;j++)
        {
            copy[i][j]=image[i][j];
        } 
           
    } 
       

    for (int i=0 ; i< height;i++)
    {
        for(int j=0 ;j<width ;j++)
        {  
            int r_sum=0; 
            int g_sum=0;
            int b_sum=0;
            float count=0.0;
            
            for(int k=i-1 ;k <= i+1 ;k++)
            {
                for(int l=j-1;l<= j+1 ;l++)
                {
                    if ( (k>=0) && (l>=0) && (k<height) &&  (l<width) )
                    {
                        r_sum = r_sum + copy[k][l].rgbtRed;
                        g_sum = g_sum + copy[k][l].rgbtGreen;
                        b_sum = b_sum + copy[k][l].rgbtBlue;
                        count++;
                    }
                        else
                  {
                    continue;
                  }
                }
            }
            
            image[i][j].rgbtRed = round(r_sum/count);
            image[i][j].rgbtGreen = round(g_sum/count);
            image[i][j].rgbtBlue = round(b_sum/count);
            
            if(image[i][j].rgbtRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            if(image[i][j].rgbtGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            if(image[i][j].rgbtBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
return;
}

//
//  part1.cpp
//  threshold
//
//  Created by Gurman Gill on 9/8/17.
//  Copyright © 2017 Gurman Gill. All rights reserved.
//
// Authors : Gabriel Duarte and Roberto Rojas
// Date : 9/18/2017
// Description : We will be manipulating bits to change the image bits to make them darker or lighter
#include <iostream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

int main(int argc, const char * argv[]) {

    //Store image to load in a variable
    const char* filename = "bergen.jpg"; //Try different images by replacing this string
    CImg<unsigned char> img1(filename); //Reads the image and stores pixel values in img1
    
    int w = img1.width(); //Gets width of image
    int h = img1.height(); //Gets height of image
    int channels = img1.spectrum(); //Gets number of channels
    
    cout << "Successfully loaded image of size " << w << " x " << h << " x " << channels << endl;
    
    // Create a title for the image comprising of: name of image and its dimensions (width, height, channels).
    // Channels = 1 implies its a gray level image, =3 implies its a color image.
    char title[100];
    sprintf(title, "%s (%d x %d x %d)", filename, w, h, channels);

    // Create a display
    CImgDisplay disp(img1, title, 0); //This will show the image but close it instantly
    img1.display(disp, false); //This command will ensure image stays on the screen
    
    CImg<unsigned char> img2(img1); //Creates a copy of img1 into img2
    
    // Iterate through the image img2 using a nested for loop. Note img2(x, y) corresponds to the pixel value at x and y coordinates.
    // TASK 1: Modify img2 to store just the most significant bit. For example:
            //pixel value 0b00110101 will become 0b00000000 (because most significant bit is 0)
            //pixel value 0b10110101 will become 0b10000000 (because most significant bit is 1)
    
    //TODO::Enter code here.. based on nested for loop.. *****(ONLY EMPLOY BIT MANIPULATIONS)*****
    for (int i = 0; i < w; i++)
    for (int j = 0; j < h; j++)
    if (img2(i,j) > 0b10000000 == 0) // This is checking to see if there is a zero or one
      img2(i,j) = img2(i,j) & 0b00000000; // This is the bitwise operator & and changes the values 
      else
      if (img2(i,j) >= 0b10000000)  // This is checking to see if there is a zero or one
        img2(i,j) = img2(i,j) & 0b10000000;  // This is the bitwise operator & and changes the values 
    
    img2.display(disp, false); //Use the same display window created earlier to display this image
    //Save the image img2 onto disk
    img2.save_png("img2.png");
    
    //img2 has two shades (0 and 128) and therefore looks dull.
    //Create, display and save a new image img3 that has pixel value 0 when the most significant bit (in original image) is 0 but has pixel value 0xFF (255) when the most significant bit (in original image) is 1.
    CImg<unsigned char> img3(img1);
    
    //TODO: Enter code here.. based on nested for loop..
     for (int i = 0; i < w; i++)
     for (int j = 0; j < h; j++)
     if (img3(i,j) > 0b10000000)
       img3(i,j) = 0xFF; // This is going to change the pixels to white when the most significant bit is 1
       else
       if (img3(i,j) <= 0b10000000) 
         img3(i,j) = 0b00000000; // This is going to change the pixel to black when the most significant bit is 0
        
    CImgDisplay disp3((img1, img2, img3), title, 0); //Create a new display to show all three images simultaneously
    (img1, img2, img3).display(disp3, false);

    //Save the image img3 onto disk
    img3.save_png("img3.png");
    
    //TASK 2: Let's brighten up our day ..err.. brighten up the image by multiplying each pixel value by 2.
    //Use left shifting by one bit to accomplish this.
    
    CImg<unsigned char> img4(img1); //Create a copy of img1 into img4 (in which the brightened image will be stored)
    
	//TODO: Enter code here.. based on nested for loop *****(ONLY EMPLOY BIT MANIPULATIONS)*****
  	for (int i = 0; i < w; i++)
    for (int j = 0; j < h; j++)
    if (img4(i,j) >= 0b00000000) // We are checking to see if it is infact a bit 
        img4(i,j) = img4(i,j) << 1; // Then we are left shifting the each bit by one
	 
    //Save the image img4 onto disk
    img4.save_png("img4.png");
    //img4 does not look like a brightened version of img1 at all. What's going wrong? Well, let's say pixel value is stored in variable val. If after doubling the pixel value, the result exceeds 255 it will be rounded off to 2*val - 255.

	
    //Create, display and save a new image img5 that caps the pixel value to 255 if after doubling the result exceeds 255.
    CImg<unsigned char> img5(img1);
    
	//TODO: Enter code here.. based on nested for loop..
      	for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
          if ((img5(i,j) << 1) > 0xFF) // This is asking if after left shifting, if the value is greater than 255 
            img5(i,j) = 0xFF;          // Then you want to set that pixel to 255 for a maximum
          else if ((img5(i,j) << 1) < 0xFF) // If the bit is less than white (255)
            img5(i,j) = img5(i,j) << 1;     // then left shift it with out having to make the white adjustment
            
    (img1, img4, img5).display(disp3, false); //Show these three images simultaneously
    //Save the image img5 onto disk
    img5.save_png("img5.png");

    
    
    return 0;
}

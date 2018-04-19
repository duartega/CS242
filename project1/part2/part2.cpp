//
//  part2.cpp
//
//  Created by Gurman Gill on 9/8/17.
//  Copyright © 2017 Gurman Gill. All rights reserved.
//
// Authors : Gabriel Duarte and Roberto Rojas
// Date : 9/18/2017
// Description : We will be manipulating bits to change the logo image bits to make them darker or lighter
//               We are also using different masked images to display over an image.
#include <iostream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

int main(int argc, const char * argv[]) {
    string firstFile = ""; // This is going to get the first file name (background image)
    string secondFile = ""; // This is going to get the logo name (second file)
    cout << "Enter the filenames corresponding to the Image and the Logo (in that order): " << endl; // Ask the user for input
    cin >> firstFile; // Store the first image name in a string
    cin >> secondFile; // Store the second image name in a string

    const char* filename = firstFile.c_str(); // Use the firstFile name and convert it so that we can read the string
    CImg<unsigned char> initialImage(filename); // Open the image and name it initialImage which is the background image
    
    const char* filename2 = secondFile.c_str(); // Use the secondFile name and convert it so that we can read the string
    CImg<unsigned char> logo(filename2); // Open the image and name it initialImage which is the background image
    
    int w = initialImage.width(); // Get the width of the first image (initialImage)
    int h = initialImage.height(); // Get the height of the first image (initialImage)
    int channels = initialImage.spectrum(); 
    
    // We let the user know that the image was loaded successfully and the width and height
    cout << "Successfully loaded image " << firstFile << " of size " << w << " x " << h << " x " << channels << endl;
    
    int w2 = logo.width(); // Get the width of the logo image
    int h2 = logo.height(); // Get the height of the logo image
    channels = logo.spectrum();
    
    // We let the user know that the image was loaded successfully and the width and height
    cout << "Successfully loaded image " << secondFile << " of size " << w2 << " x " << h2 << " x " << channels << endl;
    
    // We ask the user for the position that they want to see the image at
    cout << "Enter the position in (x, y) coordinates where this logo must be placed." << endl << "x must be between 0 and 239 and y must be between 0 and 191." << endl;
    int x1 = 0; // Initialize the variable
    int y1 = 0; // Initialize the variable
    cin >> x1; // Read in the x coordinate
    cin >> y1; // Read in the y coordinate

    char title[100];
    sprintf(title, "%s (%d x %d x %d)", filename, w, h, channels);


     //CImgDisplay disp(initialImage, title, 0); // Display the initialImage
     CImg<unsigned char> cpimg(initialImage); // Copy initialImage into cpimg
     CImg<unsigned char> logoimg(logo); // Copy logo into logoimg
 
 
// Threshold turns background white
    for (int i = 0; i < w2; i++)
    for (int j = 0; j < h2; j++)
    if (logo(i,j) < 0b11000000)
      logo(i,j) = logo(i,j) & 0b00000000; // Make the pixels black
      else
      if (logo(i,j) >= 0b11000000)  
        logo(i,j) = logo(i,j) & 0xFF; // Make the pixels white
        
        
     CImg<unsigned char> logoinverse(logo); // Copy the logo into logoinverse
 
     for (int i = 0; i < w2; i++)
      for (int j = 0; j < h2; j++)
        logoinverse(i,j) = ~logoinverse(i,j); // Takes the inverse of every pixel
        
        
        CImg<unsigned char> inverseandlogo(logoimg); // Copy the modified logoimg into inverseandlogo
        
    for (int i = 0; i < w2; i++)
    for (int j = 0; j < h2; j++)
      inverseandlogo(i,j) = inverseandlogo(i,j) & logoinverse(i,j); // Uses the bitwise operator to merge the two essentially

        
      for (int x = x1; x < x1+w2; x++)
      for (int y= y1; y < y1+h2; y++)
      {
      initialImage(x,y) = initialImage(x,y) & logo(x-x1,y-y1); // Uses the bitwise operator to merge the two essentially
      }

      for (int x = x1; x < x1+w2; x++)
      for (int y= y1; y < y1+h2; y++)
      { 
      if (initialImage(x,y) == 0x00)
      initialImage(x,y) = initialImage(x,y) | inverseandlogo(x-x1,y-y1); // Uses the bitwise operator to merge the two essentially
  
      }
       CImgDisplay dualDisplay((cpimg, initialImage), 0); // Display both images at once side by side
       (cpimg, initialImage).display(dualDisplay, false); // Keep the display open
       initialImage.save_png("imgLogo.png"); // Saves the image to the disk
      
 return 0;
 }
     
   
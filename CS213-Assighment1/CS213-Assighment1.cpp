/*
  Assignment 1 - OOP Course
  ---------------------------------------------------------------------------------------------------
  Team Members:
  1. Abdelrahman Amr Rashad           | ID: 20250366 | Section: S29 , S30 | Filters: 4, 8 , 12 , 16
  2. Zeyad Ahmed Abdullah             | ID: 20250244 | Section: S29 , S30 | Filters: 2, 6 , 10 , 14
  3. Ahmed Tarek El-gelany            | ID: 20250035 | Section: S29 , S30 | Filters: 1, 5 , 9  , 13
  4. Seif El-Deen Mohamed Hassanin    | ID: 20250310 | Section: S29 , S30 | Filters: 3, 7 , 11 , 15
  ---------------------------------------------------------------------------------------------------
*/

#include <iostream>
#include "Image_Class.h"
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

//All filter choices
enum enFiltersChoice {GrayScale =1 , BlackAndWhite , Invert , AddFrame , Flip , Rotate , DarkenAndLighten , Resize
	,Merge, DetectEdge , Crop, Blur, AddSunlight, TvStudioEffect, PurpleFilter, InfraredFilter , eExit};

//Asks the user to enter the name of the image to add filter
Image loadImagefromUser() 
{
	string image_name;
	cout << "Enter the image name to add Filter : " << endl;
	cin >> image_name;

	Image userImage(image_name);
	return userImage;
}

//save the image after performing the filter
void saveImageByUserName(Image& image) 
{
	system("cls");

	string newImageName;
	cout << "Enter the new image name to save" << endl;
	cout << "and specify extension .jpg, .bmp, .png, .tga: ";
	cin >> newImageName;

	image.saveImage(newImageName);
	cout << "\nImage saved successfully as \'" << newImageName << "\'!\n";
}

void printFiltersMenu()
{
	system("cls");

	cout << "=============================================\n";
	cout << "\t\tFilters Menu";
	cout << "\n=============================================\n\n";
	cout << "[1] Grayscale Conversion\n";
	cout << "[2] Black & White\n";
	cout << "[3] Invert Image\n";
	cout << "[4] Add Frame\n";
	cout << "[5] Flip Image\n";
	cout << "[6] Rotate Image\n";
	cout << "[7] Darken and Lighten Image\n";
	cout << "[8] Resize Image\n";
	cout << "[9] Merge Images\n";
	cout << "[10] Detect Edge\n";
	cout << "[11] Crop Image\n";
	cout << "[12] Blur Image\n";
	cout << "[13] Add Sunlight\n";
	cout << "[14] Tv Studio Effect\n";
	cout << "[15] Purple Filter\n";
	cout << "[16] Infrared Filter\n";
	cout << "[17] Exit Program\n";
	cout << "\n=============================================\n";
}

short readFilterChoice()
{
	short filterChoice;

	cout << "\nEnter your choice...?\n";
	cin >> filterChoice;

	while (filterChoice < 1 || filterChoice > 17)
	{
		cout << "\nEnter your choice \"It must be from 1 to 17\"...?\n";
		cin >> filterChoice;
	}

	return filterChoice;
}

//A part of add frame to a picture filter
void AddSimpleFrame(Image& OriginalImage)
{
	system("cls");

	int width = OriginalImage.width , height = OriginalImage.height;
	int minDim = min(width, height);
	int thickness = minDim * 0.03;

	for (int i = 0; i < width ; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i >= width - thickness || i < thickness
				|| j < thickness || j >= height - thickness)
			{
				OriginalImage.setPixel(i, j, 0, 20);
				OriginalImage.setPixel(i, j, 1, 30);
				OriginalImage.setPixel(i, j, 2, 70);
			}
		}
	}

	saveImageByUserName(OriginalImage);
}

//A part of add frame to a picture filter
void AddFancyFrame(Image& OriginalImage)
{
	system("cls");

	int width = OriginalImage.width, height = OriginalImage.height;
	int minDim = min(width, height);
	int BlueThickness = minDim * 0.06;
	int YellowThickness = minDim * 0.03;
	int corner = minDim * 0.03;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			bool isCorner = (i < corner && j < corner) || (i >= width - corner && j < corner)
				|| (i < corner && j >= height - corner) || (i >= width - corner && j >= height - corner);

			bool isBlueThickness = (i >= width - BlueThickness || i < BlueThickness
				|| j < BlueThickness || j >= height - BlueThickness);

			bool leftLine = (i >= YellowThickness && i < BlueThickness) && (j > YellowThickness && j < height - YellowThickness);

			bool rightLine = (i <= width - YellowThickness && i > width - BlueThickness) && (j > YellowThickness && j < height - YellowThickness);

			bool topLine = (j >= YellowThickness && j < BlueThickness) && (i > YellowThickness && i < width - YellowThickness);

			bool bottomLine = (j <= height - YellowThickness && j >= height - BlueThickness) && (i > YellowThickness && i < width - YellowThickness);

			if (isBlueThickness)
			{
				OriginalImage.setPixel(i, j, 0, 20);
				OriginalImage.setPixel(i, j, 1, 30);
				OriginalImage.setPixel(i, j, 2, 70);
			}

			if (isCorner)
			{
				OriginalImage.setPixel(i, j, 0, 230);
				OriginalImage.setPixel(i, j, 1, 190);
				OriginalImage.setPixel(i, j, 2, 70);
			}

			if (leftLine || rightLine || topLine || bottomLine)
			{
				OriginalImage.setPixel(i, j, 0, 200);
				OriginalImage.setPixel(i, j, 1, 160);
				OriginalImage.setPixel(i, j, 2, 50);
			}
		}
	}

	saveImageByUserName(OriginalImage);
}

// Add frame to a picture (Filter 4)
void AddFrameFilter(Image& OriginalImage)
{
	system("cls");

	int frameChoice;

	cout << "What frame do you prefer?\n";
	cout << "\n[1] Simple Frame\n";
	cout << "\n[2] Fancy Frame\n\n";
	cout << "Enter your choice...?\n";

	cin >> frameChoice;

	while (frameChoice < 1 || frameChoice > 2)
	{
		cout << "Enter your choice 1 or 2?\n";
		cin >> frameChoice;
	}

	if (frameChoice == 1)
	{
		AddSimpleFrame(OriginalImage);
	}
	else
	{
		AddFancyFrame(OriginalImage);
	}

}

// A part of Resize function
void PerformTheResize(Image & OriginalImage, int resizeChoice)
{
	system("cls");

	int ResizedWidth = 0, ResizedHeigth = 0 , ratio;
	float percOfI , PercOfJ;

	

	if (resizeChoice == 1)
	{
		cout << "Please, enter the width..?\n";
		cin >> ResizedWidth;

		while (ResizedWidth <= 0)
		{
			cout << "\nEnter a posative width..?\n";
			cin >> ResizedWidth;
		}

		cout << "\nPlease, enter the heigth..?\n";
		cin >> ResizedHeigth;

		while (ResizedHeigth <= 0)
		{
			cout << "\nEnter a posative heigth..?\n";
			cin >> ResizedHeigth;
		}
	}
	else
	{
		cout << "Please, enter the ratio..?\n";
		cin >> ratio;

		while (ratio <= 0)
		{
			cout << "\nEnter a posative ratio..?\n";
			cin >> ratio;
		}

		ResizedWidth = (ratio / 100.0) * OriginalImage.width;
		ResizedHeigth = (ratio / 100.0) * OriginalImage.height;
	}

	Image ResizedsImage(ResizedWidth, ResizedHeigth);

	for (int i = 0; i < ResizedWidth; i++)
	{
		for (int j = 0; j < ResizedHeigth; j++)
		{	
			percOfI = float(i) / ResizedWidth;
			PercOfJ = float(j) / ResizedHeigth;

			ResizedsImage(i, j, 0) = OriginalImage(percOfI * OriginalImage.width, PercOfJ * OriginalImage.height, 0);
			ResizedsImage(i, j, 1) = OriginalImage(percOfI * OriginalImage.width, PercOfJ * OriginalImage.height, 1);
			ResizedsImage(i, j, 2) = OriginalImage(percOfI * OriginalImage.width, PercOfJ * OriginalImage.height, 2);
		}
	}

	saveImageByUserName(ResizedsImage);
}

// Resize picture dimensions (Filter 8)
void resizeFilter(Image & OriginalImage)
{
	system("cls");

	int resizeChoice;

	cout << "What method do you prefer to use?\n";
	cout << "\n[1] Resize using Dimensions\n";
	cout << "\n[2] Resize using Ratio\n\n";
	cout << "Enter your choice...?\n";

	cin >> resizeChoice;

	while (resizeChoice < 1 || resizeChoice > 2)
	{
		cout << "Enter your choice 1 or 2?\n";
		cin >> resizeChoice;
	}

	PerformTheResize(OriginalImage, resizeChoice);

}

// Black and white (Filter 2)
struct Pixel 
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

void blackAndWhiteFilter(Image& img) 
{
	system("cls");

	for (int i = 0; i < img.width; ++i) {
		for (int j = 0; j < img.height; ++j) {
			Pixel p;
			p.r = img.getPixel(i, j, 0);
			p.g = img.getPixel(i, j, 1);
			p.b = img.getPixel(i, j, 2);

			int gray = (p.r + p.g + p.b) / 3;

			unsigned char bwValue = (gray > 127) ? 255 : 0;

			img.setPixel(i, j, 0, bwValue);
			img.setPixel(i, j, 1, bwValue);
			img.setPixel(i, j, 2, bwValue);
		}
	}
}

//Rotate Image (Filter 6)
void rotateImage(Image& image) 
{
	system("cls");

	int choice;
	cout << "Choose rotation angle:\n";
	cout << "1. Rotate 90 degrees clockwise\n";
	cout << "2. Rotate 180 degrees clockwise\n";
	cout << "3. Rotate 270 degrees clockwise\n";
	cout << "Enter your choice (1/2/3): ";
	cin >> choice;

	while (choice < 1 || choice > 3)
	{
		cout << "\nEnter your choice \"It has to be from 1 to 3\"\n";
		cin >> choice;
	}

	int originalWidth = image.width;
	int originalHeight = image.height;

	if (choice == 1) { // Rotate 90
		Image rotated(originalHeight, originalWidth);
		for (int i = 0; i < originalHeight; ++i) {
			for (int j = 0; j < originalWidth; ++j) {
				for (int k = 0; k < image.channels; ++k) {
					rotated.setPixel(originalHeight - 1 - i, j, k, image.getPixel(j, i, k));
				}
			}
		}
		image = rotated;
	}
	else if (choice == 2) { // Rotate 180
		Image rotated(originalWidth, originalHeight);
		for (int i = 0; i < originalHeight; ++i) {
			for (int j = 0; j < originalWidth; ++j) {
				for (int k = 0; k < image.channels; ++k) {
					rotated.setPixel(originalWidth - 1 - j, originalHeight - 1 - i, k, image.getPixel(j, i, k));
				}
			}
		}
		image = rotated;
	}
	else if (choice == 3) { // Rotate 270
		Image rotated(originalHeight, originalWidth);
		for (int i = 0; i < originalHeight; ++i) {
			for (int j = 0; j < originalWidth; ++j) {
				for (int k = 0; k < image.channels; ++k) {
					rotated.setPixel(i, originalWidth - 1 - j, k, image.getPixel(j, i, k));
				}
			}
		}
		image = rotated;
	}
}

void backToFiltersMenu()
{
	cout << "\nPress any key to return to Filters Menu.....";
	system("pause>0");

	printFiltersMenu();
}

void printCredits()
{
	system("cls");

	cout << "=====================================================================\n";
	cout << "\t\tThe Program has been DONE by\n";
	cout << "=====================================================================\n";
	cout << left << setw(32) << "Abdelrahman Amr Rashad" << " | ID: " << "20250366" << " | " << "Filters: 4/8/12/16\n";
	cout << left << setw(32) << "Zeyad Ahmed Abdullah" << " | ID: " << "20250244" << " | " << "Filters: 2/6/10/14\n";
	cout << left << setw(32) << "Ahmed Tarek El-gelany" << " | ID: " << "20250035" << " | " << "Filters: 1/5/9/13\n";
	cout << left << setw(32) << "Seif El-Deen Mohamed Hassanin" << " | ID: " << "20250310" << " | " << "Filters: 3/7/11/15\n";
	cout << "=====================================================================\n\n";

	cout << "Press any key to end the program....";
	system("pause>0");
}

// Grayscale filter (1)
void applyGrayscale(Image& image) 
{
	system("cls");

	for (int i = 0; i < image.height; ++i) {
		for (int j = 0; j < image.width; ++j) {
			int red = image(j, i, 0);
			int green = image(j, i, 1);
			int blue = image(j, i, 2);

			int avg = (red + green + blue) / 3;

			image(j, i, 0) = avg;
			image(j, i, 1) = avg;
			image(j, i, 2) = avg;
		}
	}
}

// Invert image filter (3)
void invertImage(Image& originalImg) {
	for (int i = 0; i < originalImg.width; i++) {
		for (int j = 0; j < originalImg.height; j++) {
			int red = originalImg(i, j, 0);
			int green = originalImg(i, j, 1);
			int blue = originalImg(i, j, 2);

			int newRed = 255 - red;
			int newGreen = 255 - green;
			int newBlue = 255 - blue;

			originalImg(i, j, 0) = newRed;
			originalImg(i, j, 1) = newGreen;
			originalImg(i, j, 2) = newBlue;
		}
	}
}

// filter Darken and Lighten Image (7)
void darkenAndLightenImage(Image& img) 
{
	system("cls");

	int choice;
	cout << "1 for darken, 2 for lighten: ";
	cin >> choice;

	for (int i = 0; i < img.width; i++) {
		for (int j = 0; j < img.height; j++) {
			int red = img(i, j, 0);
			int green = img(i, j, 1);
			int blue = img(i, j, 2);

			if (choice == 1) {
				red = red / 2;
				green = green / 2;
				blue = blue / 2;
			}
			else if (choice == 2) {
				red = (red + 255) / 2;
				green = (green + 255) / 2;
				blue = (blue + 255) / 2;
			}

			img(i, j, 0) = red;
			img(i, j, 1) = green;
			img(i, j, 2) = blue;
		}
	}
}

//Flip Image Filter (5)
void flipImage(Image& img) 
{
	system("cls");

	int choice;
	cout << "1. Horizontal Flip\n";
	cout << "2. Vertical Flip\n";
	cin >> choice;

	if (choice == 1) {
		for (int i = 0; i < img.width / 2; i++) {
			for (int j = 0; j < img.height; j++) {
				for (int k = 0; k < 3; k++) {
					int temp = img(i, j, k);
					img(i, j, k) = img(img.width - 1 - i, j, k);
					img(img.width - 1 - i, j, k) = temp;
				}
			}
		}
	}

	else if (choice == 2) {
		for (int i = 0; i < img.width; i++) {
			for (int j = 0; j < img.height / 2; j++) {
				for (int k = 0; k < 3; k++) {
					int temp = img(i, j, k);
					img(i, j, k) = img(i, img.height - 1 - j, k);
					img(i, img.height - 1 - j, k) = temp;
				}
			}
		}
	}
}

// filter (10)
void detectEdges(Image& img)
{
	system("cls");

	int width = img.width;
	int height = img.height;

	Image edgeImage(width, height);

	int threshold = 30;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			int R = img.getPixel(j, i, 0);
			int G = img.getPixel(j, i, 1);
			int B = img.getPixel(j, i, 2);
			int Gray = (R + G + B) / 3;

			int rightGray = Gray;
			int downGray = Gray;

			if (j + 1 < width)
			{
				int rightR = img.getPixel(j + 1, i, 0);
				int rightG = img.getPixel(j + 1, i, 1);
				int rightB = img.getPixel(j + 1, i, 2);
				rightGray = (rightR + rightG + rightB) / 3;
			}

			if (i + 1 < height) {
				int downR = img.getPixel(j, i + 1, 0);
				int downG = img.getPixel(j, i + 1, 1);
				int downB = img.getPixel(j, i + 1, 2);
				downGray = (downR + downG + downB) / 3;
			}
			int diffX = abs(Gray - rightGray);
			int diffY = abs(Gray - downGray);

			if (diffX > threshold || diffY > threshold) {
				edgeImage.setPixel(j, i, 0, 0);
				edgeImage.setPixel(j, i, 1, 0);
				edgeImage.setPixel(j, i, 2, 0);
			}
			else {
				edgeImage.setPixel(j, i, 0, 255);
				edgeImage.setPixel(j, i, 1, 255);
				edgeImage.setPixel(j, i, 2, 255);
			}
		}
	}
	img = edgeImage;
}

//part of optimizedBlur filter (12)
vector<vector<long long>> prefixSumArray(Image& img , int channel)
{
	int height = img.height;
	int width = img.width;

	vector<vector<long long>> vPrefix(width, vector<long long>(height, 0));

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			short currentPixel = img.getPixel(i, j, channel);
			long long sum = 0;
			long long top = 0;
			long long topLeft = 0;
			long long left = 0;

			if (j - 1 < 0) // row out of boundry
			{
				if (i - 1 < 0) // column out of boundry
				{
					if (i - 1 < 0 && j - 1 < 0)
					{
						sum = currentPixel;

						vPrefix[i][j] = sum;
					}
				}
				else
				{
					left = vPrefix[i - 1][j];
					sum = currentPixel + left;
					vPrefix[i][j] = sum;
				}
			}
			else // row in boundry
			{
				if (i - 1 < 0) // column out of boundry
				{
					top = vPrefix[i][j-1];
					sum = currentPixel + top;
					vPrefix[i][j] = sum;
				}
				else // column in boundry
				{
					top = vPrefix[i][j - 1];
					left = vPrefix[i - 1][j];
					topLeft = vPrefix[i - 1][j - 1];
					sum = currentPixel + top + left - topLeft;
					vPrefix[i][j] = sum;
				}
			}
		}
	}

	return vPrefix;
}

// filter (12)
void applyOptimizedBlur(Image& img)
{
	vector<vector<long long>> vPrefixRed = prefixSumArray(img, 0);
	vector<vector<long long>> vPrefixGreen = prefixSumArray(img, 1);
	vector<vector<long long>> vPrefixBlue = prefixSumArray(img, 2);

	int radius = max(3, (int)(img.width * 0.01));

	for (int i = 0; i < img.width; i++)
	{
		for (int j = 0; j < img.height; j++)
		{
			int bottomRightBoundryi = min(img.width - 1, i + radius);
			int bottomRightBoundryj = min(img.height - 1, j + radius);

			int topRighti = bottomRightBoundryi;
			int topRightj = max(0, j - (radius + 1));

			int bottomLefti = max(0, i - (radius + 1));
			int bottomLeftj = bottomRightBoundryj;

			int commoni = max(0, i - (radius + 1));
			int commonj = max(0, j - (radius + 1));

			int startI = max(0, i - radius);
			int startJ = max(0, j - radius);

			int pixelsX = bottomRightBoundryi - startI + 1;
			int pixelsY = bottomRightBoundryj - startJ + 1;

			int howManyPixels = pixelsX * pixelsY;

			int sumR = 0;
			int sumG = 0;
			int sumB = 0;

			sumR = vPrefixRed[bottomRightBoundryi][bottomRightBoundryj] - vPrefixRed[topRighti][topRightj]
				- vPrefixRed[bottomLefti][bottomLeftj] + vPrefixRed[commoni][commonj];

			img.setPixel(i, j, 0, sumR / howManyPixels);

			sumG = vPrefixGreen[bottomRightBoundryi][bottomRightBoundryj] - vPrefixGreen[topRighti][topRightj]
				- vPrefixGreen[bottomLefti][bottomLeftj] + vPrefixGreen[commoni][commonj];

			img.setPixel(i, j, 1, sumG / howManyPixels);

			sumB = vPrefixBlue[bottomRightBoundryi][bottomRightBoundryj] - vPrefixBlue[topRighti][topRightj]
				- vPrefixBlue[bottomLefti][bottomLeftj] + vPrefixBlue[commoni][commonj];

			img.setPixel(i, j, 2, sumB / howManyPixels);
		}
	}
}

// CropImageFilter(11)
void cropImage(Image& img)
{
	system("cls");

	int x, y, width, height;

	cout << "Enter x: ";
	cin >> x;

	cout << "Enter y: ";
	cin >> y;

	cout << "Enter width: ";
	cin >> width;

	cout << "Enter height: ";
	cin >> height;

	Image cropped(width, height);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			cropped(i, j, 0) = img(x + i, y + j, 0);
			cropped(i, j, 1) = img(x + i, y + j, 1);
			cropped(i, j, 2) = img(x + i, y + j, 2);
		}
	}

	img = cropped;
}

//Filter(13)
void sunlight(Image& img)
{
	system("cls");

	for (int i = 0; i < img.width; i++)
	{
		for (int j = 0; j < img.height; j++)
		{
			int red = img(i, j, 0);
			int green = img(i, j, 1);
			int blue = img(i, j, 2);

			red = red + 50;
			green = green + 30;
			blue = blue + 10;

			if (red > 255)
				red = 255;

			if (green > 255)
				green = 255;

			if (blue > 255)
				blue = 255;

			img(i, j, 0) = red;
			img(i, j, 1) = green;
			img(i, j, 2) = blue;
		}
	}
}

//filter (14)
void TVScanlinesEffect(Image& img)
{
	for (int i = 0; i < img.height; i++) {
		if (i % 10 == 0) {
			for (int j = 0; j < img.width; j++) {
				for (int k = 0; k < 3; k++) {

					img.setPixel(j, i, k,img.getPixel(j,i,k)*.1);

				}
			}
		}
    }
}


//Merge Images (Filter 9)
void MergeImages(Image& image1, Image& image2) 
{
	system("cls");

	int minWidth = std::min(image1.width, image2.width);
	int minHeight = std::min(image1.height, image2.height);

	for (int i = 0; i < minWidth; ++i) {
		for (int j = 0; j < minHeight; ++j) {
			for (int k = 0; k < image1.channels; ++k) {
				image1(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
			}
		}
	}
}

void applyInfraredFilter(Image& img)
{
	system("cls");

	int width = img.width, height = img.height;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int c = 0; c < 3; c++)
			{
				if (c == 0) img.setPixel(i, j, c, 255);
				else
				{
					short oldChannel = img.getPixel(i, j, c);
					img.setPixel(i, j, c, 255 - oldChannel);
				}
			}
		}
	}
}

void startProgram() 
{
	Image OriginalImage = loadImagefromUser();

	printFiltersMenu();

	int userChoice = enFiltersChoice(readFilterChoice());

	bool addAnotherFilter = true;
	
	while (addAnotherFilter)
	{
		switch (userChoice)
		{
		case GrayScale :
			applyGrayscale(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case BlackAndWhite:
			blackAndWhiteFilter(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case Invert:
			invertImage(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case AddFrame:
			AddFrameFilter(OriginalImage);
			backToFiltersMenu();
			break;
		case Flip:
			flipImage(OriginalImage);
		    saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case Rotate:
			rotateImage(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case DarkenAndLighten:
			darkenAndLightenImage(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case Resize:
			resizeFilter(OriginalImage);
			backToFiltersMenu();
			break;
		case Merge:
		{
			system("cls");

			string secondFileName;
			cout << "Enter second image filename: ";
			cin >> secondFileName;
			Image secondImage(secondFileName);
			MergeImages(OriginalImage, secondImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		}
		case DetectEdge:
			detectEdges(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case Crop:
			cropImage(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case Blur:
			applyOptimizedBlur(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case AddSunlight:
			sunlight(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case TvStudioEffect:

			break;
		case PurpleFilter:

			break;
		case InfraredFilter:
			applyInfraredFilter(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case eExit:
			printCredits();
			addAnotherFilter = false;
			break;
		}

		if (addAnotherFilter)
		{
			userChoice = enFiltersChoice(readFilterChoice());

			if (userChoice == eExit)
			{
				printCredits();
				break;
			}

			system("cls");
			OriginalImage = loadImagefromUser();
		}
	}
}

int main()
{
	startProgram();
}

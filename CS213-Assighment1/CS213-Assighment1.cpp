#include <iostream>
#include "Image_Class.h"
#include <algorithm>

using namespace std;

void printFiltersMenu()
{
	cout << "\n=============================================\n";
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
	cout << "\n=============================================\n";
}

short readFilterChoice()
{
	short filterChoice;

	cout << "\nEnter your choice...?\n";
	cin >> filterChoice;

	while (filterChoice < 1 || filterChoice > 8)
	{
		cout << "\nEnter your choice \"It must be from 1 to 8\"...?\n";
		cin >> filterChoice;
	}

	return filterChoice;
}

//A part of add frame to a picture filter
void AddSimpleFrame(string imgName)
{
	system("cls");

	Image img(imgName);

	int width = img.width , height = img.height;
	int minDim = min(width, height);
	int thickness = minDim * 0.03;

	for (int i = 0; i < width ; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i >= width - thickness || i < thickness
				|| j < thickness || j >= height - thickness)
			{
				img.setPixel(i, j, 0, 20);
				img.setPixel(i, j, 1, 30);
				img.setPixel(i, j, 2, 70);
			}
		}
	}

	cout << "Pls enter image name to store new image\n";
	cout << "and specify extension .jpg, .bmp, .png, .tga: ";

	cin >> imgName;
	img.saveImage(imgName);
}

//A part of add frame to a picture filter
void AddFancyFrame(string imgName)
{
	system("cls");

	Image img(imgName);

	int width = img.width, height = img.height;
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
				img.setPixel(i, j, 0, 20);
				img.setPixel(i, j, 1, 30);
				img.setPixel(i, j, 2, 70);
			}

			if (isCorner)
			{
				img.setPixel(i, j, 0, 230);
				img.setPixel(i, j, 1, 190);
				img.setPixel(i, j, 2, 70);
			}

			if (leftLine || rightLine || topLine || bottomLine)
			{
				img.setPixel(i, j, 0, 200);
				img.setPixel(i, j, 1, 160);
				img.setPixel(i, j, 2, 50);
			}
		}
	}

	cout << "Pls enter image name to store new image\n";
	cout << "and specify extension .jpg, .bmp, .png, .tga: ";

	cin >> imgName;
	img.saveImage(imgName);
}

// Add frame to a picture (Filter 4)
void AddFrameFilter() 
{
	system("cls");

	string imgName = "";
	int frameChoice;

	cout << "\nWhat frame do you prefer?\n";
	cout << "\n[1] Simple Frame\n";
	cout << "\n[2] Fancy Frame\n\n";
	cout << "Enter your choice...?\n";

	cin >> frameChoice;

	while (frameChoice < 1 || frameChoice > 2)
	{
		cout << "Enter your choice 1 or 2?\n";
		cin >> frameChoice;
	}

	cout << "\nEnter image name to add the frame\n";
	cin >> imgName;

	if (frameChoice == 1)
	{
		AddSimpleFrame(imgName);
	}
	else
	{
		AddFancyFrame(imgName);
	}

}

// A part of Resize function
void PerformTheResize(string imgName , int resizeChoice)
{
	system("cls");

	int ResizedWidth = 0, ResizedHeigth = 0 , ratio;
	float percOfI , PercOfJ;

	Image OriginalImage(imgName);

	if (resizeChoice == 1)
	{
		cout << "\nPlease, enter the width..?\n";
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
		cout << "\nPlease, enter the ratio..?\n";
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

	cout << "\nPls enter image name to store new image\n";
	cout << "and specify extension .jpg, .bmp, .png, .tga: ";

	cin >> imgName;
	ResizedsImage.saveImage(imgName);
}

// Resize picture dimensions (Filter 8)
void resizeFilter()
{
	system("cls");

	string imgName = "";
	int resizeChoice;

	cout << "\nWhat method do you prefer to use?\n";
	cout << "\n[1] Resize using Dimensions\n";
	cout << "\n[2] Resize using Ratio\n\n";
	cout << "Enter your choice...?\n";

	cin >> resizeChoice;

	while (resizeChoice < 1 || resizeChoice > 2)
	{
		cout << "Enter your choice 1 or 2?\n";
		cin >> resizeChoice;
	}

	cout << "\nEnter image name to resize\n";
	cin >> imgName;

	PerformTheResize(imgName, resizeChoice);

}

int main()
{
	resizeFilter();
}

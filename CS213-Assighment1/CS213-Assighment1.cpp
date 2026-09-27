#include <iostream>
#include "Image_Class.h"
#include <algorithm>

using namespace std;

//All filter choices
enum enFiltersChoice {gray =1 , blAwh , Invert , Frame , Flip , Rotate , DarALig , Resize , eExit};

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
	cout << "[9] Exit Program\n";
	cout << "\n=============================================\n";
}

short readFilterChoice()
{
	short filterChoice;

	cout << "\nEnter your choice...?\n";
	cin >> filterChoice;

	while (filterChoice < 1 || filterChoice > 9)
	{
		cout << "\nEnter your choice \"It must be from 1 to 9\"...?\n";
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

	saveImageByUserName(ResizedsImage);
}

// Resize picture dimensions (Filter 8)
void resizeFilter(Image& OriginalImage)
{
	system("cls");

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

	PerformTheResize(OriginalImage, resizeChoice);

}

// Black and white filter(2)
struct Pixel {
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
		case gray :
			applyGrayscale(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case blAwh:
			blackAndWhiteFilter(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case Invert:

			break;
		case Frame:
			AddFrameFilter(OriginalImage);
			backToFiltersMenu();
			break;
		case Flip:

			break;
		case Rotate:
			rotateImage(OriginalImage);
			saveImageByUserName(OriginalImage);
			backToFiltersMenu();
			break;
		case DarALig:

			break;
		case Resize:
			resizeFilter(OriginalImage);
			backToFiltersMenu();
			break;
		case eExit:
			system("cls");
			addAnotherFilter = false;
			break;
		}

		if (addAnotherFilter)
		{
			userChoice = enFiltersChoice(readFilterChoice());

			if (userChoice == eExit)
			{
				system("cls");
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



















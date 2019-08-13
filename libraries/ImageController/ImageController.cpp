/*****************
ImageController.cpp
******************/

#include"ImageController.h"
#include"Arduino.h"


ImageController::ImageController()
{
}

ImageController::~ImageController()
{
}


void ImageController::wrapPosition()
{
	if (x + IMAGE_CONTROLLER_WINDOW_WIDTH >= IMAGE_CONTROLLER_WIDTH)
	{
		x = IMAGE_CONTROLLER_WIDTH - IMAGE_CONTROLLER_WINDOW_WIDTH - 1;
	}
	else if (x < 0)
	{
		x = 0;
	}

	if (y + IMAGE_CONTROLLER_WINDOW_HEIGHT >= IMAGE_CONTROLLER_HEIGHT)
	{
		y = IMAGE_CONTROLLER_HEIGHT - IMAGE_CONTROLLER_WINDOW_HEIGHT - 1;
	}
	else if (y < 0)
	{
		y = 0;
	}
}

void ImageController::setPosition(int newX, int newY)
{
	x = newX;
	y = newY;

	wrapPosition();
}

void ImageController::movePosition(int deltaX, int deltaY)
{
	x += deltaX;
	y += deltaY;

	wrapPosition();
}

void ImageController::centerPosition()
{
	x = (IMAGE_CONTROLLER_WIDTH - IMAGE_CONTROLLER_WINDOW_WIDTH) / 2;
	y = (IMAGE_CONTROLLER_HEIGHT - IMAGE_CONTROLLER_WINDOW_HEIGHT) / 2;
}

void ImageController::resetPosition()
{
	x = 0;
	y = 0;
}

int ImageController::getPositionX()
{
	return x;
}

int ImageController::getPositionY()
{
	return y;
}



void ImageController::print()
{
	for (int i = 0; i < IMAGE_CONTROLLER_HEIGHT; i++)
	{
		for (int j = 0; j < IMAGE_CONTROLLER_WIDTH; j++)
		{
			IMAGE_CONTROLLER_SERIAL.print(image[i][j] ? "1 " : "0 ");
		}
		IMAGE_CONTROLLER_SERIAL.println();
	}
}

void ImageController::printWindow()
{
	for (int i = y; i < y + IMAGE_CONTROLLER_WINDOW_HEIGHT; i++)
	{
		for (int j = x; j < x + IMAGE_CONTROLLER_WINDOW_WIDTH; j++)
		{
			IMAGE_CONTROLLER_SERIAL.print(image[i][j] ? "1 " : "0 ");
		}
		IMAGE_CONTROLLER_SERIAL.println();
	}
}


void ImageController::draw(byte buffer[(IMAGE_CONTROLLER_WINDOW_WIDTH / 8) * IMAGE_CONTROLLER_WINDOW_HEIGHT])
{
	memset(&buffer[0], 0, (IMAGE_CONTROLLER_WINDOW_WIDTH / 8) * IMAGE_CONTROLLER_WINDOW_HEIGHT);

	int pos = 0;
	for (int i = y; i < y + IMAGE_CONTROLLER_WINDOW_HEIGHT; i++)
	{
		for (int j = x; j < x + IMAGE_CONTROLLER_WINDOW_WIDTH; j++)
		{
			buffer[pos / 8] = (buffer[pos / 8] | (image[i][j] << (7 - (pos % 8))));
			pos++;
		}
	}
}


void ImageController::loadSample(ImageSampleType imageSample)
{
	switch (imageSample)
	{
		case Empty:
			for (int i = 0; i < IMAGE_CONTROLLER_HEIGHT; i++)
			{
				for (int j = 0; j < IMAGE_CONTROLLER_WIDTH; j++)
				{
					image[i][j] = 0;
				}
			}
			break;
		case Full:
			for (int i = 0; i < IMAGE_CONTROLLER_HEIGHT; i++)
			{
				for (int j = 0; j < IMAGE_CONTROLLER_WIDTH; j++)
				{
					image[i][j] = 1;
				}
			}
			break;
		case Calibration:
			for (int i = 0; i < IMAGE_CONTROLLER_HEIGHT; i++)
			{
				for (int j = 0; j < IMAGE_CONTROLLER_WIDTH; j++)
				{
					image[i][j] = 0;
				}
			}
			image[0][0] = 1;
			image[1][0] = 1;
			image[0][2] = 1;
			break;
		case Dot:
			for (int i = 0; i < IMAGE_CONTROLLER_HEIGHT; i++)
			{
				for (int j = 0; j < IMAGE_CONTROLLER_WIDTH; j++)
				{
					image[i][j] = 0;
				}
			}
			image[IMAGE_CONTROLLER_HEIGHT/2-1][IMAGE_CONTROLLER_WIDTH/2-1] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-1][IMAGE_CONTROLLER_WIDTH/2] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2][IMAGE_CONTROLLER_WIDTH/2-1] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2][IMAGE_CONTROLLER_WIDTH/2] = 1;
			break;
		case Smiley:
			for (int i = 0; i < IMAGE_CONTROLLER_HEIGHT; i++)
			{
				for (int j = 0; j < IMAGE_CONTROLLER_WIDTH; j++)
				{
					image[i][j] = 0;
				}
			}
			image[IMAGE_CONTROLLER_HEIGHT/2+2][IMAGE_CONTROLLER_WIDTH/2-3] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2+2][IMAGE_CONTROLLER_WIDTH/2-2] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2+3][IMAGE_CONTROLLER_WIDTH/2-3] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2+3][IMAGE_CONTROLLER_WIDTH/2-2] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2+2][IMAGE_CONTROLLER_WIDTH/2+1] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2+2][IMAGE_CONTROLLER_WIDTH/2+2] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2+3][IMAGE_CONTROLLER_WIDTH/2+1] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2+3][IMAGE_CONTROLLER_WIDTH/2+2] = 1;

			image[IMAGE_CONTROLLER_HEIGHT/2-4][IMAGE_CONTROLLER_WIDTH/2-3] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-4][IMAGE_CONTROLLER_WIDTH/2-2] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-3][IMAGE_CONTROLLER_WIDTH/2-3] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-3][IMAGE_CONTROLLER_WIDTH/2-2] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-4][IMAGE_CONTROLLER_WIDTH/2-1] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-4][IMAGE_CONTROLLER_WIDTH/2-0] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-3][IMAGE_CONTROLLER_WIDTH/2-1] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-3][IMAGE_CONTROLLER_WIDTH/2-0] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-4][IMAGE_CONTROLLER_WIDTH/2+1] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-4][IMAGE_CONTROLLER_WIDTH/2+2] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-3][IMAGE_CONTROLLER_WIDTH/2+1] = 1;
			image[IMAGE_CONTROLLER_HEIGHT/2-3][IMAGE_CONTROLLER_WIDTH/2+2] = 1;
			break;
	}
}

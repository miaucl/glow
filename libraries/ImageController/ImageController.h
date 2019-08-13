/*******************
ImageController.h
*******************/

#ifndef _IMAGE_CONTROLLER_H__
#define _IMAGE_CONTROLLER_H__

#include "Arduino.h"

#define IMAGE_CONTROLLER_WIDTH 64
#define IMAGE_CONTROLLER_HEIGHT 64
#define IMAGE_CONTROLLER_WINDOW_WIDTH 16
#define IMAGE_CONTROLLER_WINDOW_HEIGHT 16

#define IMAGE_CONTROLLER_SERIAL Serial

enum ImageSampleType
{
  Empty,
  Full,
  Calibration,
  Dot,
  Smiley
};


class ImageController
{
  private:
    boolean image[IMAGE_CONTROLLER_WIDTH][IMAGE_CONTROLLER_HEIGHT] = {{0}};
    int x = 0;
    int y = 0;
    void wrapPosition();

  public:
    ImageController();
    ~ImageController();

    void loadSample(ImageSampleType imageSample);

    void setPosition(int newX, int newY);
    void movePosition(int deltaX, int deltaY);
    void centerPosition();
    void resetPosition();
    int getPositionX();
    int getPositionY();

    void draw(byte buffer[(IMAGE_CONTROLLER_WINDOW_WIDTH / 8) * IMAGE_CONTROLLER_WINDOW_HEIGHT]);

    void print();
    void printWindow();

};


#endif

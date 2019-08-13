/*
   Glow a dynamic pattern

   2019 C. Lippuner

   cy.li@gmx.ch

*/

#include <MdLep16X16.h>
#include <ImageController.h>

#define MIN_REFRESH_DELAY 70

MdLep16X16 mdLep(0xFF, 0xFF, 0xFF, 0xFF);
ImageController imageController;
byte window[32] = {0};

void setup()
{
  Serial.begin(9600);
  
  imageController.loadSample(Smiley);
  Serial.println(F("reset:"));
  imageController.centerPosition();
  imageController.draw(window);

  mdLep.init();
  mdLep.loadScreen(window);
  delay(100);
}

void loop()
{

  while (Serial.available())
  {
    char key = Serial.read();

    switch (key)
    {
      case 'w': imageController.movePosition(0, 1); break;
      case 's': imageController.movePosition(0, -1); break;
      case 'a': imageController.movePosition(1, 0); break;
      case 'd': imageController.movePosition(-1, 0); break;
    }

    imageController.draw(window);
  }

  mdLep.loadScreen(window);
  delay(MIN_REFRESH_DELAY);
}

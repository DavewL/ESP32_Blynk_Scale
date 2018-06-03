#include <HX711_ADC.h>

/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  Note: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ba4bb0437daa423db7a93b2961141b9c";

HX711_ADC LoadCell(4, 5);
long t;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Pilate2";
char pass[] = "asdfghjklqwer";

float i;

void setup()
{
  // Debug console
  Serial.begin(9600);
  
  LoadCell.begin();
  LoadCell.setCalFactor(4500.0); // user set calibration factor (float)

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  
  LoadCell.update();
  
  if (millis() > t + 250) {
    i = LoadCell.getData() - 1867.15;
    //Serial.print("Load_cell output val: ");
    //Serial.println(i);
    t = millis();
  }
}

BLYNK_READ(V0) //Blynk app has something on V0
{
  Blynk.virtualWrite(V0, i); //sending to Blynk
}

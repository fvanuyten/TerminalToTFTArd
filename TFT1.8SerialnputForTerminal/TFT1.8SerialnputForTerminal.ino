/*
This program is not perfect but it works for me, just 
want to share it and if you like it or have some problems
e-mail me ad fvanuyten@gmail.com
 

*/
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

String OutString = "";
boolean stringComplete = false;// whether the string is complete
int xas=120;
int tell = 0;
int tell2= 0;
// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

// pin definition for the Leonardo
// #define cs   7
// #define dc   0
// #define rst  1

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

// char array to print to the screen


void setup() {

  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  // set the font size
  TFTscreen.setTextSize(2);
  // write the text to the top left corner of the screen
  TFTscreen.text("   TERMINAL    ", 0, 10);
  TFTscreen.setTextSize(1.5);
  TFTscreen.textWrap(" Use 1 line of command and short outputs ", 0, 40);
  TFTscreen.text(" Made by Francis van Uyten   ", 0, 60);
  // ste the font size very large for the loop
  TFTscreen.setTextSize(5);
  Serial.begin(9600);
  
}

void loop() {
  
 
  if(Serial.available()) {

    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    OutString += inChar;
    tell2++;
    
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
   if(inChar =='\clr'){ TFTscreen.background(0, 0, 0); TFTscreen.stroke(255, 255, 255);}
   if ( inChar == '\n' || tell2 == 26) {
      stringComplete = true;
      tell2 = 0;
      //delay(1000);
    }
   
   if (stringComplete == true){
           tell++;
           
           TFTscreen.background(0, 0, 0);
          
          // set the font color to white
          TFTscreen.stroke(255, 255, 255);
          
          
          TFTscreen.setTextSize(1);
          
          //Sending string to TFT////////
          char charBuf[OutString.length()];
           
          OutString.toCharArray(charBuf,OutString.length());
          if(tell == 2 ){
              xas -= 16; tell=0;
          }
          TFTscreen.textWrap(charBuf, 0,xas );
          
          stringComplete = false;
          Serial.println(xas);
          if(xas <-300){
              xas = 120;
              OutString = "";
              TFTscreen.textWrap("Buffer is clear", 0,xas ); 
            }
        }
     }

}




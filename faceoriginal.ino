#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NUMPIXELS 49 
#define EYEPIXELS 7 


Adafruit_NeoPixel pixels (NUMPIXELS, 1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel eye (EYEPIXELS, 6, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

int analogPin = A3;
int i = 0; 

void setup() {

  pixels.begin();
  eye.begin ();
}

void loop() {
  pixels.clear(); 
  eye.clear();
  
 for(int i=1; i<5; i++) { // For each expression...

  if (i==1){
/////////////////////////////sad//////////////////////////////

   eye.setPixelColor(3, eye.Color(128, 0,128));

   
   pixels.setPixelColor(45, pixels.Color(128, 0,128));
 


   
   pixels.setPixelColor(9, pixels.Color(128, 0,128));
   pixels.setPixelColor(16, pixels.Color(128, 0, 128));
   pixels.setPixelColor(18, pixels.Color(128, 0, 128));
   pixels.setPixelColor(24, pixels.Color(128, 0, 128));
   pixels.setPixelColor(27, pixels.Color(128, 0, 128));
   pixels.setPixelColor(32, pixels.Color(128, 0, 128));
   pixels.setPixelColor(36, pixels.Color(128, 0, 128));
   pixels.setPixelColor(40, pixels.Color(128, 0, 128));
                      ////
   pixels.setPixelColor(37, pixels.Color(128, 0, 128));
   pixels.setPixelColor(38, pixels.Color(128, 0, 128));
   pixels.setPixelColor(39, pixels.Color(128, 0, 128));
  }
  else if (i==5){
///////////////////////////////very sad//////////////////////////////


     eye.setPixelColor(5, eye.Color(128, 0,128));
     eye.setPixelColor(6, eye.Color(128, 0,128));
     eye.setPixelColor(7, eye.Color(128, 0,128));
     
   pixels.setPixelColor(47, pixels.Color(128, 0,128));
   pixels.setPixelColor(48, pixels.Color(128, 0,128));
   pixels.setPixelColor(49, pixels.Color(128, 0,128));


   pixels.setPixelColor(9, pixels.Color(255, 255, 255));
   pixels.setPixelColor(10, pixels.Color(255, 255, 255));
   pixels.setPixelColor(11, pixels.Color(255, 255, 255));
   pixels.setPixelColor(12, pixels.Color(255, 255, 255));
   pixels.setPixelColor(13, pixels.Color(255, 255, 255));
   pixels.setPixelColor(14, pixels.Color(255, 255, 255));
   pixels.setPixelColor(15, pixels.Color(255, 255, 255));
   pixels.setPixelColor(16, pixels.Color(255, 255, 255));
                    //////
   pixels.setPixelColor(18, pixels.Color(255, 255, 255));
   pixels.setPixelColor(24, pixels.Color(255, 255, 255));
   pixels.setPixelColor(27, pixels.Color(255, 255, 255));
   pixels.setPixelColor(32, pixels.Color(255, 255, 255));
   pixels.setPixelColor(36, pixels.Color(255, 255, 255));
   pixels.setPixelColor(40, pixels.Color(255, 255, 255));
                      ////
   pixels.setPixelColor(37, pixels.Color(255, 255, 255));
   pixels.setPixelColor(38, pixels.Color(255, 255, 255));
   pixels.setPixelColor(39, pixels.Color(255, 255, 255));
    }
    else if (i==3){
/////////////////////////////smile//////////////////////////////
  
   pixels.setPixelColor(46, pixels.Color(128, 0,128));
 
   eye.setPixelColor(4, eye.Color(128, 0,128));
     
   pixels.setPixelColor(11, pixels.Color(0, 0, 255));
   pixels.setPixelColor(12, pixels.Color(0, 0, 255));
   pixels.setPixelColor(13, pixels.Color(0, 0, 255));
   pixels.setPixelColor(14, pixels.Color(0, 0, 255));
   pixels.setPixelColor(19, pixels.Color(0, 0, 255));
   pixels.setPixelColor(23, pixels.Color(0, 0, 255));
   pixels.setPixelColor(27, pixels.Color(0, 0, 255));
   pixels.setPixelColor(32, pixels.Color(0, 0, 255));
   pixels.setPixelColor(35, pixels.Color(0, 0, 255));
   pixels.setPixelColor(41, pixels.Color(0, 0, 255));

  }
      else if (i==4){
/////////////////////////////ANGRY//////////////////////////////

   pixels.setPixelColor(43, pixels.Color(128, 0,128)); 
   pixels.setPixelColor(49, pixels.Color(128, 0,128));
   eye.setPixelColor(1, eye.Color(128, 0,128));
   eye.setPixelColor(7, eye.Color(128, 0,128));  

   pixels.setPixelColor(35, pixels.Color(255,0,0));
   pixels.setPixelColor(32, pixels.Color(255,0,0));
   pixels.setPixelColor(19, pixels.Color(255,0,0));
   
   pixels.setPixelColor(31, pixels.Color(255,0,0));
   pixels.setPixelColor(37, pixels.Color(255,0,0));
   pixels.setPixelColor(30, pixels.Color(255,0,0));
   pixels.setPixelColor(21, pixels.Color(255,0,0));
   pixels.setPixelColor(29, pixels.Color(255,0,0));
   pixels.setPixelColor(39, pixels.Color(255,0,0));
      
   pixels.setPixelColor(28, pixels.Color(255,0,0));
   pixels.setPixelColor(23, pixels.Color(255,0,0));
   pixels.setPixelColor(27, pixels.Color(255,0,0));
   pixels.setPixelColor(41, pixels.Color(255,0,0));

   

  }
  else if (i==2){
/////////////////////////////SHOOK//////////////////////////////
   pixels.setPixelColor(43, pixels.Color(128, 0,128));
   pixels.setPixelColor(44, pixels.Color(128, 0,128));
   pixels.setPixelColor(45, pixels.Color(128, 0,128));
   pixels.setPixelColor(46, pixels.Color(128, 0,128));
   pixels.setPixelColor(47, pixels.Color(128, 0,128));
   pixels.setPixelColor(48, pixels.Color(128, 0,128));

   eye.setPixelColor(1, eye.Color(128, 0,128));
   eye.setPixelColor(2, eye.Color(128, 0,128));
   eye.setPixelColor(3, eye.Color(128, 0,128));
   eye.setPixelColor(4, eye.Color(128, 0,128));
   eye.setPixelColor(5, eye.Color(128, 0,128));
   eye.setPixelColor(6, eye.Color(128, 0,128));

   pixels.setPixelColor(3, pixels.Color(255, 255, 255));
   pixels.setPixelColor(4, pixels.Color(255, 255, 255));
   pixels.setPixelColor(5, pixels.Color(255, 255, 255));

   pixels.setPixelColor(14, pixels.Color(255,255,255));
   pixels.setPixelColor(11, pixels.Color(255,255,0255));
   pixels.setPixelColor(19, pixels.Color(255,255,255));
   pixels.setPixelColor(23, pixels.Color(255,255,255));
   pixels.setPixelColor(31, pixels.Color(255,255,255));
   pixels.setPixelColor(28, pixels.Color(255,255,255));
                  ////
   pixels.setPixelColor(37, pixels.Color(255,255,255));
   pixels.setPixelColor(38, pixels.Color(255,255,255));
   pixels.setPixelColor(39, pixels.Color(255,255,255));
 
  }

    
    pixels.show(); // Send the updated pixel colors to the hardware.
    eye.show();
    delay(10000);
    pixels.clear();
    eye.clear();

 }
    
// Pause before next pass through loop
  }

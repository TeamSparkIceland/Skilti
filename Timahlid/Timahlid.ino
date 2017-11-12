#include "Adafruit_HT1632.h"


#define HT_DATA 2
#define HT_WR   3
#define HT_CS   4
#define HT_CS2  5

// Fastar
#define letter_with 12

// 2 tilvik skilgreind til að geta stýrt 7 panelum
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS, HT_CS2, 6, 7);
Adafruit_HT1632LEDMatrix matrix2 = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, 8,9,10);


// Breitur skilgreindar
char function = '0';
int index;
int laser = 2;
double t1;
double t2;
double timamunur;
double laptime[5];




void setup() {
  Serial.begin(9600);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  matrix2.begin(ADA_HT1632_COMMON_16NMOS);

  // Config text
  matrix.setTextSize(2);
  matrix2.setTextSize(2);
    /*
  matrix.fillScreen();
  matrix2.fillScreen();
  delay(1000);
  */
  matrix.clearScreen();
  matrix2.clearScreen();
  matrix.setTextWrap(false);
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  //acceleration();
  endurance();
}

void lasertest(){
  matrix.clearScreen();
  matrix.setCursor(0,0);
  matrix.print(digitalRead(laser));
  matrix.writeScreen();
  }

void endurance(){
  matrix.clearScreen();
  matrix.setCursor(0, 0);
  matrix.print("ok");
  matrix.writeScreen();
  while(digitalRead(A1)==1);
  while(digitalRead(A0)==0);
  t1 = millis();
  
  for(int i = 1; i <= 5; i++) {
   while(digitalRead(A0)==0);
   
   laptime[i] = millis();
   
   matrix.clearScreen();
   matrix.setCursor(0, 0);
   matrix.print(laptime[i]/1000);
   matrix.writeScreen();
   delay(2000);
   }
   
  matrix.clearScreen();
  matrix.setCursor(0, 0);
  matrix.print("end");
  matrix.writeScreen(); 
  delay(2000); 
}

void acceleration(){
  matrix.clearScreen();
  matrix.setCursor(0, 0);
  matrix.print("ok");
  matrix.writeScreen();
  while(digitalRead(A2)==1){}
  
  t1 = millis();
  //Serial.println("Timataka hafin");
  
  matrix.clearScreen();
  matrix.setCursor(0, 0);
  matrix.print("start");
  matrix.writeScreen();
   
  while(digitalRead(A0)==0) {
    matrix.clearScreen();
    matrix.setCursor(0, 0);
    matrix.print((millis()-t1)/1000);
    matrix.writeScreen();
    delay(10);
    }
  t2 = millis();
  timamunur = (t2-t1)/1000;
//  Serial.print(timamunur);
//  Serial.println(" s");
     
  matrix.clearScreen();
  matrix.setCursor(0, 0);
  matrix.print(timamunur);
  matrix.writeScreen();
  while(digitalRead(A2)==0){}
}

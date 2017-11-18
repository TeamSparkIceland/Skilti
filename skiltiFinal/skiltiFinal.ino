#include "Adafruit_HT1632.h"


#define HT_DATA 11
#define HT_WR   13
#define HT_CS   4
#define HT_CS2  5
#define HT_CS3  6
#define HT_CS4  7
#define HT_CS5  8
#define HT_CS6  9
#define HT_CS7  3
// Fastar
#define letter_width 12
#define takki A0
#define laser A1
#define rofi1 A2
#define rofi2 A3

// 2 tilvik skilgreind til að geta stýrt 7 panelum
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS, HT_CS2, HT_CS3, HT_CS4);
Adafruit_HT1632LEDMatrix matrix2 = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS5, HT_CS6, HT_CS7);

double t1;
double t2;
double timi;
double timamunur;
int sec;
int prevsec;
int min;
int prevmin;
int ms;
int x;

void setup() {
  // put your setup code here, to run once:
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
  pinMode(laser, INPUT);
  pinMode(takki, INPUT);
  x = 2;
}

void loop() {
  if (digitalRead(rofi1) == 1) {
    if (digitalRead(A3) == 1) {
      if (x != 1) {
        matrix2.clearScreen();
        matrix.clearScreen();
        matrix.setCursor(0, 1);
        matrix.print("Enduranc");
        matrix.writeScreen();
        matrix2.setCursor(0, 1);
        matrix2.print("e");
        matrix2.writeScreen();
      }
      if (digitalRead(takki) == 0) {
        endurance();
        x = 3;
      }
      else {
        x = 1;
      }
    }
    else {
      if ( x != 0) {
        matrix2.clearScreen();
        matrix.clearScreen();
        matrix.setCursor(0, 1);
        matrix.print("Accelera");
        matrix.writeScreen();
        matrix2.setCursor(0, 1);
        matrix2.print("tion");
        matrix2.writeScreen();
      }
      if (digitalRead(takki) == 0) {
        acceleration();
        x = 3;
      }
      else {
        x = 0;
      }
    }
  }
}

void endurance() {
  //  matrix2.clearScreen();
  //  matrix.clearScreen();
  //  matrix.setCursor(0, 1);
  //  matrix.print("Enduranc");
  //  matrix.writeScreen();
  //  matrix2.setCursor(0, 1);
  //  matrix2.print("e");
  //  matrix2.writeScreen();

  int numberOfLaps = 5;
  double laptime[numberOfLaps];
  matrix2.clearScreen();
  matrix.clearScreen();
  matrix.setCursor(0, 1);
  matrix.print("Ready!");
  matrix.writeScreen();

  while (digitalRead(laser) == 0); //byrjar tímatöku þegar laser er fyrst rofinn

  t1 = millis();              //upphafstími
  matrix.clearScreen();
  matrix.setCursor(0, 1);
  matrix.print("Lap 1:");
  matrix.writeScreen();

  prevsec = -1;
  prevmin = 0;
  while (millis() - t1 < 10000) {
    timePrint();
    delay(10);
  }

  for (int i = 0; i < numberOfLaps; i++) {
    matrix.clearPanel(2);
    matrix.setCursor(4 * letter_width, 1);
    matrix.print(i + 1);
    matrix.print(":");
    matrix.writeScreen();
    while (digitalRead(laser) == 0) { //sýnir rauntímann þangað til laser er rofinn
      timePrint();
      delay(10);
    }
    if (i == 1) {
      laptime[i] = millis() - t1; //skráir fyrsta laptime
    }
    else {
      laptime[i] = millis() - laptime[i - 1]; //skráir seinni laptimes
    }
    matrix2.clearScreen();
    matrix2.setCursor(0,1);
    matrix2.print(laptime[i]/1000);
    matrix2.writeScreen();

    delay(2000);
  }
}

void acceleration() {
  // Acceleration run ready!
  //  matrix2.clearScreen();
  //  matrix.clearScreen();
  //  matrix.setCursor(0, 1);
  //  matrix.print("Accelera");
  //  matrix.writeScreen();
  //  matrix2.setCursor(0, 1);
  //  matrix2.print("tion");
  //  matrix2.writeScreen();
  //  while (digitalRead(takki) == 1);


  matrix.clearScreen();
  matrix2.clearScreen();
  matrix.setCursor(0, 1);
  matrix.print("Ready!");
  matrix.writeScreen();


  delay(2000);
  while (digitalRead(takki) == 1); //bíður eftir að tímataka hefjist
  // Countdown: 3-2-1-
  // Go!
  matrix.clearScreen();
  matrix.setCursor(0, 1);
  matrix.print("Countdow");
  matrix.writeScreen();

  matrix2.setCursor(0, 1);
  matrix2.print("n:");
  matrix2.writeScreen();

  for (int i = 3; i > 0; i--) {
    matrix2.setCursor(letter_width * 2, 1);
    matrix2.clearPanel(1);
    matrix2.print(i);
    matrix2.writeScreen();
    delay(1000);
  }

  matrix.clearScreen();
  matrix2.clearScreen();

  //  matrix.setCursor(0, 1);
  //  matrix.print("Go!");
  //  matrix.writeScreen();

  t1 = millis();    //skráir upphafstíma

  //  delay(1000);
  matrix.clearScreen();
  matrix.setCursor(0, 1);
  matrix.print("Time: ");
  matrix.writeScreen();

  prevsec = -1;
  prevmin = 0;

  while (digitalRead(laser) == 0) { //sýnir rauntímann þangað til laser er rofinn
    timePrint();
    delay(10);
  }

  t2 = millis();        //skráir lokatíma
  timamunur = t2 - t1;

  matrix.clearScreen();
  matrix.setCursor(0, 1);
  matrix.print("Finish!");
  matrix.writeScreen();

  //prentar út lokatíma

  while (digitalRead(takki) == 1) {} //bíður eftir að næstu keyrslu
  delay(2000);
}

void timePrint() {
  timi = (millis() - t1) / 1000; // skráir tímann
  min = (int)timi / 60;
  sec = (int) (timi - min * 60);
  ms = (int)((timi - sec - min * 60) * 100);

  if (prevmin != min) { // uppfærir mínútur
    prevmin = min;
    matrix.clearPanel(3);
    if (min >= 10) {
      matrix.setCursor(letter_width * 6, 1);
    }
    else {
      matrix.setCursor(letter_width * 7, 1);
    }
    matrix.print(prevmin);
    matrix.writeScreen();
  }



  if (prevsec != sec) { // uppfærir sekúndur
    prevsec = sec;
    matrix2.clearPanel(1);
    matrix2.clearPanel(0);
    matrix2.setCursor(0, 1);
    if (prevmin > 0) {
      matrix2.print(":");
    }
    if (prevsec >= 10) {
      matrix2.setCursor(letter_width, 1);
      matrix2.print(prevsec);
    }
    else {
      matrix2.setCursor(letter_width, 1);
      matrix2.print(0);
      matrix2.print(prevsec);
    }
    matrix2.print(".");
    matrix2.writeScreen();
  }

  // uppfærir millisekúndur
  matrix2.clearPanel(2);
  matrix2.setCursor(letter_width * 4, 1);
  matrix2.print(ms);
  matrix2.writeScreen();
}




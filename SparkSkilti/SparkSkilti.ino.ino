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
}

void loop() {
  caountdown();
  function = '0';
  
  Serial.println("Selevt mode of operation");
  Serial.println();
  Serial.println("1 - Niðurteljari");
  Serial.println("2 - Skilaboð");
  Serial.println("3 - Tímamælir");
  Serial.println("C - Config");
  Serial.println();
  Serial.print("- ");
  
  do{
    if (Serial.available() > 0){
      function = Serial.read();
      Serial.println(function);
    }
  }while(function == '0');
  delay (100);
  switch(function){
    case '1':
      caountdown();
    break;
    case '2':
      mesage();
    break;
    case '3':
      takeTime();
    break;
    default:
    Serial.println("Ekki var rétt valið");
  }
  
}

// 

void caountdown(int d_nidur, int h_nidur, int m_nidur, int s_nidur){
  while(millis()%1000 !=0);
    s_nidur--;  // Minkar sek. um 1
    matrix2.clearPanel(2); // Hreinsar sekúntur af skjá

    // Endurstillir sek. og minkar min. um 1
    if(s_nidur == -1){    
      s_nidur = 59;
      m_nidur--;
      
      //Hreinsar mínotur af skjá
      matrix2.clearPanel(1);  
      matrix2.clearPanel(0);

      // Endurstillir min. og minkar kls.
      if(m_nidur == -1){
        matrix.clearPanel(3);
        m_nidur = 59;
        h_nidur--;

        // Endurstillir kls. og minkar dag um 1
        if(h_nidur == -1){
          matrix.clearScreen();
          h_nidur = 23;
          d_nidur--;
        }
      }
    }

  // Prentar tíma á skjá
  printTime(d_nidur,h_nidur,m_nidur,s_nidur);
  caountdown();
}

void mesage(){
   matrix.clearScreen();
   matrix.setCursor(0, 0);
   matrix.print("skilaboð");
   matrix.writeScreen();
   while(1);
}

void takeTime(){
   matrix.clearScreen();
   matrix.setCursor(0, 0);
   matrix.print("tima taka");
   matrix.writeScreen();
}
void printTime(int d, int h, int m, int s){

  // Hliðrar degi miðað við tugasæti
  if(d >=100){
    index = 1;
  }else if(d >=10){
    index = 2;
    matrix.setCursor(letter_with,1);
    matrix.print("0");
    matrix.writeScreen();
  }else if(d>=0){
    index = 3;
    matrix.setCursor(letter_with,1);
    matrix.print("00");
    matrix.writeScreen();
  }
  
  // Prentar út daga
  matrix.setCursor(index*letter_with,1);
  matrix.print(d);
  matrix.writeScreen();
  matrix.setCursor(4*letter_with,1);
  matrix.print("d");
  matrix.writeScreen();

  // Hliðrar klukkutíma miðað við tugasæti
  if(h>=10){
    index = 6;
  }else if(h<10){
    index = 7;
    matrix.setCursor(6*letter_with,1);
    matrix.print("0");
    matrix.writeScreen();
  }

  // Prentar út klukkutíma
  matrix.setCursor(index*letter_with,1);
  matrix.print(h);
  matrix.writeScreen();
  matrix2.setCursor(0*letter_with,1);
  matrix2.print(":");
  matrix2.writeScreen();

   if(m>=10){
    index = 1;
  }else if(m<10){
    index = 2;
    matrix2.setCursor((index-1)*letter_with,1);
    matrix2.print("0");
    matrix2.writeScreen();
  }
  matrix2.setCursor(index*letter_with,1);
  matrix2.print(m);
  matrix2.writeScreen();
  matrix2.setCursor(3*letter_with,1);
  matrix2.print(":");
  matrix2.writeScreen();

   if(s>=10){
    index = 4;
  }else if(s<10){
    index = 5;
    matrix2.setCursor((index-1)*letter_with,1);
    matrix2.print("0");
    matrix2.writeScreen();
  }
  
  matrix2.setCursor(index*letter_with,1);
  matrix2.print(s);
  matrix2.writeScreen();
}



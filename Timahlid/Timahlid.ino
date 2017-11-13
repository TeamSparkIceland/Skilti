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
  while(1){
   matrix.clearScreen();
   matrix.setCursor(0,0);
   matrix.print(digitalRead(A0));
   matrix.writeScreen();
  }
  }

void endurance(){
  skiltiPrint("ok", matrix);
  
  while(digitalRead(A1)==1);  //byrjar ekki tímatöku nema rofi sé á
  while(digitalRead(A0)==0);  //byrjar tímatöku þegar laser er fyrst rofinn
  t1 = millis();              //upphafstími
  
  for(int i = 1; i <= 5; i++) {
    while(digitalRead(A0)==0) {    //sýnir rauntímann þangað til laser er rofinn
      skiltiPrint(String((millis()-t1)/1000), matrix);    
      delay(10);
    } 
    if(i==1){
      laptime[i] = millis()-t1;  //skráir fyrsta laptime
    }
    else {
      laptime[i]=millis()-laptime[i-1];  //skráir seinni laptimes
    }
    skiltiPrint(String(laptime[i]/1000), matrix);
    delay(2000);
  }

  skiltiPrint("Mark!",matrix);
  delay(2000);
  skiltiPrint("Tímar:",matrix);
  delay(2000);
  String stringLaptime[5];
  
  for(int i = 1; i<=5; i++) {
    skiltiPrint(String(laptime[i]),matrix);
//    stringLaptime[i] = String(laptime[i]);
//    skiltiPrint("Hringur "+String(i)+": "+stringLaptime[i], matrix);
    delay(2000);
  }
  
  delay(2000); 
}

void acceleration(){
  skiltiPrint("ok", matrix);
  
  while(digitalRead(A2)==1){}  //bíður eftir að tímataka hefjist
  
  t1 = millis();    //skráir upphafstíma  
  while(digitalRead(A0)==0) {    //sýnir rauntímann þangað til laser er rofinn
    skiltiPrint(String((millis()-t1)/1000), matrix);    
    delay(10);
  } 
  t2 = millis();        //skráir lokatíma
  timamunur = (t2-t1)/1000; 
  
  skiltiPrint(String(timamunur), matrix); //prentar út lokatíma
  
  while(digitalRead(A2)==0){}    //bíður eftir að næstu keyrslu
}


// prentar út einföld skilaboð, þyrft að skrifa ný föll föll fyrir mismunandi tilfelli t.d. tími eða texti og blöndu af báðu
// gæti t.d. tekið báða panela og cursor sem input
void skiltiPrint (String str, Adafruit_HT1632LEDMatrix skilti ) { 
  skilti.clearScreen();
  skilti.setCursor(0, 0);
  skilti.print(str);
  skilti.writeScreen();  
}



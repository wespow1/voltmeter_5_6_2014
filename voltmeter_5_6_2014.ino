#include <UTFT.h>
#include <UTouch.h>
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
char stCurrent[20]="";
char stLast[20]="";
UTFT myGLCD(ITDB32S,38,39,40,41);
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0;
float R2 = 10000.0;
int value = 0;
int page = 0;
int stCurrentLen=0;
int x, y;
int sensorValue = 0;

UTouch  myTouch( 6, 5, 4, 3, 2);
void setup() {
 myGLCD.InitLCD(0);
 myGLCD.clrScr();
 myGLCD.setFont(SmallFont);
 myTouch.InitTouch();
 myTouch.setPrecision(PREC_HI);
 Serial.begin(9600);
 Serial.println("Starting...");
 homescr();
 touchread();
}
void homescr(){
 readvoltage();
 myGLCD.setColor(0,0,255);
 myGLCD.drawRect(10,250,100,290);
 myGLCD.fillRect(10,250,100,290);
 myGLCD.setColor(255,255,255);
 myGLCD.print("Menu 1", 25, 265);
 myGLCD.setColor(0,0,255);
 myGLCD.drawRect(130,250,220,290);
 myGLCD.fillRect(130,250,220,290);
 myGLCD.setColor(255,255,255);
 myGLCD.print("INFO", 160, 265);   
}
void redraw(){
 if (page == 0) {
 homescr();
 }
 if (page = 1) {
 menu1();
 }
 if (page == 2) {
 info();
 }
}
void menu1() {  
 myGLCD.print("MENU 1", CENTER, 2);  
 myGLCD.drawRect(0, 20, 150, 50);
 myGLCD.drawRect(170, 20, 150, 50);
 myGLCD.drawRect(0, 80, 150, 50);
 myGLCD.drawRect(170, 80, 150, 50);
 myGLCD.drawRect(0, 140, 150, 50);
 myGLCD.drawRect(170, 140, 150, 50);
 myGLCD.setColor(0,0,255);
 myGLCD.drawRect(10,250,100,290);
 myGLCD.fillRect(10,250,100,290);
 myGLCD.setColor(255,255,255);
 myGLCD.print("button 1", 25, 265);
 myGLCD.setColor(0,0,255);
 myGLCD.drawRect(130,250,220,290);
 myGLCD.fillRect(130,250,220,290);
 myGLCD.setColor(255,255,255);
 myGLCD.print("HOME", 160, 265);
}
void info() {
 myGLCD.print("INFO", CENTER, 2);  
 myGLCD.drawRect(0, 20, 150, 50);
 myGLCD.drawRect(170, 20, 150, 50);
 myGLCD.drawRect(0, 80, 150, 50);
 myGLCD.drawRect(170, 80, 150, 50);
 myGLCD.drawRect(0, 140, 150, 50);
 myGLCD.drawRect(170, 140, 150, 50);
 myGLCD.setColor(0,0,255);
 myGLCD.drawRect(10,250,100,290);
 myGLCD.fillRect(10,250,100,290);
 myGLCD.setColor(255,255,255);
 myGLCD.print("HOME", 35, 265);
 myGLCD.setColor(0,0,255);
 myGLCD.drawRect(130,250,220,290);
 myGLCD.fillRect(130,250,220,290);
 myGLCD.setColor(255,255,255);
 myGLCD.print("button 1", 150, 265);
}  
void readvoltage(void){
  int val1 = 0;
  val1 = analogRead(A1);
  vout = (val1 * 5.0) / 1024.0;
  vin = vout / (R2/(R1+R2));  
  if (vin<0.09) {
      vin=0.0;
  }

  //String sensorVal1 = String(vin);
  //Serial.print(sensorVal1);
  String sensorVal2 = String(analogRead(A2));
  String sensorVal3 = String(analogRead(A3));
  String sensorVal4 = String(analogRead(A4));
  String sensorVal5 = String(analogRead(A5));
  String sensorVal6 = String(analogRead(A6));
  myGLCD.setColor(0, 255, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("DC VOLTMETER", CENTER, 2);
  myGLCD.print("Voltage #1",10,90, 0);
  myGLCD.print(floatToString(vin),200,90, 0);
 /* myGLCD.print("Voltage #2",10,110, 0);
  myGLCD.print(sensorVal2,200,110, 0);
  myGLCD.print("Voltage #3",10,130, 0);
  myGLCD.print(sensorVal3,200,130, 0);
  myGLCD.print("Voltage #4",10,150, 0);
  myGLCD.print(sensorVal4,200,150, 0);
  myGLCD.print("Voltage #5",10,170, 0);
  myGLCD.print(sensorVal5,200,170, 0);
  myGLCD.print("Voltage #6",10,190, 0);
  myGLCD.print(sensorVal6,200,190, 0);*/

  }
 


void loop() {
 Serial.println(page);
 touchread();
 if (page == 0);{
 homescr();
 }
 if (page == 1); {
   
 }
}
void touchread() {
    long x, y;  
    while(myTouch.dataAvailable() == true){
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
 // Serial.print("X: ");
 // Serial.println(x);    
 // Serial.print("Y: ");
 // Serial.println(y);
    if (y > 6 && y < 150 && x > 22 && x < 61) {
    if (page == 0) { 
    myGLCD.clrScr();
    menu1();
    page = 1;
    }
    if (page == 1) {
    //myGLCD.clrScr();
    //menu1();
    }    
    if (page == 2) { 
    myGLCD.clrScr();
    homescr();
    page = 0;
    }
   }
    if (y > 153 && y < 224 && x > 22 && x < 61) {
    if (page == 0) { 
    myGLCD.clrScr();
    info();
    page = 2;  
    }
    if (page == 1) {
    myGLCD.clrScr();
    homescr();
    page = 0; 
    }       
    if (page == 2) {
    //myGLCD.clrScr();
   // homescr();
    //page = 0; 
    }
   }
   delay(1000);
 }
}

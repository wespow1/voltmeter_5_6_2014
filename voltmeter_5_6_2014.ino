#include <UTFT.h>
#include <UTouch.h>
#include <stdlib.h>

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
float R2 = 100000.0;
int value = 0;
int page = 0;
int stCurrentLen=0;
int x, y;
int sensorValue = 0;
int delay_per_reading = 20;

UTouch  myTouch( 6, 5, 4, 3, 2);

void setup() {
  
 pinMode(0,INPUT);
 pinMode(1,INPUT);
 pinMode(2,INPUT);
 pinMode(3,INPUT);
 pinMode(4,INPUT);
 pinMode(5,INPUT);
 //pinMode(6,INPUT);
 
 myGLCD.InitLCD(0);
 myGLCD.clrScr();
 myGLCD.setFont(SmallFont);
 myTouch.InitTouch();
 myTouch.setPrecision(PREC_HI);
 Serial.begin(9600);
 Serial.println("Starting...");
 //homescr();
 //touchread();
}
void homescr(){
 readvoltage();
 /*
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
 */
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

  int sensorReading1 = read_sensor(1, 5);
  int sensorReading2 = read_sensor(2, 5);
  int sensorReading3 = read_sensor(3, 5);
  int sensorReading4 = read_sensor(4, 5);
  int sensorReading5 = read_sensor(5, 5);
  //int sensorReading6 = read_sensor(6, 5);

  char buffer[10];
  
  vin = 0.0;
  vin = convert_to_voltage(sensorReading1);
  dtostrf (vin, 5 , 3, buffer);
  String strout1 = buffer;
  
  vin = 0.0;
  vin = convert_to_voltage(sensorReading2);
  dtostrf (vin, 5 , 3, buffer);
  String strout2 = buffer;
  
  vin = 0.0;
  vin = convert_to_voltage(sensorReading3);
  dtostrf (vin, 5 , 3, buffer);
  String strout3 = buffer;
  
  vin = 0.0;
  vin = convert_to_voltage(sensorReading4);
  dtostrf (vin, 5 , 3, buffer);
  String strout4 = buffer;
  
  vin = 0.0;
  vin = convert_to_voltage(sensorReading5);
  dtostrf (vin, 5 , 3, buffer);  
  String strout5 = buffer;
  
  /*vin = 0.0;
  vin = convert_to_voltage(sensorReading6);
  dtostrf (vin, 5 , 3, buffer);  
  String strout6 = buffer;*/
  
  myGLCD.setColor(0, 255, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print("DC VOLTMETER", CENTER, 2);
  myGLCD.print("Voltage #1",10,90, 0);
  myGLCD.print(strout1,200,90, 0);
  myGLCD.print("Voltage #2",10,110, 0);
  myGLCD.print(strout2,200,110, 0);
  myGLCD.print("Voltage #3",10,130, 0);
  myGLCD.print(strout3,200,130, 0);
  myGLCD.print("Voltage #4",10,150, 0);
  myGLCD.print(strout4,200,150, 0);
  myGLCD.print("Voltage #5",10,170, 0);
  myGLCD.print(strout5,200,170, 0);
 /* myGLCD.print("Voltage #6",10,190, 0);
  myGLCD.print(strout6,200,190, 0); */

  }
 


void loop() {
 //Serial.println(page);
 //touchread();
 //if (page == 0);{
 homescr();
 //}
 //if (page == 1); {
   
 //}
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
   //delay(1000);
 }
}

float convert_to_voltage(int raw_sensor_data){
  float to_return = 0.0;
  vout = raw_sensor_data * ( 5.0 / 1023.0);
  //Serial.println(vout, 3);
  to_return = vout / ( R2 / (R1+R2) );  
  if (to_return <0.09) {
      to_return =0.0;
  }
  Serial.println(to_return, 3);
  return to_return;
}

int read_sensor(int pinToRead, int num_of_readings){
  int sum_of_readings = 0;
  int avg_reading = 0;
  int raw_value = 0;
  for (int i= 0; i < num_of_readings; i++) { 
    raw_value = analogRead(pinToRead);
    Serial.print("Raw:");
    Serial.println(raw_value);
    sum_of_readings = sum_of_readings + raw_value;
    //Serial.print("sum_of_readings: ");
    //Serial.println(sum_of_readings);
    delay(delay_per_reading);
  }
  avg_reading = (sum_of_readings  /  num_of_readings);
  Serial.print ("Pin:");
  Serial.println (pinToRead);
  Serial.print("avg:");
  Serial.println(avg_reading);
  return (avg_reading);
}

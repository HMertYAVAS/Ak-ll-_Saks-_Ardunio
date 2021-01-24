#include <dht.h>
dht DHT;
#include <LedControl.h>
#define DHT11_PIN 7

const int waterLevelPin = A3;
int waterLevelThreshold = 380;                                    
int sensorWaterLevelValue = 0;


int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status




int DIN = 10;
int CS =  9;
int CLK = 8;

LedControl lc=LedControl(DIN,CLK,CS,0);

void setup(){
 lc.shutdown(0,false);       
 lc.setIntensity(0,15);      //Adjust the brightness maximum is 15
 lc.clearDisplay(0);    
 Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
 pinMode(ledPin, OUTPUT);      // declare LED as output
 pinMode(inputPin, INPUT);     // declare sensor as input
}

void loop(){ 

    //Facial Expression
    byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
    byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};
    byte sad[8]=   {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};
    
    byte damla[8]={0x10,0x38,0x7C,0x7C,0xFA,0xF2,0x7C,0x38};
    
    byte kar1[8]={0x60,0xF8,0xFE,0x7F,0x00,0x04,0x4E,0xE4};
    byte kar2[8]={0x60,0xF8,0xFE,0x7F,0x00,0x02,0x27,0x72};
    byte kar3[8]={0x60,0xF8,0xFE,0x7F,0x00,0x00,0x02,0x27};
    byte kar4[8]={0x60,0xF8,0xFE,0x7F,0x00,0x00,0x04,0x4E};
   
    byte gunes1[8]={0xF8,0xF2,0xE1,0xC4,0x92,0x09,0xA4,0x92};
    byte gunes2[8]={0xF8,0xF0,0xE1,0xC0,0x82,0x09,0x24,0x92};
    byte gunes3[8]={0xF8,0xF2,0xE0,0xC4,0x90,0x01,0x04,0x92};
    
   


  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);


  sensorWaterLevelValue = analogRead(waterLevelPin);              //read the value of the water level sensor
  Serial.print("Water level sensor value: ");                     //print it to the serial monitor
  Serial.println(sensorWaterLevelValue);


//Motion Sensör kodları

val=0;
   val = digitalRead(inputPin);  // read input value
  
  if (val == HIGH)  // check if the input is HIGH
  {            

      Serial.println("Hareket Algılandı!"); // print on output change
      pirState = HIGH;
      delay(1000);
          printByte(smile);
    delay(500); 
  } 
  else 
  {

      Serial.println("Hareket Yok!");  // print on output change
      pirState = LOW;
      delay(1000);
      
    printByte(neutral);
    delay(1000);

  }
//su seviyesi için tepki

if (sensorWaterLevelValue<300){
     printByte(damla);
   delay(1000);
  
  }
else{
      printByte(smile);
    delay(1000);  
  }


//Sıcaklık seviyesi için

if(DHT.temperature>30){
     printByte(gunes1);
   delay(500);
   printByte(gunes2);
   delay(500);
   printByte(gunes3);
   delay(500);   
   printByte(gunes1);
   delay(500);
  
  }
else if(DHT.temperature<5){
  
   printByte(kar1);
   delay(500);
   printByte(kar2);
   delay(500);
   printByte(kar3);
   delay(500);
   printByte(kar4);
   delay(500);
  }   
  
else{
    printByte(smile);
    delay(500);  
  }

if(DHT.humidity<10){
    printByte(sad);    
    delay(1000);
}
else{
  printByte(smile);
  delay(500);
  }

  
}



void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}

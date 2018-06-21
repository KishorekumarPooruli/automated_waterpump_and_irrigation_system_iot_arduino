
/* AUTOMATED WATER PUMP AND IRRIGATION SYSTEM 
  DEVELOPED BY KISHORE KUMAR P B
  Queries: crazykishore2015@gmail.com
  SENSORS:  0.TEMPERATURE SENSOR
            1.WATERLEVEL SENSOR
            2.FLAME SENSOR
            3.SOIL MOISTURE SENSOR
            4.RAIN DETECT SENSOR
            5.LCD 
*/
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
//Declaration

int value; //Water Level sensor
float tempC; //temp sensor
int reading; //temp sensor
int tempPin = 0;//temp sensor

int D8=8; //Flame Sensor
int LED =13; //LED for Flame and Rain water Detect 


const int sensorMin = 0;     // sensor minimum rain detect
const int sensorMax = 1024;  // sensor maximum rain detect



int ByteReceived;
void setup()
{
  lcd.begin(16,2); // lcd begin
  lcd.setCursor(0,0);
  analogReference(INTERNAL);//Temp Sensor
  pinMode(A1, INPUT);   //Water Level Sensor
  pinMode(D8,INPUT);   //Flame Sensor
  pinMode(A5, INPUT);  //Moisture Sensor
  pinMode(A4,INPUT); //Rain Detect Sensor
  pinMode(LED,OUTPUT); //LED for Flame And Rain Detect
  pinMode(7,OUTPUT);
  Serial.begin(9600); // Serial Monitor Begin
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome to IOT");
  lcd.setCursor(0,1);
  lcd.print("Project");
  lcd.setCursor(0,0);
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("By");
  lcd.setCursor(0,1);
  lcd.print("Kishore kumar PB");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Automated Water");
  lcd.setCursor(0,1);
  lcd.print("Pump and");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Irrigation");
  lcd.setCursor(0,1);
  lcd.print("System.............");
  delay(1000);
  
  //---------------------------------------------------------------------------------------------
  Serial.println("--- Automated Water Pump And Irrigation System ---");
  Serial.println("--- Start Serial Monitor ---");
  Serial.println("Type in Box above");
  Serial.println(); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Input:");
  //----------------------------------------------------------------------------------------------

}


void loop()
{
  if (Serial.available() > 0)
  {
    ByteReceived = Serial.read();
    
 //   Serial.print(ByteReceived);   
 //   Serial.print("        ");      
 //   Serial.print(ByteReceived, HEX);
    Serial.print("       ");  
    Serial.print("\t\t");   
    Serial.print(char(ByteReceived));
    
//------------------------TEMP SENSOR CODE-----------------------------------------------------
      if(ByteReceived == '0')
      {

          Serial.print("Temperature Module:");
          reading = analogRead(tempPin);
          tempC = reading / 9.31;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Temperature:");
          lcd.setCursor(0,1);
          Serial.println(tempC);
          lcd.print(tempC);
          lcd.print("'C");
          delay(1000);
      }
      
//----------------------WATER LEVEL SENSOR CODE--------------------------------------------------

      if(ByteReceived == '1')
      {
      //Water Level Sensor 
          value = analogRead(A1);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Water Level:");
          Serial.print("Water Level Module:");
          if(value<=480)
          {
              lcd.setCursor(0,1);
              lcd.print("0mm -Empty!"); 
              Serial.println("0mm -Empty!");
              digitalWrite(7,HIGH);
          }

          else if (value>480 && value<=530)
          {
              lcd.setCursor(0,1);
              Serial.println("0mm to 5mm");
              lcd.print("0mm to 5mm");
              digitalWrite(7,LOW);
          }
          
          else if (value>530 && value<=615)
          {
      
              lcd.setCursor(0,1);
              Serial.println("5mm to 10mm");
              lcd.print("5mm to 10mm");
              digitalWrite(7,LOW);
          }
          else if (value>615 && value<=660)
          {
      
              lcd.setCursor(0,1);
              Serial.println("10mm to 15mm");
              lcd.print("10mm to 15mm");
              digitalWrite(7,LOW);
         }
         else if (value>660 && value<=680)
         {
              lcd.setCursor(0,1);
              Serial.println("15mm to 20mm");
              lcd.print("15mm to 20mm");
              digitalWrite(7,LOW);
        }
       else if (value>680 && value<=690)
       {
      
              lcd.setCursor(0,1);
              Serial.println("20mm to 25mm");
              lcd.print("20mm to 25mm");
              digitalWrite(7,LOW); 
       }
       else if (value>690 && value<=700)
       {
      
              lcd.setCursor(0,1);
              Serial.println("25mm to 35mm");
              lcd.print("25mm to 35mm");
              digitalWrite(7,LOW); 
       }
       else if (value>700 && value<=705)
       {
     
              lcd.setCursor(0,1);
              Serial.println("30mm to 35mm");
              lcd.print("30mm to 35mm"); 
              digitalWrite(7,LOW);
       }
       else if (value>705)
       {
              lcd.setCursor(0,1);
              Serial.println("35mm to 40mm");
              lcd.print("35mm to 40mm"); 
              digitalWrite(7,LOW);
       }
    }
//---------------FLAME SENSOR CODE--------------------------------------------------------------
       if(ByteReceived == '2')
       {
          int sensorreading = digitalRead(8);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Flame Module:");


          if(sensorreading==1)
          {
              digitalWrite(LED,LOW);
              Serial.println(" No Flame  ");
  
              lcd.setCursor(0,1);
              lcd.print("No Flame");
          }
          else
          {
              digitalWrite(LED,HIGH);
              Serial.println("Flame");
  
              lcd.setCursor(0,1);
               lcd.print("Flame");
          }
        }
//-------------------MOISTURE SENSOR------------------------------------------------------------
        if(ByteReceived == '3')
        {
          int SensorValue= analogRead(A5);
          lcd.setCursor(0,0);
          lcd.print("Moisture Module:");
          Serial.print(SensorValue); Serial.print(" =");

          if(SensorValue >=1000)
          {
            Serial.println("SOIL MOISTURE:Sensor is in HUMID");
            lcd.setCursor(0,1);
            lcd.print("Status:HUMID");
          }
          if(SensorValue <910 && SensorValue >=600)
          {
            Serial.println("SOIL MOISTURE:Soil is DRY");
            lcd.setCursor(0,1);
            lcd.print("Status:Dry");
          }
          if(SensorValue <600 && SensorValue >=370)
          {
            Serial.println("SOIL MOISTURE:Soil is HUMID");
            lcd.setCursor(0,1);
            lcd.print("Status:Humid");
          }

          if(SensorValue <370)
          {
              Serial.println("SOIL MOISTURE:Sensor is in Water");
              lcd.setCursor(0,1);
              lcd.print("Status:Water");
         }
        }
//------------------------RAIN DETECT SENSOR----------------------------------------------------
        if(ByteReceived == '4')
        {
          int sensorReading = analogRead(A4);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Rain Detect:");
          int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  
         // range value:
            switch (range) {
            case 0:    // Sensor getting wet
             Serial.println("Flood");
             lcd.setCursor(0,1);
             lcd.print("FLOOD"); 
             break;
             case 1:    // Sensor getting wet
             Serial.println("Rain Warning");
             lcd.setCursor(0,1);
             lcd.print("RAIN WARNING");
             break;
             case 2:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
             Serial.println("Not Raining");
             lcd.setCursor(0,1);
             lcd.print("NOT RAINING");
             break;
             }
        }
//------------------------ALL MODULES OVER-------------------------------------------------------
  }
}

  



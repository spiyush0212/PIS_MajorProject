#include <Wire.h>                                                             // Library for I2C communication
#include <LiquidCrystal_I2C.h>                                                // Library for LCD
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd1 = LiquidCrystal_I2C(0x23, 20, 4);
LiquidCrystal_I2C lcd2 = LiquidCrystal_I2C(0x25, 20, 4);
LiquidCrystal_I2C lcd3 = LiquidCrystal_I2C(0x26, 20, 4);
LiquidCrystal_I2C lcd4 = LiquidCrystal_I2C(0x27, 20, 4);

const int analogInPin = A0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;
int blueled = 13;
int redled = 24;
int greenled = 25;
int tempblueled = 32;
int tempredled = 33;
int tempgreenled = 34;
int levblueled = 35;
int levredled = 36;
int levgreenled = 37;
int turbblueled = 38;
int turbredled = 39;
int turbgreenled = 40;
int buzzer = 31;

void setup() 
{
  sensors.begin();
  Serial.begin(9600);
  
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();
  
  pinMode(trigPin, OUTPUT);                               // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
}


void loop() 
{
  
ph();
turb();

}


/*
  //ultrasonic code 
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);                                    // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);                                       // Reads the echoPin, returns the sound wave travel time in microseconds

duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;                                       // Calculating the distance

Serial.print("Distance: ");                                       // Prints the distance on the Serial Monitor
Serial.println(distance);

 lcd3.setCursor(0, 0);
 lcd3.print("water level");
 lcd3.setCursor(2,1);
 lcd3.print(distance);


 //temperature
 //temperature
 //temperature
 //temperature

  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);

  Serial.print(Celsius);
  Serial.print(" C  ");
  Serial.print(Fahrenheit);
  Serial.println(" F");

  */




    void ph()
    {
        for(int i=0;i<10;i++) 
        { 
            buf[i]=analogRead(analogInPin);
            delay(10);
        }
        for(int i=0;i<9;i++)
        { 
            for(int j=i+1;j<10;j++)
            {
                if(buf[i]>buf[j])
                {
                    temp=buf[i];
                    buf[i]=buf[j];
                    buf[j]=temp;
                }
            } 
        }
 
        avgValue=0;
 
        for(int i=2;i<8;i++)
            avgValue+=buf[i];
   
        float pHVol=(float)avgValue*5.0/1024/6;
        float phValue = ((-5.70 * pHVol) + 21.34);
 
        Serial.print("sensor = ");
        Serial.println(phValue);
 
        delay(20);

        if(phValue >= 7.30)
        {
            digitalWrite(blueled, LOW);
            digitalWrite(greenled, LOW);
            digitalWrite(redled, HIGH);
            digitalWrite(buzzer, HIGH);
    
            Serial.print("PH VALUE: ");
            Serial.println(phValue); 
            Serial.println("Water Alkalinity high");
            delay(3000);
        }


        
        if(phValue >= 6.90 && phValue <= 7.19)
        {
            digitalWrite(blueled, HIGH);
            digitalWrite(greenled,LOW);
            digitalWrite(redled, LOW);
            digitalWrite(buzzer, LOW);
  
            Serial.print("PH VALUE: ");
            Serial.println(phValue); 
            Serial.println("Water Is  neutral (safe)");
        }
        
         if(phValue < 6.89)
         {
             digitalWrite(blueled, LOW);
             digitalWrite(greenled, LOW);
             digitalWrite(redled, HIGH);
             digitalWrite(buzzer, HIGH);
    
             Serial.print("PH VALUE: ");
             Serial.println(phValue); 
             Serial.println("Water Acidity High");
             delay(3000);
         }
         
        delay(8000);
    } 


// CODE FOR TURBIDITY SENSOR

    void turb()
{
        int sensorValue = analogRead(A1);                               // read the input on analog pin 0:
        float voltage = sensorValue * (5.0 / 1024.0);                   // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  
        Serial.println(voltage);                                        // print out the value you read:
        delay(500);

    if( voltage > 9)
    {
        digitalWrite(turbblueled, LOW);
        digitalWrite(turbgreenled, LOW);
        digitalWrite(turbredled, HIGH);
        digitalWrite(buzzer, HIGH);
  
        Serial.print("Turbidity Level: ");
        Serial.print(voltage ); 
        Serial.println("Water Very Clean ");
        delay(3000);
    }

    if( voltage >= 6 && voltage <= 9 )
    {
        digitalWrite(turbblueled, HIGH);
        digitalWrite(turbgreenled, LOW);
        digitalWrite(turbredled, LOW);
        digitalWrite(buzzer, LOW);
    
        Serial.print("Turbidity Level: ");
        Serial.print(voltage ); 
        Serial.println("Water Clean ");
    }

    if( voltage < 6)
    {
        digitalWrite(turbblueled, LOW);
        digitalWrite(turbgreenled, LOW);
        digitalWrite(turbredled, HIGH);
        digitalWrite(buzzer, HIGH);
   
        Serial.print("Turbidity Level: ");
        Serial.print(voltage ); 
        Serial.println("Water Very Dirty ");
        delay(3000);
   }
   
      delay (8000);
 }
 
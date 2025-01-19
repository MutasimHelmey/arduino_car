//Thes software is FOSS OSL-1.0 
//GNU AGPLv3
//CC BY-NC-ND 4.0
/********************* defines Start **********************/
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define RX 2
#define TX 3
#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10
#define buzzer 11
#define FrontLed 12
#define BackLed 13
SoftwareSerial bluetooth(2,3);
LiquidCrystal_I2C lcd(0x27, 24,4);
/********************* defines End **********************/

/******************** variable Start **********************/
int speed = 255;
String blumsg ="";
/******************** variable Start **********************/


/********************* setup Start **********************/
void setup() {
  pinMode(IN1, OUTPUT);  //RIGHT MOTOR FRONT
  pinMode(IN2, OUTPUT);  //RIGHT MOTOR BACK
  pinMode(IN3, OUTPUT);  //LEFT MOTOR FRONT
  pinMode(IN4, OUTPUT);  //LEFT MOTOR BACK
  pinMode(BackLed,OUTPUT);
  pinMode(FrontLed,OUTPUT);
  pinMode(buzzer,OUTPUT);
  lcd.begin();

  Serial.begin(9600);
  bluetooth.begin(9600);
  car_setup();

} 
/********************* setup End **********************/

void loop() {
  if (bluetooth.available())
  {
    blumsg = bluetooth.readString();
    Serial.println(blumsg);
    Serial.println();
    /********************* bluetooth Start **********************/
    if (blumsg=="Front")    {front();}
    else if (blumsg=="Back"){back(); }
    else if(blumsg=="Right"){right();}
    else if(blumsg=="Left") {left(); }
    else if(blumsg=="Stop") {stop(); }

    else if(blumsg[0]=="S" &&  blumsg[1]==":" )  
    {
      //speed = blumsg.substring(2).toInt();
      digitalWrite(buzzer,HIGH);
      Serial.print(speed);
      lcd.setCursor(8,1);
      lcd.print("speed");
    }
    /********************* bluetooth End **********************/
    speed = 255;
    blumsg = " ";
  }
/********************* loop Start **********************/

/********************* loop End **********************/
}

/********************* functions **********************/
void car_setup()
{
  lcd.backlight();
  lcd.setCursor(7, 1);
  lcd.print("ready");
  digitalWrite(buzzer,HIGH);
  digitalWrite(FrontLed,HIGH);
  digitalWrite(BackLed,HIGH);
  delay(2000);
  lcd.clear();
  digitalWrite(buzzer,LOW);
  digitalWrite(FrontLed,LOW);
  digitalWrite(BackLed,LOW);
  lcd.setCursor(0,0);
  lcd.print("direction : ");
  lcd.setCursor(0,1);
  lcd.print("speed : ");
  lcd.setCursor(0,2);
  lcd.print("mesage : ");
}
void front() {
  analogWrite(IN1, speed);
  analogWrite(IN3, speed);
  analogWrite(IN2, 0);
  analogWrite(IN4, 0);
  lcd.setCursor(11,0 );
  lcd.print("Front");
}
void back() {
  analogWrite(IN2, speed);
  analogWrite(IN4, speed);
  analogWrite(IN1, 0);
  analogWrite(IN3, 0);
  lcd.setCursor(11,0 );
  lcd.print("Back ");
}
void right() {
  analogWrite(IN1, speed);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
  lcd.setCursor(11,0 );
  lcd.print("Right");
}
void left() {
  analogWrite(IN3, speed);
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN4, 0);
  lcd.setCursor(11,0 );
  lcd.print("Left ");
}
void stop() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
  lcd.setCursor(11,0 );
  lcd.print("Stop ");
}                                                          
/******************************************/
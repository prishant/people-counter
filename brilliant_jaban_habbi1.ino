#include<LiquidCrystal.h>

int count=0;
int indoor=15;
int inpr=16;
int outdoor=14;
int outpr=17;
float temp;
int tempPin = A5;
const int buzzer = 9;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
byte bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
byte cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};

void setup()
{
  pinMode(15, INPUT);
  pinMode(14, INPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop()
{
  lcd.clear();
  lcd.createChar(1, heart);
  lcd.createChar(2, bell);
  lcd.createChar(3, cross);
  
  digitalWrite(outpr, HIGH);
  digitalWrite(inpr, HIGH);
  
  lcd.setCursor(0,0);
  lcd.print("People Counter ");
  lcd.write(2);
  
  //Measuring temparature
  temp = analogRead(tempPin);
  temp = temp / 1024;       
  temp = temp * 5;          
  temp = temp - 0.5;               
  temp = temp * 100; 
  
  
  //check for person entering
  if(digitalRead(outdoor)==1)
  {
    lcd.setCursor(0,1);
    lcd.print("person entering");
    while(!digitalRead(indoor))
      delay(5);
      count+=1;
    while(digitalRead(indoor))
      delay(5);
  }
  //check for person leaving
  if(digitalRead(indoor)==1)
  {
    lcd.setCursor(0,1);
    lcd.print("person leaving");
    while(!digitalRead(outdoor))
      delay(5);
    if(count>0)
      count-=1;
    while(digitalRead(outdoor))
      delay(5);
  }
  
  //covid-19 condition check
	if(temp>39.1)
  {
    tone(buzzer, 1000); // Send 1KHz sound signal...
    lcd.setCursor(0,1);
    lcd.print("Action required");
      lcd.write(3);
    delay(200);
    noTone(buzzer);     // Stop sound...
  }
  else
  {
 	LCD_setup();
  	delay(200);
  }
}

void LCD_setup()
{
  lcd.setCursor(0,1);
  lcd.print("Count : ");
  if(count<1000)
  	lcd.print(count);
  
  else if(count<1000000)
  {
    lcd.print(count/1000);
    lcd.print("K");
  }
	lcd.write(1);
}
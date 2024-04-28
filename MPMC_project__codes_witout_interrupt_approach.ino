#include <LiquidCrystal_I2C.h>

#define MOTSPEED 9
#define DIRECTION1 8
#define DIRECTION2 7
#define POT A0
#define PUSH 2

int reg;
int dirState=1;
int rpm;


 
LiquidCrystal_I2C lcd(0x20, 16, 2);

//unsigned long LastTimePressed=millis();
//unsigned long debounceDelay=50;

void DirectionToggle(){
  if(dirState==1){
    dirState=2;
  }
  else{
    dirState=1;
}
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 pinMode(PUSH,INPUT);
  pinMode(POT,INPUT);
 pinMode(MOTSPEED,OUTPUT);
 pinMode(DIRECTION1,OUTPUT);
 pinMode(DIRECTION2,OUTPUT);
  Serial.println("fully functional"); 
  
 lcd.init();  // initialize the lcd
    
 lcd.backlight();   // Turn on the Backlight
  

}

void loop() {
  // put your main code here, to run repeatedly:
// unsigned long TimeNow=millis();
 

    
   

  if(digitalRead(PUSH)==1){
   DirectionToggle();
    lcd.clear();
  }
 
//delay(500);

  if(dirState==1){
 digitalWrite(DIRECTION1,HIGH);
 digitalWrite(DIRECTION2,LOW);
    
    lcd.setCursor(0,1);
    lcd.print("CW ");
    Serial.println("d1");
 
  }
 else if(dirState==2){
 digitalWrite(DIRECTION1,LOW);
 digitalWrite(DIRECTION2,HIGH);
   lcd.setCursor(0,1);
    lcd.print("AW ");
 Serial.println("d2");
  }  

   reg=analogRead(POT)/4;

analogWrite(MOTSPEED,reg);
 
  rpm=64.8235294118*reg;
 Serial.println(rpm);
  
   lcd.setCursor(0,0);
      
    lcd.print("Regulator:");
  lcd.print(reg);  
  lcd.print("         ");
  
   
    lcd.setCursor(3,1);
    
    lcd.print("RPM:");
   lcd.print(rpm);
  lcd.print("         ");
  

delay(500);
}

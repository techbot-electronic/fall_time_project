int button = 3;
int relay = 4;
int cbRung = 5;
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
long duration, distance; // Duration used to calculate distance

// cau hinh 0.5 s
const long interval = 500;
unsigned long prevMillis = 0;

int TIME_OUT = 0;

bool flg = false;


void setup() {

  lcd.init(); // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  // Blinking block cursor
  lcd.blink_on();
  
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  // Cau hinh nut nhan nhan tin hieu dau vao
  pinMode(button, INPUT);
  pinMode(cbRung, INPUT);

  // Cau hinh dieu khien relay
  pinMode(relay, OUTPUT);

  // Bat relay de luon luon hut thanh sat
  digitalWrite(relay, LOW);
 


}

void loop() {

    int buttonStatus = digitalRead(button);
  int cbRung = digitalRead(cbRung);
    
     digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 
  
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10); 
   
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   
   //Calculate the distance (in cm) based on the speed of sound.
   distance = duration/58.2;

    String disp = String(distance);
   
   lcd.clear();
   lcd.print("h = :"); // first line 
   lcd.setCursor(0, 1); // second line
   lcd.print(disp);
   lcd.print(" cm");
   if (cbRung == 1) {
    lcd.setCursor(1, 1); // second line
   lcd.print("detect CB Rung");
    }
  


  if (buttonStatus == 1 && TIME_OUT == 0) {
    flg = true;
    Serial.println("BAT RELAY");
      digitalWrite(relay, LOW);
  } else {
        flg = false;
        TIME_OUT = 0;
      digitalWrite(relay, HIGH);
  }




  

  unsigned long currentMillis = millis();
  // Cau hinh chong nhieu khi doc nut nhan
  if (currentMillis - prevMillis >= interval) {
       prevMillis = currentMillis;
       if (flg) {
        TIME_OUT ++;
       // 0, 1, 2, 3 --> 2 s
       if (TIME_OUT > 4) {
           TIME_OUT = 0;
           flg = false;
       }
       }
       
       
    
    
   }
   

  
  

}

#define RELAY 4
#define CB_RUNG A0
#define BUTTON 2
#define ECHO 7        // Pin received echo pulse
#define TRIGGER 8     // Pin sends shot pulse 

#define BAT_RELAY digitalWrite(RELAY, HIGH)
#define TAT_RELAY digitalWrite(RELAY, LOW)

#include <LiquidCrystal_I2C.h>

#include <Wire.h> 


 
//#define TRIGGER_PIN 11
//#define ECHO_PIN 12
#define MAX_DISTANCE 200


// NewPing setup of pins and maximum distance
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

LiquidCrystal_I2C lcd(0x27,16,2); 


// cau hinh 0.5 s
unsigned long interval = 1, count = 0;
unsigned long tag = 0, debounce = 0;

int TIME_OUT = 0;

bool flg = false;
int todo = 0;


void setup() {


  
  Serial.begin(9600);
  lcd.init();                    
  lcd.backlight();

  
  // put your setup code here, to run once:
  // Cau hinh nut nhan nhan tin hieu dau vao
  pinMode(BUTTON, INPUT);
  pinMode(CB_RUNG, INPUT);

  // Cau hinh dieu khien relay
  pinMode(RELAY, OUTPUT);
  pinMode(TRIGGER,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(ECHO,INPUT);    // chân echo sẽ nhận tín hiệu


  BAT_RELAY;


}

void loop() {
//
//unsigned long currentMillis = micros();
//digitalWrite(TRIGGER, LOW);
//
//if (currentMillis - previousMillis > 4) {
//  digitalWrite(TRIGGER, HIGH);
//  previousMillis = currentMillis;
//}
//
//if (currentMillis - previousMillis > 12) {
//  digitalWrite(TRIGGER, LOW);
//  previousMillis = currentMillis;
//}
//
//duration = pulseIn(ECHO, HIGH);
//distance_sm = impulseTime / 58; // convert to centimeters
//distance = distance_sm;
  
//unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
//    digitalWrite(TRIGGER,0);   // tắt chân trig
//    delayMicroseconds(2);
//    digitalWrite(TRIGGER,1);   // phát xung từ chân trig
//    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
//    digitalWrite(TRIGGER,0);   // tắt chân trig
//    
//    /* Tính toán thời gian */
//    // Đo độ rộng xung HIGH ở chân echo. 
//    duration = pulseIn(ECHO,HIGH);  
//    // Tính khoảng cách đến vật.
//    distance = int(duration/2/29.412);

  

 int buttonStatus = digitalRead(BUTTON);
  int cbRung = analogRead(CB_RUNG);

  if (debounce > 0) debounce--;

  if (buttonStatus == 1 && debounce == 0) {
    todo = 1;
    debounce = 200;
    TAT_RELAY; // tat 
    tag = millis(); // co bat dau dem
  }

  if (buttonStatus == 0 && debounce == 0 && todo == 1) {
      
      todo = 2;
      debounce = 200;
      BAT_RELAY;  // bat
  }
  
 
  if (millis() - tag > interval) {
    tag = millis();
    count += 1;    
  }
  
     if (cbRung < 500  && todo == 2) {
        int totalMs = count * 10;
        float second = (float)totalMs / 1000.0;
        String result = String(second);
        todo = 0;
        
        Serial.print(result);
        Serial.println(" s");

        lcd.clear();
        lcd.setCursor(0,0);   
        lcd.print("t = "); 
        lcd.setCursor(4, 0); 
        lcd.print(result + "s");
  
        lcd.setCursor(0,1);   
        lcd.print("h = "); 
        lcd.setCursor(4, 1); 
        lcd.print(String(distance) + "cm");
  
        count = 0;

  
    }

   


   

  
  

}

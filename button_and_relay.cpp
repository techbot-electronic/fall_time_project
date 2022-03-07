#include <LiquidCrystal_I2C.h>

#include <Wire.h> 
//#include <NewPing.h>

int button = 3;
int relay = 4;
int cbRung = 1;

 
//#define TRIGGER_PIN 11
//#define ECHO_PIN 12
#define MAX_DISTANCE 200


// NewPing setup of pins and maximum distance
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

LiquidCrystal_I2C lcd(0x27,16,2); 

long duration, distance; // Duration used to calculate distance

// cau hinh 0.5 s
unsigned long interval = 10, count = 0;
unsigned long tag = 0, debounce = 0;

int TIME_OUT = 0;

bool flg = false;
bool todo = false;


void setup() {


  
  Serial.begin(9600);
  lcd.init();                    
  lcd.backlight();

  
  // put your setup code here, to run once:
  // Cau hinh nut nhan nhan tin hieu dau vao
  pinMode(button, INPUT);
  pinMode(cbRung, INPUT);

  // Cau hinh dieu khien relay
  pinMode(relay, OUTPUT);

  digitalWrite(relay, HIGH);
 


}

void loop() {

 int buttonStatus = digitalRead(button);
  int cbRung = analogRead(cbRung);
 
   Serial.println(cbRung);
  
 // unsigned int distance = sonar.ping_cm();
  String disp = String("123");
  String result = String(count * 10);

   if (cbRung < 500 && !todo ) {
      Serial.println("HERE ---->>>");
      lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
      lcd.print("Hello world!");
      lcd.clear();
      lcd.print("t = "); // first line 
      lcd.setCursor(4, 0); // second line
      lcd.print(result);
  
    }

  
  if (debounce > 0) debounce--;

  if (buttonStatus == 1 && debounce == 0) {
    Serial.println("TAT RELAY");
    todo = false;
    debounce = 200;
    digitalWrite(relay, LOW); // tat 
    tag = millis(); // co bat dau dem
  }

  if (buttonStatus == 0 && debounce == 0 && !todo) {
      
      todo = true;
      debounce = 200;
      Serial.println("BAT RELAY");
      digitalWrite(relay, HIGH);  // bat
  }
  
 
  if (millis() - tag > interval) {
    tag = millis();
    count += 1;    
  }
  
   


   

  
  

}

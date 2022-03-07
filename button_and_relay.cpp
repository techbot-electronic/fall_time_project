#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//#include <NewPing.h>

int button = 3;
int relay = 4;
int cbRung = 5;

 
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

  lcd.init(); // initialize the lcd 
  lcd.backlight();
  lcd.blink_on();
  
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  // Cau hinh nut nhan nhan tin hieu dau vao
  pinMode(button, INPUT);
  pinMode(cbRung, INPUT);

  // Cau hinh dieu khien relay
  pinMode(relay, OUTPUT);

  digitalWrite(relay, LOW);
 


}

void loop() {

  int buttonStatus = digitalRead(button);
  int cbRung = digitalRead(cbRung);
  
 // unsigned int distance = sonar.ping_cm();
  String disp = String("123");
  String result = String(count * 10);

   if (cbRung == 1 && result != "") {

      lcd.clear();
      lcd.print("h = :"); // first line 
      lcd.setCursor(0, 1); // second line
      lcd.print(disp);
      lcd.print(" cm");
      lcd.setCursor(1, 1); // second line
      lcd.print(result);
      result = "";
    }

  
  if (debounce > 0) debounce--;

  if (buttonStatus == 1 && debounce == 0) {
    debounce = 200;
    digitalWrite(relay, HIGH); // tat 
    tag = millis(); // co bat dau dem
  }

  if (buttonStatus == 0 && debounce == 0 && !todo) {
      
      todo = true;
      debounce = 200;
      Serial.println("BAT RELAY");
      digitalWrite(relay, LOW);  // bat
  }
  
 
  if (millis() - tag > interval) {
    tag = millis();
    count += 1;    
  }
  
   


   

  
  

}

int button = 3;
int relay = 4;

// cau hinh 0.5 s
const long interval = 500;
unsigned long prevMillis = 0;

int TIME_OUT = 0;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // Cau hinh nut nhan nhan tin hieu dau vao
  pinMode(button, INPUT);
  // Cau hinh dieu khien relay
  pinMode(relay, OUTPUT);

  // Bat relay de luon luon hut thanh sat
  digitalWrite(relay, HIGH);

}

void loop() {
  
  // put your main code here, to run repeatedly:
  int buttonStatus = digitalRead(button);
  if (buttonStatus == 1) {
    Serial.println("BAT RELAY");
      digitalWrite(relay, HIGH);
  } else {
        Serial.println("TTAT RELAY");

      digitalWrite(relay, LOW);
  }
  

//  unsigned long currentMillis = millis();
//  // Cau hinh chong nhieu khi doc nut nhan
//  if (currentMillis - prevMillis >= interval) {
//       prevMillis = currentMillis;
//       TIME_OUT ++;
//       // 0, 1, 2, 3 --> 2 s
//       if (TIME_OUT > 4) {
//           TIME_OUT = 0;
//       }
//       
//    
//    
//   }
   

  
  

}

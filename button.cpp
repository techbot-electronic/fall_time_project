int cbRung = 11;
void setup() {
  Serial.begin(9600);
  pinMode(cbRung, INPUT);  //Cài đặt chân D11 ở trạng thái đọc dữ liệu
}

void loop() {
  int readCbRung = digitalRead(cbRung);    //Đọc trạng thái button
  if (readCbRung == HIGH) { // Nếu mà button bị nhấn
    Serial.println("OK");
  } else { // ngược lại
     Serial.println("NOT OK");

  }
}

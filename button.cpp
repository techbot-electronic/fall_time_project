int cbRung = 11;
void setup() {
  Serial.begin(9600);
  pinMode(cbRung, INPUT);  //Cài đặt chân D11 ở trạng thái đọc dữ liệu
}

void loop() {
  int cbRung = digitalRead(button);    //Đọc trạng thái button
  if (buttonStatus == HIGH) { // Nếu mà button bị nhấn
    Serial.println("OK");
  } else { // ngược lại
     Serial.println("NOT OK");

  }
}

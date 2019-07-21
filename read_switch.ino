//This method reads a switch to change mode from weather to news and vice versa
void read_switch() {
  int switch_data = digitalRead(switchPin);
  //  if (Serial.available() > 0) {
  switch_mode = switch_data;
//  Serial.println(switch_data);
  delay(100);
  //  }
}

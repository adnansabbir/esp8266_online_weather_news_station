String weather_url = "http://api.openweathermap.org/data/2.5/weather?lat=23.7011&lon=90.4263&appid=";
String weather_APIKEY = "xxxxxxxxxxxxxxxxxxxxxxxxx";
void get_weather() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http; //Object of class HTTPClient
    http.begin(weather_url+weather_APIKEY);
    int httpCode = http.GET();
    if (httpCode == 200)
    {
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());

      int id = root["id"];
      const char* name = root["name"];
      const char* temp = root["main"]["temp"];
      const char* pressure = root["main"]["pressure"];
      const char* humidity = root["main"]["humidity"];
      const char* weather = root["weather"]["main"];


      Serial.print("Name:");
      Serial.println(name);
      Serial.print("Temperature:");
      Serial.println(temp);
      Serial.print("Pressure:");
      Serial.println(pressure);
      Serial.print("Humidity:");
      Serial.println(humidity);

      print_weather_data(name, temp, pressure, humidity, weather);

    }
    http.end(); //Close connection


  }
}

void print_weather_data(String name, String temp, String pressure, String humidity, String weather) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("City: "+name);

  lcd.setCursor(0, 1);
  lcd.print("Temperature: "+temp);

  lcd.setCursor(0, 2);
  lcd.print("Presssure: "+pressure);

  lcd.setCursor(0, 3);
  lcd.print("Humidity: "+humidity);

  while(switch_mode==1){
    read_switch();
    Serial.println("In weather mode");
    }
}

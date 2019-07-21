//This method fetches news update from newsapi.org and displays it in 2004 LCD with ha time interval of 6 sec each news 

String news_url = "http://newsapi.org/v2/top-headlines?sources=techcrunch&apiKey=";
String news_APIKEY = "xxxxxxxxxxxxxxxxxxxxxxxxx";
void get_news() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http; //Object of class HTTPClient
    http.begin(news_url+news_APIKEY);
    int httpCode = http.GET();
    if (httpCode == 200)
    {
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());

      int id = root["id"];
      JsonArray& articles = root["articles"];
      //      JsonObject& nowT = articles[0];

      const char* status = root["status"];
      String article1 = articles[0]["title"];
      String article2 = articles[1]["title"];
      String article3 = articles[2]["title"];
      String article4 = articles[3]["title"];
      String article5 = articles[4]["title"];

      Serial.print("Articles:");
      Serial.println(article2);

      print_articles_to_lcd_with_interval(article1, article2, article3, article4, article5, 6000);
    }
    http.end(); //Close connection

    //    delay(20000);
  }
}

void print_articles_to_lcd_with_interval(String a1, String a2, String a3, String a4, String a5, int interval) {
  int counter = 0;
  
  while (switch_mode==0) {
    if(counter%5==0) print_long_string_to_lcd(a1, interval);
    if(counter%5==1) print_long_string_to_lcd(a2, interval);
    if(counter%5==2) print_long_string_to_lcd(a3, interval);
    if(counter%5==3) print_long_string_to_lcd(a4, interval);
    if(counter%5==4) print_long_string_to_lcd(a5, interval);

    counter++;
    read_switch();
    Serial.println("In news mode");
  }
}

void print_long_string_to_lcd(String str, int interval) {
  Serial.println(str);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(str.substring(0, 20));

  lcd.setCursor(0, 1);
  lcd.print(str.substring(20, 40));

  lcd.setCursor(0, 2);
  lcd.print(str.substring(40, 60));

  lcd.setCursor(0, 3);
  lcd.print(str.substring(60, 80));

  delay(interval);

  //  char str_char[100];
  //  str.toCharArray(str_char, 100);
}

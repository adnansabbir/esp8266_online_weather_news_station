#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 4;
// set LCD address, number of columns and rows
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

//Set Wifi SSID and Password
const char* ssid     = "YOUR_SSID";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "YOUR_WIFI_NETWORK_PASSWORD";     // The password of the Wi-Fi network

int switchPin = 12;
int switch_mode = 1; //1 = Weather 0 == News
void setup() {
  //  Setup
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  pinMode(switchPin, INPUT_PULLUP);

  // initialize LCD and turn backlight on
  lcd.init();
  lcd.backlight();

  //  Welcome Message
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");

  connect_to_wifi();

  read_switch();
}

void connect_to_wifi() {
  //  Connecting to WiFI
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  delay(1500);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print(ssid); Serial.println(" ...");

  int i = 0;
  lcd.setCursor(0, 2);
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
    lcd.print(i);
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connection");
  lcd.setCursor(0, 1);
  lcd.print("Established!");
  delay(2000);

}

void loop() {
  // set cursor to first column, first row

  if (switch_mode == 1)
  {
    get_weather();
  }
  else if (switch_mode == 0)
  {
    get_news();
  }
}

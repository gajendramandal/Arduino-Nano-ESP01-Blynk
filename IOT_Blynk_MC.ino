
// Blynk credentials - fill yours here
#define BLYNK_TEMPLATE_ID "TMPL3lIWmAldx"           //BLYNK_TEMPLATE_ID
#define BLYNK_TEMPLATE_NAME "LED ON OFF"              //BLYNK_TEMPLATE_NAME
#define BLYNK_AUTH_TOKEN "**********-XH4k9xeB9-zb1Wu" ////BLYNK_AUTH_TOKEN

#define BLYNK_PRINT Serial

#include <SoftwareSerial.h>

//  Use BlynkESP8266 library path
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char ssid[] = "dd";          //wifi_name
char pass[] = "12345678";    //wifi_password

SoftwareSerial EspSerial(13, 2); //conection pins
#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);

#define OUTPUT_PIN 7     //sensor connected pins

BLYNK_WRITE(V0) {
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(OUTPUT_PIN, HIGH);
    Serial.println("ON");
  } else {
    digitalWrite(OUTPUT_PIN, LOW);
    Serial.println("OFF");
  }
}

void setup() {
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(1000);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, LOW);
  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
}

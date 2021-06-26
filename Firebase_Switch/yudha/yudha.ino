#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "AndroidAP"
#define WIFI_PASSWORD "khansakm"

#define TOKEN "WclzvEO0Yyak65pPrrb4NG12Utt8t38CPeEOBZ9J"

/* 3. Define the RTDB URL */
#define DATABASE_URL "tugas-akhir-7d195-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#define Relay1 D8 //Pin 8 NodeMcu sebgai D8 PinOut
#define led D4 //Pin 2 NodeMcu sebgai D0 PinOut
#define sensor A0 //Pin A0 untuk sensor
String tmpget; //Temporary Data from String to Integer
int val1;
int adc;
float cout;
float ntu;

void setup()
{
  pinMode(Relay1, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);
  
  Serial.begin(115200);  
  wifi();
  conect();
}

void wifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.println(".");
      delay(300);
  }
  Serial.print("\n Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void conect()
{
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.database_url = DATABASE_URL;
  config.signer.tokens.legacy_token = TOKEN;

  Firebase.begin(&config, &auth);

  Firebase.reconnectWiFi(true);
}

void pull()
{
  if (Firebase.RTDB.getString(&fbdo, "/DB/Filter")) {
    if (fbdo.dataType() == "string") {
      Serial.println(fbdo.stringData());
    }
  } else {
    Serial.println(fbdo.errorReason());
  }
}

void convert()
{
  tmpget = fbdo.stringData();
  val1 = tmpget.toInt();
}

void cek()
{
  if (val1 == 0) {
    digitalWrite(led, HIGH);
    digitalWrite(Relay1, HIGH);
    Serial.println("Relay Dinyalakan");
  } else {
    digitalWrite(Relay1, LOW);
    digitalWrite(led, LOW);
    Serial.println("Relay Dimatikan");
  }
}

void baca()
{
  adc = analogRead(sensor);  // Get value of ADC (integer)
  
  cout = adc*1.00; //Confert to float
  
  ntu = (cout - 855.0)/(0.29*-1); // final NTU value  
}

void kirim()
{
  if (Firebase.ready())
  {
    Firebase.RTDB.setFloat(&fbdo, "/DB/NTU", ntu);
  }
}

void loop()
{
  pull();
  convert();
  cek();
  baca();
  kirim();
  
  Serial.print("\n Status Filter     : ");
  Serial.println(val1);

  Serial.print("NTU : ");
  Serial.println(ntu);

  delay(300);
}

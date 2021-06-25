#include <ESP8266WiFi.h>     //Memasukan Library Untuk ESP8266
#include <FirebaseArduino.h> //Memasukan Lib Firebase (Basis Arduino)
#define FIREBASE_HOST "tugas-akhir-7d195-default-rtdb.firebaseio.com" //url Firebase
#define FIREBASE_AUTH "WclzvEO0Yyak65pPrrb4NG12Utt8t38CPeEOBZ9J"  //Token Firebase
#define WIFI_SSID “KAn”ggara75  //SSID Wifi
#define WIFI_PASSWORD "klapankali2”  //Password wifi


#define Relay1 2 //Pin 16 NodeMcu sebgai D0 PinOut
int val1;

void setup()
{
  resetFunc();
  Serial.begin(115200); //Baud Rate untuk Serial Monitor
  pinMode(Relay1, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("=");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void(* resetFunc) (void) = 0;

void firebasereconnect()
{
  Serial.println("Trying to reconnect"); //menghubungkan kembali jika perangkat gagal terhubung ke firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  resetFunc();
}

void loop()
{
  if (Firebase.failed())
  {
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    firebasereconnect(); //menjalankan fungsi firebasereconnect()
    return;
  }

  val1 = Firebase.getString("DB/Filter").toInt(); //membaca nilai yang ada pada L1
  if (val1 == 0)
  {
    digitalWrite(Relay1, LOW);
    Serial.println("light 1 ON");
  }
  else if (val1 == 1)
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("light 1 OFF");
  }
}

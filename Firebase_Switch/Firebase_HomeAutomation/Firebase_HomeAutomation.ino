#include <ESP8266WiFi.h>     //Memasukan Library Untuk ESP8266
#include <FirebaseArduino.h> //Memasukan Lib Firebase (Basis Arduino)
#define FIREBASE_HOST "iot-saklar.firebaseio.com" //url Firebase
#define FIREBASE_AUTH "lxaAkwAdObs4KspY6BPo5IIqB0ySEjqA23FW4lKt"  //Token Firebase
#define WIFI_SSID "HiMaTe16"  //SSID Wifi
#define WIFI_PASSWORD "klapankali"  //Password wifi

#define Relay1 16 //Pin 16 NodeMcu sebgai D0 PinOut
int val1;
#define Relay2 5 //Pin 16 NodeMcu sebgai D1 PinOut
int val2;
#define Relay3 4 //Pin 16 NodeMcu sebgai D2 PinOut
int val3;
#define Relay4 0 //Pin 16 NodeMcu sebgai D3 PinOut
int val4;

void setup()
{
  resetFunc();
  Serial.begin(115200); //Baud Rate untuk Serial Monitor
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);

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

  val1 = Firebase.getString("IoT/L1").toInt(); //membaca nilai yang ada pada L1
  val2 = Firebase.getString("IoT/L2").toInt(); //membaca nilai yang ada pada L2
  val3 = Firebase.getString("IoT/L3").toInt(); //membaca nilai yang ada pada L2
  val4 = Firebase.getString("IoT/L4").toInt(); //membaca nilai yang ada pada L2
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
  else if (val2 == 0)
  {
    digitalWrite(Relay2, LOW);
    Serial.println("light 2 ON");
  }
  else if (val2 == 1)
  {
    digitalWrite(Relay2, HIGH);
    Serial.println("light 2 OFF");
  }
  else  if (val3 == 0)
  {
    digitalWrite(Relay3, LOW);
    Serial.println("light 3 ON");
  }
  else if (val3 == 1)
  {
    digitalWrite(Relay3, HIGH);
    Serial.println("light 3 OFF");
  }
  else if (val4 == 0) // Jika nilai =  Saklar Dimatikan
  {
    digitalWrite(Relay4, LOW);
    Serial.println("light 4 ON");
  }
  else if (val4 == 1) // Jika nilai = 1 Saklar Dimatikan
  {
    digitalWrite(Relay4, HIGH);
    Serial.println("light 4 OFF");
  }
}

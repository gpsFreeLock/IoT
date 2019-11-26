//#include <SPI.h>
#include <MFRC522.h>
#include <FirebaseArduino.h> //Memasukan Lib Firebase (Basis Arduino)
#include <ESP8266WiFi.h>
#include <Servo.h>

#define SS_PIN 15
#define RST_PIN 0

#define ERROR_PIN 4
#define SUCCESS_PIN 5
#define CONN_PIN 5

int A, B, C, D, E, F, G, H, I, J; //UID Variabel
int S1, S2, S3, S4, S5, S6, S7, S8, S9, S0; //Variabel State Pengguna

#define FIREBASE_HOST "kanggara101.firebaseio.com" //Database Config
#define FIREBASE_AUTH "Clw7sePLvWSbAP4oH7dt2FAVWouWnPEhdglbc9JA"

const char *ssid = "HiMaTe16";
const char *password = "klapankali";

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myservo;

void setup() {
  delay(1000);
  myservo.attach(2);  // attaches the servo on GIO2 to the servo object
  myservo.write(5);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(CONN_PIN, OUTPUT);
  pinMode(SUCCESS_PIN, OUTPUT);
  pinMode(ERROR_PIN, OUTPUT);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("IoT/L5", "A");
  SPI.begin();
  mfrc522.PCD_Init();
}

void firebasereconnect()
{
  Serial.println("Trying to reconnect"); //menghubungkan kembali jika perangkat gagal terhubung ke firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void(* resetFunc) (void) = 0;

void AmbilData(int code){
  A = Firebase.getString("RFID/UID/0").toInt(); //membaca nilai yang ada pada L1
  B = Firebase.getString("RFID/UID/1").toInt(); //membaca nilai yang ada pada L1
  C = Firebase.getString("RFID/UID/2").toInt(); //membaca nilai yang ada pada L1
  D = Firebase.getString("RFID/UID/3").toInt(); //membaca nilai yang ada pada L1
  E = Firebase.getString("RFID/UID/4").toInt(); //membaca nilai yang ada pada L1
  F = Firebase.getString("RFID/UID/5").toInt(); //membaca nilai yang ada pada L1
  G = Firebase.getString("RFID/UID/6").toInt(); //membaca nilai yang ada pada L1
  H = Firebase.getString("RFID/UID/7").toInt(); //membaca nilai yang ada pada L1
  I = Firebase.getString("RFID/UID/8").toInt(); //membaca nilai yang ada pada L1
  J = Firebase.getString("RFID/UID/9").toInt(); //membaca nilai yang ada pada L1
  S1 = Firebase.getString("RFID/UID/1").toInt(); //membaca nilai yang ada pada L1
  S2 = Firebase.getString("RFID/UID/2").toInt(); //membaca nilai yang ada pada L1
  S3 = Firebase.getString("RFID/UID/3").toInt(); //membaca nilai yang ada pada L1
  S4 = Firebase.getString("RFID/UID/4").toInt(); //membaca nilai yang ada pada L1
  S5 = Firebase.getString("RFID/UID/5").toInt(); //membaca nilai yang ada pada L1
  S6 = Firebase.getString("RFID/UID/6").toInt(); //membaca nilai yang ada pada L1
  S7 = Firebase.getString("RFID/UID/7").toInt(); //membaca nilai yang ada pada L1
  S8 = Firebase.getString("RFID/UID/8").toInt(); //membaca nilai yang ada pada L1
  S9 = Firebase.getString("RFID/UID/9").toInt(); //membaca nilai yang ada pada L1
  
  
  if (code == A)
  {
    berhasil();
  }
  else if (code == B)
  {
    berhasil();
  }
  else if (code == C)
  {
    berhasil();
  }
  else if (code == D)
  {
    berhasil();
  }
  else if (code == E)
  {
    berhasil();
  }
  else if (code == F)
  {
    berhasil();
  }
  else if (code == G)
  {
    berhasil();
  }
  else if (code == H)
  {
    berhasil();
  }
  else if (code == I)
  {
    berhasil();
  }
  else
  {
   buzzer();
  }
}

void berhasil()
{
  digitalWrite(SUCCESS_PIN, HIGH);
  tone(16, 20000, 500);
  delay(500);
  buka();
  delay(1500);
  tutup();
  digitalWrite(ERROR_PIN, HIGH);
}

void kirimData(int UID) {
  if (WiFi.status() == WL_CONNECTED)
  {
    tone(16, 5000, 500);
    String postData = "UID= " + String(UID);
    Firebase.pushString("RFID/PUSH/", String(UID));
    Serial.println(UID);
    Serial.println(postData);
  }
}

void loop() {
  if ( mfrc522.PICC_IsNewCardPresent()) {
    if ( mfrc522.PICC_ReadCardSerial()) {
      int code = 0;
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        code = ((code + mfrc522.uid.uidByte[i]) * 2);
      }
      kirimData(code); //Memanggil fungsi kirimData();
      AmbilData(code);
      if (Firebase.failed())
      {
        Serial.print("setting number failed:");
        Serial.println(Firebase.error());
        resetFunc();
        return;
      }
  delay (500);
  digitalWrite(SUCCESS_PIN, HIGH);
  digitalWrite(ERROR_PIN, LOW);
  }
 }
}

void buka()
{
  int x;
  Serial.println("Membuka Pagar");
  for (x = 10; x <= 100; x++)
  {
    myservo.write(x); delay(10);
  }
  myservo.write(100); delay(10);
}

void tutup()
{
  int i;
  Serial.println("Menutup Pagar");
  for (i = 100; i >= 10; i--)
  {
    myservo.write(i); delay(10);
  }
  myservo.write(10); delay(10);
}

void buzzer()
{
  digitalWrite(ERROR_PIN, HIGH);
  tone(16, 100, 300);
  delay(300);
  tone(16, 1000, 300);
}

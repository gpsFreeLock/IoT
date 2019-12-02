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
int Q, R, S, T, U, V, W, X, Y, Z; //Variabel State Pengguna

#define FIREBASE_HOST "kanggara101.firebaseio.com" //Database Config
#define FIREBASE_AUTH "Clw7sePLvWSbAP4oH7dt2FAVWouWnPEhdglbc9JA"

const char *ssid = "iPhone";
const char *password = "empatbelas";

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
  Ready();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
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
  A = Firebase.getString("RFID/UID/0").toInt(); //membaca nilai yang ada pada UID/0
  B = Firebase.getString("RFID/UID/1").toInt(); //membaca nilai yang ada pada UID/1
  C = Firebase.getString("RFID/UID/2").toInt(); //membaca nilai yang ada pada UID/2
  D = Firebase.getString("RFID/UID/3").toInt(); //membaca nilai yang ada pada UID/3
  E = Firebase.getString("RFID/UID/4").toInt(); //membaca nilai yang ada pada UID/4
  F = Firebase.getString("RFID/UID/5").toInt(); //membaca nilai yang ada pada UID/5
  G = Firebase.getString("RFID/UID/6").toInt(); //membaca nilai yang ada pada UID/6
  H = Firebase.getString("RFID/UID/7").toInt(); //membaca nilai yang ada pada UID/7
  I = Firebase.getString("RFID/UID/8").toInt(); //membaca nilai yang ada pada UID/8
  J = Firebase.getString("RFID/UID/9").toInt(); //membaca nilai yang ada pada UID/9
  Q = Firebase.getString("RFID/S/0").toInt(); //membaca nilai State pada S/0
  R = Firebase.getString("RFID/S/1").toInt(); //membaca nilai State pada S/1
  S = Firebase.getString("RFID/S/2").toInt(); //membaca nilai State pada S/2
  T = Firebase.getString("RFID/S/3").toInt(); //membaca nilai State pada S/3
  U = Firebase.getString("RFID/S/4").toInt(); //membaca nilai State pada S/4
  V = Firebase.getString("RFID/S/5").toInt(); //membaca nilai State pada S/5
  W = Firebase.getString("RFID/S/6").toInt(); //membaca nilai State pada S/6
  X = Firebase.getString("RFID/S/7").toInt(); //membaca nilai State pada S/7
  Y = Firebase.getString("RFID/S/8").toInt(); //membaca nilai State pada S/8
  Z = Firebase.getString("RFID/S/9").toInt(); //membaca nilai State pada S/9
  
       if (code == A && Q == 0 )
  {
    berhasil();
    Serial.println("Pengguna A Memasuki Wilayah");
    Firebase.setString("RFID/S/0", "1");
  }
  else if (code == A && Q == 1 )
  {
    berhasil();
    Serial.println("Pengguna A Keluar Wilayah");
    Firebase.setString("RFID/S/0", "0");
  }
  else if (code == B && R == 0 )
  {
    berhasil();
    Serial.println("Pengguna B Memasuki Wilayah");
    Firebase.setString("RFID/S/1", "1");
  }
  else if (code == B && R == 1 )
  {
    berhasil();
    Serial.println("Pengguna B Keluar Wilayah");
    Firebase.setString("RFID/S/1", "0");
  }
  else if (code == C && S == 0 )
  {
    berhasil();
    Serial.println("Pengguna C Memasuki Wilayah");
    Firebase.setString("RFID/S/2", "1");
  }
  else if (code == C && S == 1 )
  {
    berhasil();
    Serial.println("Pengguna C Keluar Wilayah");
    Firebase.setString("RFID/S/2", "0");
  }
  else if (code == D && T == 0 )
  {
    berhasil();
    Serial.println("Pengguna D Memasuki Wilayah");
    Firebase.setString("RFID/S/3", "1");
  }
  else if (code == D && T == 1 )
  {
    berhasil();
    Serial.println("Pengguna D Keluar Wilayah");
    Firebase.setString("RFID/S/3", "0");
  }
  else if (code == E && U == 0 )
  {
    berhasil();
    Serial.println("Pengguna E Memasuki Wilayah");
    Firebase.setString("RFID/S/4", "1");
  }
  else if (code == E && U == 1 )
  {
    berhasil();
    Serial.println("Pengguna E Keluar Wilayah");
    Firebase.setString("RFID/S/4", "0");
  }
  else if (code == F && V == 0 )
  {
    berhasil();
    Serial.println("Pengguna F Memasuki Wilayah");
    Firebase.setString("RFID/S/5", "1");
  }
  else if (code == F && V == 1 )
  {
    berhasil();
    Serial.println("Pengguna F Keluar Wilayah");
    Firebase.setString("RFID/S/5", "0");
  }
  else if (code == G && W == 0 )
  {
    berhasil();
    Serial.println("Pengguna G Memasuki Wilayah");
    Firebase.setString("RFID/S/6", "1");
  }
  else if (code == G && W == 1 )
  {
    berhasil();
    Serial.println("Pengguna G Keluar Wilayah");
    Firebase.setString("RFID/S/6", "0");
  }
  else if (code == H && X == 0 )
  {
    berhasil();
    Serial.println("Pengguna H Memasuki Wilayah");
    Firebase.setString("RFID/S/7", "1");
  }
  else if (code == H && X == 1 )
  {
    berhasil();
    Serial.println("Pengguna H Keluar Wilayah");
    Firebase.setString("RFID/S/7", "0");
  }
  else if (code == I && Y == 0 )
  {
    berhasil();
    Serial.println("Pengguna I Memasuki Wilayah");
    Firebase.setString("RFID/S/8", "1");
  }
  else if (code == I && Y == 1 )
  {
    berhasil();
    Serial.println("Pengguna I Keluar Wilayah");
    Firebase.setString("RFID/S/8", "0");
  }
  else if (code == J && Z == 0 )
  {
    berhasil();
    Serial.println("Pengguna J Memasuki Wilayah");
    Firebase.setString("RFID/S/9", "1");
  }
  else if (code == J && Z == 1 )
  {
    berhasil();
    Serial.println("Pengguna J Keluar Wilayah");
    Firebase.setString("RFID/S/9", "0");
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

void Ready()
{
  #define NOTE_C4  262
  #define NOTE_G3  196
  #define NOTE_A3  220
  #define NOTE_B3  247  
  int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};
  int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

  for (int thisNote = 0; thisNote < 8; thisNote++) 
  {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(16, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
  digitalWrite(SUCCESS_PIN, HIGH);
  digitalWrite(ERROR_PIN, LOW);
}

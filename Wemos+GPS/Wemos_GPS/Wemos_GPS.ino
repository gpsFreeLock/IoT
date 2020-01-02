#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

TinyGPSPlus gps;  // The TinyGPS++ object

SoftwareSerial ss(12, 13); // The serial connection to the GPS device

const char* ssid = "KAnggara75";
const char* password = "klapankali";

float latitude, longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;

WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop()
{
 while (ss.available() >0) 
 {
  if (gps.encode(ss.read())) 
  info();
 }
}

void info()
{
  if(gps.location.isUpdated()) 
  {
   latitude = gps.location.lat();
   Serial.println(gps.location.lat(), 6);
   lat_str = String(latitude, 6);
   longitude = gps.location.lng();
   Serial.println(gps.location.lng(), 6);
   lng_str = String(longitude, 6);
  }

  if (gps.time.isValid())
  {
   time_str = "";
   hour = gps.time.hour();
   minute = gps.time.minute();
   second = gps.time.second();

   minute = (minute);
   if (minute > 59)
   {
    minute = minute - 60;
    hour = hour + 1;
   }
   hour = (hour + 7) ;
   if (hour > 23)
   hour = hour - 24;

   if (hour < 10)
   time_str = '0';
   time_str += String(hour);
   Serial.print(hour);
   Serial.print(":");

   time_str += " : ";

   if (minute < 10)
   time_str += '0';
   time_str += String(minute);
   Serial.print(minute);
   Serial.print(":");

   time_str += " : ";

   if (second < 10)
   time_str += '0';
   time_str += String(second);
   Serial.print(second);
   Serial.print("   ");
  }

  
  if (gps.date.isValid())
  {
   date_str = "";
   date = gps.date.day();
   month = gps.date.month();
   year = gps.date.year();

   if (date < 10)
   date_str = '0';
   date_str += String(date);
   Serial.print(date);
   Serial.print("/");

   date_str += " / ";

   if (month < 10)
   date_str += '0';
   date_str += String(month);
   Serial.print(month);
   Serial.print("/");
   date_str += " / ";

   if (year < 10)
   date_str += '0';
   date_str += String(year);
   Serial.println(year);
  }

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>GPS Interfacing with Wemos D1 Mini</title> <style>";
  s += "a:link {background-color: lightblue;text-decoration: none;}";
  s += "table, th, td {border: 1px solid black;} </style> </head> <body> <h1  style=";
  s += "font-size:300%;";
  s += " ALIGN=CENTER> GPS Interfacing with NodeMCU</h1>";
  s += "<p ALIGN=CENTER style=""font-size:150%;""";
  s += "> <b>Location Details</b></p> <table ALIGN=CENTER style=";
  s += "width:50%";
  s += "> <tr> <th>Latitude</th>";
  s += "<td ALIGN=CENTER >";
  s += String(latitude, 6);
  s += "</td> </tr> <tr> <th>Longitude</th> <td ALIGN=CENTER >";
  s += String(longitude, 6);
  s += "</td> </tr> <tr>  <th>Date</th> <td ALIGN=CENTER >";
  s += date_str;
  s += "</td></tr> <tr> <th>Time</th> <td ALIGN=CENTER >";
  s += time_str;
  s += "</td>  </tr> </table> ";
 
  
  if (gps.location.isUpdated())
  {
    s += "<p align=center><a style=""color:RED;font-size:125%;"" href=""http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
    s += lat_str;
    s += "+";
    s += lng_str;
    s += """ target=""_top"">Click here!</a> To check the location in Google maps.</p>";
  }

  s += "</body> </html> \n";

  client.print(s);
  delay(1500);
}

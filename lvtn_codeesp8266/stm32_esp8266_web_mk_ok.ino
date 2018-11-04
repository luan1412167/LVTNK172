#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <dummy.h>
#include <stdint.h>
#include <stdio.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h> 

MDNSResponder mdns;
ESP8266WebServer server(80);
const char* ssid = "luan1412167";
const char* passphrase = "0981867669";
const char* SSID_EEPROM = "BKGPL";
const char* PASSWORD_EEPROM = "bkgpl2016";
const char* host = "112.213.89.26";
String st;
String content;
int statusCode;
float CongsuatP1,CongsuatP2,CongsuatP3,Nangluong,DienapP1,DienapP2,DienapP3,DongdienP1,DongdienP2,DongdienP3,f ;
char  Buffer[40];
char  CongSuatP1[4],CongSuatP2[4],CongSuatP3[4];
char  NangLuong[4];
char  DienApP1[4],DienApP2[4],DienApP3[4];
char  DongDienP1[4],DongDienP2[4],DongDienP3[4];
String esid ;
String epass ;
void EEPROM_ESP8266_write(String buffer, int N) {
  EEPROM.begin(512); delay(10);
  for (int L = 0; L < 32; ++L) {
    EEPROM.write(N + L, buffer[L]);
  }
  EEPROM.commit();
}
void setup() {
  pinMode(D9, INPUT);
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(10);
//EEPROM_ESP8266_write(SSID_EEPROM, 0); 
//EEPROM_ESP8266_write(PASSWORD_EEPROM, 32);
  Serial.println();
  Serial.println();
  Serial.println("Startup");
  
  // read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");

  for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");

  for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
  Serial.print("PASS: ");
  Serial.println(epass);  
  
  if ( esid.length() > 1 ) {
      WiFi.begin(esid.c_str(), epass.c_str());
      if (testWifi()) {
        launchWeb(0);
        return;
      } 
   setupAP();
  }
 
}

bool testWifi(void) {
  int c = 0;
  Serial.println("Waiting for Wifi to connect");  
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) { return true; } 
    delay(500);
    Serial.print(WiFi.status());    
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
} 

void launchWeb(int webtype) {
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer(webtype);
  // Start the server
  server.begin();
  Serial.println("Server started"); 
}

void setupAP(void) {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
     {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
     }
  }
  Serial.println(""); 
  st = "<ol>";
  for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      st += "<li>";
      st += WiFi.SSID(i);
      st += " (";
      st += WiFi.RSSI(i);
      st += ")";
      st += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*";
      st += "</li>";
    }
  st += "</ol>";
  delay(100);
  Serial.println(ssid);
  Serial.println(passphrase);
  WiFi.softAP(ssid, passphrase, 6);
  Serial.println("softap");
  launchWeb(1);
  Serial.println("over");
}

void createWebServer(int webtype)
{ Serial.println("webtype");
  mdns.update();
  if ( webtype == 1 ) {
     Serial.println("=");
    server.on("/", []() {
      Serial.println("0104");
        IPAddress ip = WiFi.softAPIP();
        String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
        content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
        content += ipStr;
        content += "<p>";
        content += st;
        content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
        content += "</html>";
        server.send(200, "text/html", content); 
    });
    server.on("/setting", []() {
        String qsid = server.arg("ssid");
        String qpass = server.arg("pass");
        if (qsid.length() > 0 && qpass.length() > 0) {
          Serial.println("clearing eeprom");
          for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
          Serial.println(qsid);
          Serial.println("");
          Serial.println(qpass);
          Serial.println("");
            
          Serial.println("writing eeprom ssid:");
          for (int i = 0; i < qsid.length(); ++i)
            {
              EEPROM.write(i, qsid[i]);
              Serial.print("Wrote: ");
              Serial.println(qsid[i]); 
            }
          Serial.println("writing eeprom pass:"); 
          for (int i = 0; i < qpass.length(); ++i)
            {
              EEPROM.write(32+i, qpass[i]);
              Serial.print("Wrote: ");
              Serial.println(qpass[i]); 
            }    
          EEPROM.commit();
          content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
          statusCode = 200;
        } else {
          content = "{\"Error\":\"404 not found\"}";
          statusCode = 404;
          Serial.println("Sending 404");
        }
        server.send(statusCode, "application/json", content);
    });
  } else if (webtype == 0) {
    server.on("/", []() {
      IPAddress ip = WiFi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      server.send(200, "application/json", "{\"IP\":\"" + ipStr + "\"}");
    });
    server.on("/cleareeprom", []() {
      content = "<!DOCTYPE HTML>\r\n<html>";
      content += "<p>Clearing the EEPROM</p></html>";
      server.send(200, "text/html", content);
      Serial.println("clearing eeprom");
      for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
      EEPROM.commit();
    });
  }
}
void readEEPROM(void)
{
  
  for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
  for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
  Serial.print("PASS: ");
  Serial.println(epass);  
  Serial.println("Reading EEPROM ssid");
  }

void Receivedata(void){
    Serial.println(" Receive data from Serial");
    while (Serial.available()<40) {} 
    for(int n=0; n<40; n++)
    {
    Buffer[n] = Serial.read();
    }
    
     for(int i=0;i<4;i++){
      DienApP1[i]=Buffer[i];
      DienApP2[i]=Buffer[i+4];
      DienApP3[i]=Buffer[i+8];
      DongDienP1[i]=Buffer[i+12];
      DongDienP2[i]=Buffer[i+16];
      DongDienP3[i]=Buffer[i+20];
      CongSuatP1[i]=Buffer[i+24];
      CongSuatP2[i]=Buffer[i+28];
      CongSuatP3[i]=Buffer[i+32];
      NangLuong[i]=Buffer[i+36];
      }
  //sscanf(string, "%x", &num); 
  DienapP1 = *((float*)&DienApP1);
  DienapP2 = *((float*)&DienApP2);
  DienapP3 = *((float*)&DienApP3); 
  DongdienP1 = *((float*)&DongDienP1);
  DongdienP2 = *((float*)&DongDienP2);
  DongdienP3 = *((float*)&DongDienP3);
  CongsuatP1 = *((float*)&CongSuatP1);
  CongsuatP2 = *((float*)&CongSuatP2);
  CongsuatP3 = *((float*)&CongSuatP3);
  Nangluong = *((float*)&NangLuong);
  Serial.printf("Congsuat1 =  %.3f \n", CongsuatP1); 
  Serial.printf("Congsuat2 =  %.3f \n", CongsuatP2);
  Serial.printf("Congsuat3 =  %.3f \n", CongsuatP3);   
  Serial.printf("Dienap1 =  %.3f \n", DienapP1); 
  Serial.printf("Dienap2 =  %.3f \n", DienapP2);
  Serial.printf("Dienap3 =  %.3f \n", DienapP3);
  Serial.printf("Dongdien1=  %.3f \n", DongdienP1);
  Serial.printf("Dongdien2=  %.3f \n", DongdienP2);
  Serial.printf("Dongdien3=  %.3f \n", DongdienP3); 
  Serial.printf("Nangluong =  %.3f \n", Nangluong); 

  
  }
  void senddata(void){
    WiFiClient client;
    Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");
    while (client.connected())
    {   
    client.print("GET /lvtn_write_data_congsuatP1.php?"); 
    client.print("value="); 
    client.printf("%.2f",CongsuatP1); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com"); 
    client.println();
    client.print("GET /lvtn_write_data_nangluong.php?"); 
    client.print("value="); 
    client.printf("%.2f",Nangluong); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com");
    client.println();
    client.stop();
    }
  }
  if (client.connect(host, 80))
  { Serial.println("connected]");
    while (client.connected()){
    client.print("GET /lvtn_write_data_dongdienP1.php?"); 
    client.print("value="); 
    client.printf("%.2f",DongdienP1); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com");
    client.println();
    client.print("GET /lvtn_write_data_dienapP1.php?"); 
    client.print("value="); 
    client.printf("%.2f",DienapP1); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com"); 
    client.println("Connection: close");
    client.println();
    client.stop();
    
    } 
  }
  if (client.connect(host, 80))
  { Serial.println("connected]");
    while (client.connected()){
    client.print("GET /lvtn_write_data_dongdienP2.php?"); 
    client.print("value="); 
    client.printf("%.2f",DongdienP2); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com");
    client.println();
    client.print("GET /lvtn_write_data_dienapP2.php?"); 
    client.print("value="); 
    client.printf("%.2f",DienapP2); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com"); 
    client.println("Connection: close");
    client.println();
    client.stop();
    
    } 
  }
  if (client.connect(host, 80))
  { Serial.println("connected]");
    while (client.connected()){
    client.print("GET /lvtn_write_data_dongdienP3.php?"); 
    client.print("value="); 
    client.printf("%.2f",DongdienP3); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com");
    client.println();
    client.print("GET /lvtn_write_data_dienapP3.php?"); 
    client.print("value="); 
    client.printf("%.2f",DienapP3); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com"); 
    client.println("Connection: close");
    client.println();
    client.stop();
    
    } 
  }
  if (client.connect(host, 80))
  { Serial.println("connected]");
    while (client.connected()){
    client.print("GET /lvtn_write_data_congsuatP2.php?"); 
    client.print("value="); 
    client.printf("%.2f",CongsuatP2); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com");
    client.println();
    client.print("GET /lvtn_write_data_congsuatP3.php?"); 
    client.print("value="); 
    client.printf("%.2f",CongsuatP3); 
    client.println(" HTTP/1.1"); 
    client.println("Host: trancongbinh.com"); 
    client.println("Connection: close");
    client.println();
    client.stop();
    Serial.println("\n[Disconnected]");
    } 
  }
  else
  {
    Serial.println("connection failed!");
    client.stop();
  }
    
  }

void loop() {
  for(int i=0;i<10000;i++){
  server.handleClient();
 
  }
  Receivedata();
  senddata();
  Serial.println("done");
  
}

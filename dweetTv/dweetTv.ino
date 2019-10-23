#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

//*-- Hardware Serial
#define _baudrate 115200

//*-- IoT Information
#define SSID "8fTomato"
#define PASS "qqwwee--"
#define HOST "dweet.io" // ThingSpeak IP Address: 184.106.153.149
#define PORT 80
#define READAPIKEY "READAPIKEY012345" // READ APIKEY for the CHANNEL_ID

uint16_t pw[] = {2650, 800, 500, 350, 500, 400, 450, 850, 500, 800, 1300, 850, 500, 350, 500, 350, 500, 400, 450, 400, 450, 400, 450, 450, 450, 400, 900, 800, 950, 800, 500, 350, 500, 400, 450, 400, 500, 350, 500, 350, 950, 800, 500, 350, 950, 350, 450, 850, 500, 350, 500, 400, 450, 400, 450, 400, 900, 400, 450, 850, 450, 400, 500};
uint16_t ok[] = {2600, 850, 450, 400, 450, 450, 450, 850, 450, 800, 1350, 850, 450, 400, 450, 400, 450, 450, 450, 400, 450, 400, 450, 400, 500, 400, 850, 850, 900, 850, 450, 400, 450, 400, 500, 400, 900, 800, 900, 850, 500, 350, 900, 400, 450, 850, 450, 400, 950, 800, 900, 400, 450, 400, 500, 800, 450, 400, 450};
uint16_t udo[] = {2650, 800, 500, 350, 500, 350, 550, 800, 500, 750, 1350, 800, 500, 400, 450, 400, 450, 400, 500, 400, 450, 400, 500, 350, 500, 400, 900, 800, 950, 800, 450, 400, 450, 400, 450, 400, 500, 400, 450, 400, 900, 850, 450, 400, 950, 350, 500, 800, 500, 350, 500, 350, 450, 450, 450, 400, 900, 800, 900, 850, 450};
uint16_t p1[] = {2600, 850, 450, 400, 500, 400, 450, 850, 450, 850, 1300, 850, 450, 400, 500, 350, 500, 400, 450, 400, 450, 400, 500, 400, 450, 400, 900, 800, 900, 850, 500, 350, 500, 400, 450, 400, 450, 400, 450, 400, 950, 800, 450, 400, 900, 400, 450, 850, 450, 400, 500, 400, 450, 400, 450, 400, 500, 400, 450, 400, 450, 400, 950};
uint16_t p2[] = {2650, 800, 500, 400, 450, 400, 500, 800, 500, 800, 1350, 800, 500, 350, 500, 350, 500, 400, 500, 350, 500, 350, 500, 400, 450, 400, 900, 850, 900, 800, 500, 350, 500, 400, 450, 400, 900, 850, 900, 800, 500, 350, 900, 400, 500, 800, 500, 350, 500, 400, 450, 400, 500, 350, 500, 400, 450, 400, 900, 800, 500};
uint16_t p3[] = {2650, 800, 500, 400, 500, 350, 500, 800, 450, 850, 1350, 800, 450, 400, 450, 400, 500, 400, 450, 400, 450, 400, 500, 400, 450, 400, 900, 850, 900, 800, 500, 350, 550, 350, 500, 350, 500, 350, 550, 350, 900, 800, 450, 400, 900, 400, 500, 800, 500, 400, 450, 400, 450, 400, 450, 450, 450, 400, 450, 400, 900, 400, 450};
uint16_t p4[] = {2650, 800, 500, 400, 450, 400, 500, 800, 450, 850, 1350, 800, 500, 350, 550, 350, 500, 350, 550, 300, 550, 350, 500, 350, 500, 350, 950, 800, 900, 800, 500, 400, 450, 400, 450, 400, 900, 850, 900, 800, 500, 400, 900, 350, 550, 750, 550, 350, 500, 350, 550, 300, 550, 350, 500, 350, 950, 800, 450, 400, 450};
uint16_t p5[] = {2600, 850, 450, 400, 500, 350, 500, 850, 450, 800, 1400, 750, 450, 450, 450, 400, 450, 400, 450, 450, 450, 400, 450, 400, 450, 450, 850, 850, 900, 850, 450, 400, 500, 350, 500, 350, 500, 400, 450, 400, 900, 850, 450, 400, 900, 400, 450, 850, 450, 400, 450, 400, 450, 450, 450, 400, 450, 400, 950, 800, 900};
uint16_t p6[] = {2600, 800, 500, 400, 450, 400, 450, 850, 500, 800, 1350, 800, 450, 400, 550, 350, 500, 350, 450, 400, 450, 450, 450, 400, 450, 400, 900, 850, 900, 800, 500, 400, 500, 350, 500, 350, 950, 800, 850, 850, 450, 450, 850, 400, 500, 800, 500, 400, 450, 400, 500, 350, 500, 350, 550, 350, 950, 350, 500, 800, 500};
uint16_t p7[] = {2600, 850, 450, 450, 450, 400, 450, 850, 450, 850, 1300, 850, 450, 400, 450, 400, 500, 400, 450, 400, 500, 350, 500, 400, 450, 400, 850, 850, 900, 850, 450, 400, 450, 450, 450, 400, 450, 400, 450, 450, 850, 850, 500, 350, 900, 400, 450, 850, 450, 400, 450, 450, 450, 400, 450, 400, 500, 400, 850, 450, 450, 400, 450};
uint16_t p8[] = {2600, 850, 450, 400, 450, 400, 500, 850, 450, 800, 1350, 800, 500, 400, 450, 400, 450, 400, 450, 450, 450, 400, 500, 350, 450, 400, 900, 850, 900, 850, 450, 400, 450, 400, 500, 350, 950, 800, 900, 800, 500, 400, 850, 450, 450, 850, 450, 400, 450, 400, 450, 400, 500, 400, 850, 850, 450, 450, 450, 400, 450};
uint16_t p9[] = {2600, 900, 450, 400, 450, 400, 450, 850, 450, 850, 1350, 800, 450, 450, 450, 400, 450, 400, 450, 450, 450, 400, 450, 400, 450, 450, 850, 850, 850, 850, 450, 450, 400, 450, 450, 400, 450, 400, 500, 400, 900, 850, 450, 400, 850, 400, 450, 850, 450, 450, 400, 450, 450, 400, 450, 400, 900, 900, 450, 400, 850};
uint16_t p0[] = {2650, 800, 450, 400, 500, 400, 450, 850, 450, 850, 1300, 850, 450, 400, 450, 400, 500, 400, 450, 400, 450, 400, 450, 400, 500, 400, 900, 800, 950, 800, 500, 350, 500, 350, 500, 400, 850, 850, 900, 850, 450, 400, 900, 400, 450, 850, 500, 350, 450, 400, 500, 400, 500, 350, 500, 350, 550, 350, 500, 350, 450, 400, 450};

IRsend irsend(4); // Set the GPIO to be used to sending the message.
void setup()
{
  
  irsend.begin();
  Serial.begin(_baudrate);
  Serial.println("ESP8266 Ready!");
  // Connecting to a WiFi network
  Serial.print("Connect to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASS);
  
  // 持續等待並連接到指定的 WiFi SSID
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}

void loop()
{
  retrieveField(18795, 1); // filed_id=1 是 DHT11 的溫度值
}
WiFiClient client;
void retrieveField(uint32_t channel_id, uint8_t field_id)
{
  
  // 設定 ESP8266 作為 Client 端
  client.setNoDelay(true);
  if (!client.connect(HOST, PORT))
  {
    Serial.println("connection failed");
    return;
  }

  //Serial.println("**-- Get Last Entry in a Fiels Feed --**");
  String GET = "GET /get/latest/dweet/for/stanlykuasled3";
  String getStr = GET + " HTTP/1.1\r\n";
  client.print(getStr);
  client.print("Host: http://dweet.io\r\n");
  client.println(F("Cache-Control: no-cache")); //sometime crashes here
  client.print("Connection: keep-alive\r\n\r\n");
  //     client.print( "Connection: close\r\n\r\n" );
  delay(10);

  // 讀取所有從 ThingSpeak IoT Server 的回應並輸出到串列埠
  while (client.available() || client.connected())
  {
    
    String line = client.readStringUntil('\n');
    Serial.println("begin------------Get");
    Serial.println(line);
    if (line.substring(0, 1) == "{")
    {
      Serial.println(line);
      StaticJsonDocument<300> doc;
      //String json = "{\"this\":\"succeeded\",\"by\":\"getting\",\"the\":\"dweets\",\"with\":[{\"thing\":\"stanlykuasled3\",\"created\":\"2019-04-16T02:55:24.048Z\",\"content\":{\"temp\":321,\"wet\":1000}}]}";

      deserializeJson(doc, line);
      //const char *world1 = doc["the"];
      //const char *world2 = doc["this"];
      String tv = doc["with"][0]["content"]["tv"];
      String tvNum = doc["with"][0]["content"]["tvNum"];
      //--------------------------

      if (tv.indexOf("Y") > 0)
      {
        if (tvNum == "pw")
        {
          irsend.sendRaw(pw, 63, 36);
          delay(20);
          irsend.sendRaw(pw, 63, 38);
          delay(20);
          irsend.sendRaw(pw, 63, 37);
         

        }
        else if (tvNum == "99")
        {
          //Serial.println("---------in-------");
          
          pinMode(16,OUTPUT);
          digitalWrite(16,HIGH);
          delay(5000);  
          digitalWrite(16,LOW);
          delay(1000);  
          pinMode(16,INPUT);
        }
        else if (tvNum == "0")
        {
          irsend.sendRaw(ok, 59, 36);
          delay(20);
          irsend.sendRaw(ok, 59, 38);
          delay(20);
          irsend.sendRaw(ok, 59, 37);
        }
        else if (tvNum == "1")
        {
          irsend.sendRaw(udo, 61, 36);
          delay(20);
          irsend.sendRaw(udo, 61, 38);
          delay(20);
          irsend.sendRaw(udo, 61, 37);
        }
        else
        {
          //Serial.println(line);
          for (int i = 0; i < tvNum.length(); i++)
          {
            pressNum(tvNum[i]);
            delay(800);
            Serial.println(tvNum + "--Press---");
          }
          // irsend.sendRaw(ok, 59, 36);
          // delay(20);
          // irsend.sendRaw(ok, 59, 38);
          // delay(20);
          // irsend.sendRaw(ok, 59, 37);
          
          
        }
        GET = "GET /dweet/for/stanlykuasled3?tv=N";
          String getStr = GET + " HTTP/1.1\r\n";
          client.print(getStr);
          client.print("Host: http://dweet.io\n");
          client.print("Connection: close\r\n\r\n");
          client.flush();
          client.stopAll();
      }
      //Serial.println("closing connection");
      //Serial.flush();
      delay(1000);
      return;
    }
  }
}

void pressNum(char tvNum)
{
  if (tvNum == '0')
  {
    //led(0,1,0);
    irsend.sendRaw(p0, 63, 36);

    delay(20);
    irsend.sendRaw(p0, 63, 38);
    delay(20);
    irsend.sendRaw(p0, 63, 37);
  }
  else if (tvNum == '1')
  {
    irsend.sendRaw(p1, 63, 36);
    delay(20);
    irsend.sendRaw(p1, 63, 38);

    delay(20);
    irsend.sendRaw(p1, 63, 37);
  }
  else if (tvNum == '2')
  {
    irsend.sendRaw(p2, 61, 36);
    delay(20);
    irsend.sendRaw(p2, 61, 38);
    delay(20);
    irsend.sendRaw(p2, 61, 37);
    delay(10);
    irsend.sendRaw(p2, 61, 38);
  }
  else if (tvNum == '3')
  {
    irsend.sendRaw(p3, 63, 38);
    delay(20);
    irsend.sendRaw(p3, 63, 38);
    delay(20);
    irsend.sendRaw(p3, 63, 38);
    delay(10);
    irsend.sendRaw(p3, 63, 38);
  }
  else if (tvNum == '4')
  {
    irsend.sendRaw(p4, 61, 36);
    delay(20);
    irsend.sendRaw(p4, 61, 38);

    delay(20);
    irsend.sendRaw(p4, 61, 37);
  }
  else if (tvNum == '5')
  {

    irsend.sendRaw(p5, 61, 36);
    delay(20);
    irsend.sendRaw(p5, 61, 38);

    delay(20);
    irsend.sendRaw(p5, 61, 37);
  }
  else if (tvNum == '6')
  {

    irsend.sendRaw(p6, 61, 36);
    delay(20);
    irsend.sendRaw(p6, 61, 38);

    delay(20);
    irsend.sendRaw(p6, 61, 37);
  }
  else if (tvNum == '7')
  {

    irsend.sendRaw(p7, 63, 36);
    delay(20);
    irsend.sendRaw(p7, 63, 38);

    delay(20);
    irsend.sendRaw(p7, 63, 37);
  }
  else if (tvNum == '8')
  {

    irsend.sendRaw(p8, 61, 36);
    delay(20);
    irsend.sendRaw(p8, 61, 38);

    delay(20);
    irsend.sendRaw(p8, 61, 37);
  }
  else if (tvNum == '9')
  {

    irsend.sendRaw(p9, 61, 36);
    delay(20);
    irsend.sendRaw(p9, 61, 38);

    delay(20);
    irsend.sendRaw(p9, 61, 37);
  }
}

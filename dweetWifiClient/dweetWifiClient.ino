#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

//*-- Hardware Serial
#define _baudrate   115200

//*-- IoT Information
#define SSID        "8fTomato"
#define PASS        "qqwwee--"
#define HOST        "dweet.io" // ThingSpeak IP Address: 184.106.153.149
#define PORT        80
#define READAPIKEY  "READAPIKEY012345"  // READ APIKEY for the CHANNEL_ID

IRsend irsend(4);  // Set the GPIO to be used to sending the message.
void setup() {
  irsend.begin();
  Serial.begin( _baudrate );
  Serial.println( "ESP8266 Ready!" );
  // Connecting to a WiFi network
  Serial.print("Connect to ");
  Serial.println( SSID );
  WiFi.begin( SSID, PASS );

  // 持續等待並連接到指定的 WiFi SSID
  while ( WiFi.status() != WL_CONNECTED )
  {
    delay(500);
    Serial.print( "." );
  }
  Serial.println( "" );

  Serial.println( "WiFi connected" );
  Serial.println( "IP address: " );
  Serial.println( WiFi.localIP() );
  Serial.println( "" );

  //String json = "{\"this\":\"succeeded\",\"by\":\"getting\",\"the\":\"dweets\",\"with\":[{\"thing\":\"stanlykuasled\",\"created\":\"2019-04-16T02:55:24.048Z\",\"content\":{\"temp\":321,\"wet\":1000}}]}";
  //StaticJsonDocument<200> doc;


}

void loop() {
  // 每隔多久取一次資料
  retrieveField( 18795, 1 );  // filed_id=1 是 DHT11 的溫度值
  // ms
}

void retrieveField( uint32_t channel_id, uint8_t field_id )
{
   WiFiClient client;
  // 設定 ESP8266 作為 Client 端
  client.setNoDelay(true);
  if ( !client.connect( HOST, PORT ) )
  {
    Serial.println( "connection failed" );
    return;
  }
 
    Serial.println( "**-- Get Last Entry in a Fiels Feed --**" );
    String GET = "GET /get/latest/dweet/for/stanlykuasled" ;
    String getStr = GET + " HTTP/1.1\r\n";;
    client.print( getStr );
    client.print( "Host: https://dweet.io\r\n" );
    client.println(F("Cache-Control: no-cache")); //sometime crashes here
    client.print( "Connection: keep-alive\r\n\r\n" );
//     client.print( "Connection: close\r\n\r\n" );
    delay(100);
   
    
    // 讀取所有從 ThingSpeak IoT Server 的回應並輸出到串列埠
    while (client.available()||client.connected()) {
      
      String line = client.readStringUntil('\n');
      Serial.println("begin------------Get");
      Serial.println(line);
      if (line.substring(0, 1) == "{") {
        Serial.println("---in---");
        StaticJsonDocument<300> doc;
        //Serial.println(line);
        //String json = "{\"this\":\"succeeded\",\"by\":\"getting\",\"the\":\"dweets\",\"with\":[{\"thing\":\"stanlykuasled\",\"created\":\"2019-04-16T02:55:24.048Z\",\"content\":{\"temp\":321,\"wet\":1000}}]}";
        
        deserializeJson(doc, line);
        const char* world1 = doc["the"];
        const char* world2 = doc["this"];
        String temp = doc["with"][0]["content"]["temp"];
        String water = doc["with"][0]["content"]["water"];
        Serial.println(temp);
        Serial.println(water);
        //--------------------------
       

        if (water.indexOf("Y")>0) {
          irsend.sendNEC(0x20DF4EB1, 32);
          delay(50);
          irsend.sendNEC(0x20DF4EB1, 32);
          delay(50);
          irsend.sendNEC(0x20DF4EB1, 32);
          delay(1000);
//          //https://dweet.io/dweet/for/stanlykuasled?temp=28&hum=80
          GET = "GET /dweet/for/stanlykuasled?water=N&temp=80" ;
          Serial.println( "**-- Get Last Entry in a Fiels Feed --**" );
          String getStr = GET + " HTTP/1.1\r\n";;
          client.print( getStr );
          client.print( "Host: https://dweet.io\n" );
          
        }else{
           
          }
          client.print( "Connection: close\r\n\r\n" );
          //Serial.println();
      client.flush();
     client.stopAll();
     Serial.println("closing connection");
     Serial.flush();
      delay( 1000 );
          return;
      }
    }
    //  Serial.println();
    //  client.flush();
    //  client.stopAll();
    //  Serial.println("closing connection");
    //  Serial.flush();



    //  delay( 8000 );
    //client.print( "Connection: close\r\n\r\n" );
    //client.stop();
}

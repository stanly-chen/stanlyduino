#include <ESP8266WiFi.h>

//*-- Hardware Serial
#define _baudrate   9600

//*-- IoT Information
#define SSID        "8fTomato"
#define PASS        "qqwwee--"
#define HOST        "api.thingspeak.com" // ThingSpeak IP Address: 184.106.153.149
#define PORT        80
#define READAPIKEY  "READAPIKEY012345"  // READ APIKEY for the CHANNEL_ID

void setup() {
    Serial.begin( _baudrate );
    Serial.println( "ESP8266 Ready!" );
    // Connecting to a WiFi network
    Serial.print("Connect to ");
    Serial.println( SSID );
    WiFi.begin( SSID, PASS );

    // 持續等待並連接到指定的 WiFi SSID
    while( WiFi.status() != WL_CONNECTED )
    {
        delay(500);
        Serial.print( "." );
    }
    Serial.println( "" );

    Serial.println( "WiFi connected" );
    Serial.println( "IP address: " );
    Serial.println( WiFi.localIP() );
    Serial.println( "" );

}

void loop() {

    // 每隔多久取一次資料
    retrieveField( 18795, 1 );  // filed_id=1 是 DHT11 的溫度值
    delay( 20000 ); // ms
}

void retrieveField( uint32_t channel_id, uint8_t field_id )
{
    // 設定 ESP8266 作為 Client 端
    WiFiClient client;
    if( !client.connect( HOST, PORT ) )
    {
        Serial.println( "connection failed" );
        return;
    }
    else
    {
        ////// 使用 GET 取回最後一筆 FIELD_ID 資料 //////

        /*** Method 1: ***/
        //
        //-- Get a Channel Field Feed --//
        // To view a Channel's field feed, send an HTTP GET to 
        //
        //  https://api.thingspeak.com/channels/CHANNEL_ID/fields/FIELD_ID.json
        //----
        String GET = "GET /channels/" + String(channel_id) + "/fields/" + String(field_id) + ".json?key=" +
                     READAPIKEY + "&results=1";
        //----

        Serial.println( "**-- Get a Channel Fiels Feed --**" );
        String getStr = GET + " HTTP/1.1\r\n";;
        client.print( getStr );
        client.print( "Host: api.thingspeak.com\n" );
        client.print( "Connection: keep-alive\r\n\r\n" );
        
        delay(10);
        
        // 讀取所有從 ThingSpeak IoT Server 的回應並輸出到串列埠
        while(client.available())
        {
            String line = client.readStringUntil('\r');
            Serial.print(line);
        }

        /*** Method 2: ***/
        //
        //-- Get Last Entry in a Fiels Feed --//
        // To get the last entry in a Channel's field feed, send an HTTP GET to 
        //
        //  https://api.thingspeak.com/channels/CHANNEL_ID/fields/FIELD_ID/last.json
        //----
        GET = "GET /channels/" + String(channel_id) + "/fields/" + String(field_id) + 
                    "/last.json?key=" + READAPIKEY;
        //
        //----

        Serial.println( "**-- Get Last Entry in a Fiels Feed --**" );
        getStr = GET + " HTTP/1.1\r\n";;
        client.print( getStr );
        client.print( "Host: api.thingspeak.com\n" );
        client.print( "Connection: close\r\n\r\n" );
        
        delay(10);
        
        // 讀取所有從 ThingSpeak IoT Server 的回應並輸出到串列埠
        while(client.available())
        {
            String line = client.readStringUntil('\r');
            Serial.print(line);
        }
        client.stop();
    }
}

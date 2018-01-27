#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "Adafruit_TMP006.h"

Adafruit_TMP006 tmp006(0x41);  // start with a diferent i2c address!
#define WIFI_AP "ERTS LAB 304"
#define WIFI_PASSWORD "balstre403"

#define TOKEN "VU7ITc9VzIqaZDcnv8kE"
char thingsboardServer[] = "192.168.0.107";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message for topic ");
  Serial.print(topic);
  Serial.print("with length ");
  Serial.println(length);
  Serial.println("Message:");
  Serial.write(payload, length);
  Serial.println();
}

WiFiClient wifiClient;
PubSubClient client(thingsboardServer, 1883, callback, wifiClient);

//SoftwareSerial soft(2, 3); // RX, TX

int status = WL_IDLE_STATUS;
unsigned long lastSend;

void setup() 
{
  // initialize serial for debugging
  Serial.begin(115200);
  InitWiFi();
  //client.setServer(thingsboardServer, 1883 );
  lastSend = 0;
  if (! tmp006.begin()) {
    Serial.println("No sensor found");
    while (1);
    Serial.println("Temperature Sensor OK");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void InitWiFi()
{
  // initialize serial for ESP module
  //soft.begin(9600);
  
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(WIFI_AP);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    delay(500);
  }
  Serial.println("Connected to AP");
  printWifiStatus();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Connecting to Thingsboard node ...");
    // Attempt to connect (device_name, access_token, password)
    if ( client.connect("Temp_sensor_CC3200", TOKEN, NULL) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED] [ rc = " );
      //Serial.print( client.state() );
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}

void getAndSendTemperatureAndHumidityData()
{
  // Grab temperature measurements and print them.
  float objt = tmp006.readObjTempC();
  Serial.print("Object Temperature: "); Serial.print(objt); Serial.println("*C");


  Serial.print("Temperature: ");
  Serial.print(objt);
  Serial.print(" *C ");

  String temperature = String(objt);
  

  // Just debug messages
  Serial.print( "Sending temperature and humidity : [" );
  Serial.print( temperature ); Serial.print( "," );
  //Serial.print( humidity );
  Serial.print( "]   -> " );

  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"temperature\":"; 
  payload += temperature; 
  //payload += ",";
  //payload += "\"humidity\":"; 
  //payload += humidity;
  payload += "}";

  // Send payload
  char attributes[100];
  payload.toCharArray( attributes, 100 );
  client.publish( "v1/devices/me/telemetry", attributes );
  Serial.println( attributes );
}

void loop() 
{
  status = WiFi.status();
  if ( status != WL_CONNECTED) 
  {
    while ( status != WL_CONNECTED) 
    {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(WIFI_AP);
      // Connect to WPA/WPA2 network
      status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      delay(500);
    }
    Serial.println("Connected to AP");
  }

  if ( !client.connected() ) 
  {
    reconnect();
  }

  //if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
  //  getAndSendTemperatureAndHumidityData();
  //  lastSend = millis();
  bool abc = client.subscribe("v1/devices/me/rpc/request/+");
  bool rc = client.subscribe("v1/devices/me/attributes");
  Serial.println("subscribed");
  Serial.println(rc);
  Serial.println(abc);
  getAndSendTemperatureAndHumidityData();
  delay(1000);

  //client.loop();
}





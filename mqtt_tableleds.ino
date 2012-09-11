
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x01 };
byte server[] = { 10, 0, 0, 4 };
byte ip[]     = { 10, 0, 0, 33 };

void callback(char* topic, uint8_t* payload,unsigned int length) {
  // handle message arrived
  if(length >= 3 ) {
    analogWrite(3,payload[0]);
    analogWrite(5,payload[1]);
    analogWrite(6,payload[2]);
  }
}

PubSubClient client(server, 1883, callback);

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  while( !client.connected() ) {
    if (client.connect("MainTableController")) {
      client.subscribe("MainTableLEDs");
    } else {
      delay(1000);
    }
  }
  Serial.println("Done Setup");  
}

void loop()
{
  client.loop();
}


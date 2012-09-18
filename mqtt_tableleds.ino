
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0x01 };
byte server[] = { 10, 0, 0, 4 };
byte ip[]     = { 10, 0, 0, 33 };

PubSubClient client(server, 1883, callback);

void callback(char* topic, uint8_t* payload,unsigned int length) {
  Serial.println("msg received");
  
  // handle message arrived
  if( String(topic) == "announce" ) {
    Serial.println("received announcement");
    if( payload[length-1] == 0 ) { // It's probably a string :)
      if( String((char*)payload) == "space-open" ) {
        analogWrite(3,255);
        analogWrite(5,255);
        analogWrite(6,255);
      } else if ( String((char*)payload) == "space-closed" ) {
        analogWrite(3,0);
        analogWrite(5,0);
        analogWrite(6,0);
      }
    }
  }
    
  if( String(topic) == "MainTableLEDs" ) {
    Serial.println("received base command");
    if(length == 3 ) {
      analogWrite(3,payload[0]);
      analogWrite(5,payload[1]);
      analogWrite(6,payload[2]);
    }
  }
}

void setup()
{
  Serial.println("MainTableController Starting...");
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  
  analogWrite(3,0);
  analogWrite(5,0);
  analogWrite(6,0);
      
  while( !client.connected() ) {
    if (client.connect("MainTableController")) {      
      client.publish("announce","MainTableController");
      client.subscribe("announce");
      client.subscribe("MainTableLEDs");
      Serial.println("ok");
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


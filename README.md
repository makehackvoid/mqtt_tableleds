MQTT client for the MHV main table lights.

Connects to MQTT on Morphia and subs to MainTableLEDs.
Reads 3 bytes and sets pwm pins 3,5,6 to those values.
The mosfets controlling the LED strips are connected
to 3,5,6 as R,G,B.

The ws2801 strings are not currently connected.

MQTT msgs
---------

perl -e 'print pack "ccc",[r],[g],[b];' | mosquitto_pub -t MainTableLEDs -s  
perl -e 'print "space-open", (pack "c",0)' | mosquitto_pub -t announce -s  
perl -e 'print "space-closed", (pack "c",0)' | mosquitto_pub -t announce -s  


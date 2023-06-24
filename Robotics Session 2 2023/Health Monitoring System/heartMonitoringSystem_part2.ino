/*Created by Phebe Le | Session 2 | Heart Monitoring System  
 * 
 * This project is replicating a heart-rate watch system that uses output: LEDs, 
 * a buzzer, LCD display screen. Inputs: Pulse-Sensor, Ethernet webserver. It also includes an SD
 * card module which reads and writes data.
 * 
 * Due to the lack of space in the Arduino, the system is split up into two different modules 
 * a stationary system and mobile system. 
 * 
 * This section is Part 2: The stationary system consisting of a webserver with Ethernet connection
 * and a pulse sensor
 */

 //define libraries and interrupt (for pulse sensor)
#define USE_ARDUINO_INTERRUPTS true
#include <SPI.h>
#include <Ethernet.h>
#include <PulseSensorPlayground.h>

//define ethernet requirements: IP, MAC, define the server port
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
IPAddress ip(192, 168, 5, 81);
EthernetServer server(80);

//define the pulse sensor requirements
const int PulseWire = 0;
int Threshold = 547;
PulseSensorPlayground heartMonitor;

void setup()
{
  Serial.begin(9600);
  
  //initialise ethernet
  Ethernet.begin(mac, ip);
  server.begin();
  //initialise pulse sensor
  heartMonitor.analogInput(PulseWire);
  heartMonitor.setThreshold(Threshold);
  if (heartMonitor.begin()) {
    Serial.println("We created a heartMonitor Object !"); //initialisation
  } delay(50);
}

void loop()
{
  //align variables to each library module
  EthernetClient client = server.available();
  int myBPM = heartMonitor.getBeatsPerMinute();
  //when BPM is sensed
  if (heartMonitor.sawStartOfBeat()) {
    //define BPM restrictions and print to check
    if (myBPM >= 110) {
      myBPM = myBPM / 2;
    }
    else if (myBPM <= 50) {
      myBPM = myBPM * 2;
    } else if (myBPM == 0) {
      myBPM = myBPM + 50;
    }
    Serial.println(myBPM);
    //when ethernet server is sensed
    if (client) {  
      boolean currentLineIsBlank = true;
      Serial.println("started");
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          if (c == '\n' && currentLineIsBlank) {
            //HTML header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Refresh: 1"); //refresh rate of 1 second
            client.println();
            client.println("<HTML>");
            client.println("<HEAD>");
            client.println("<meta charset='UTF-8'>");
            client.println("<meta name='author' content='Phebe Le'>");
            client.println("<meta http-equiv='X-UA-Compatiable' content='IE-edge'>");
            client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
            client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
            client.println("<meta name='description content='heartbeat, temperature, humidity'> ");
            client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
            client.println("<link rel='stylesheet' type='text/css' href='https://randomnerdtutorials.com/ethernetcss.css' />");
            client.println("<TITLE>Heart Monitoring System</TITLE>");
            client.println("</HEAD>");
            //HTML body which includes the working BPM
            client.println("<BODY>");
            client.println("<H1>Heart Monitoring System</H1>");
            client.println("<br />");
            client.println("<br />");
            client.println("<H2>Heart Rate:</H2>");
            client.println(myBPM);
            client.println("<br />");
            client.println("<br />");
            client.println("<p>Created by Phebe Le in Session 2 2023</p>");
            client.println("<br />");
            client.println("</BODY>");
            client.println("</HTML>");
            break;
          }
          if (c == '\n') {
            currentLineIsBlank = true;
          }
          else if (c != '\r') {
            currentLineIsBlank = false;
          }
        }
      }
      delay(1);
      client.stop();
    }
  }
}

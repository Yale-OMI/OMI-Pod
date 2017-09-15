/************************************************************
ESP8266_Shield_Demo.h
SparkFun ESP8266 AT library - Demo
Jim Lindblom @ SparkFun Electronics
Original Creation Date: July 16, 2015
https://github.com/sparkfun/SparkFun_ESP8266_AT_Arduino_Library
This example demonstrates the basics of the SparkFun ESP8266
AT library. It'll show you how to connect to a WiFi network,
get an IP address, connect over TCP to a server (as a client),
and set up a TCP server of our own.
Development environment specifics:
  IDE: Arduino 1.6.5
  Hardware Platform: Arduino Uno
  ESP8266 WiFi Shield Version: 1.0
This code is released under the MIT license.
Distributed as-is; no warranty is given.
************************************************************/

//////////////////////
// Library Includes //
//////////////////////
// SoftwareSerial is required (even you don't intend on
// using it).
#include <SoftwareSerial.h> 
#include <omi8266.h>
#include <StringStream.h>
#include <OSCMessage.h>

//////////////////////////////
// WiFi Network Definitions //
//////////////////////////////
// Replace these two character strings with the name and
// password of your WiFi network.
const char mySSID[] = "omihotspot";
const char myPSK[] = "OMIAccess!";

#define UDP_PORT 57120
#define UDP_LINK 3
#define UDP_IP "10.42.0.155"

// All functions called from setup() are defined below the
// loop() function. They modularized to make it easier to
// copy/paste into sketches of your own.
void wifi_setup() 
{
  // Serial Monitor is used to control the demo and view
  // debug information.
  Serial.begin(9600);
//  serialTrigger(F("Press any key to begin."));

  // initializeESP8266() verifies communication with the WiFi
  // shield, and sets it up.
  initializeESP8266();

  // connectESP8266() connects to the defined WiFi network.
  connectESP8266();

  // displayConnectInfo prints the Shield's local IP
  // and the network it's connected to.
  displayConnectInfo();

//  serialTrigger(F("Press any key to connect client."));
}

void wifi_loop() 
{
  clientDemo();
}

void initializeESP8266()
{
  // omi8266.begin() verifies that the ESP8266 is operational
  // and sets it up for the rest of the sketch.
  // It returns either true or false -- indicating whether
  // communication was successul or not.
  // true
  while (!omi8266.begin()) {
    Serial.println(F("Error talking to ESP8266."));
  }
  Serial.println(F("ESP8266 Shield Present"));
}

void connectESP8266()
{
  // The ESP8266 can be set to one of three modes:
  //  1 - ESP8266_MODE_STA - Station only
  //  2 - ESP8266_MODE_AP - Access point only
  //  3 - ESP8266_MODE_STAAP - Station/AP combo
  // Use omi8266.getMode() to check which mode it's in:
  int retVal = omi8266.getMode();
  if (retVal != ESP8266_MODE_STA)
  { // If it's not in station mode.
    // Use omi8266.setMode([mode]) to set it to a specified
    // mode.
    retVal = omi8266.setMode(ESP8266_MODE_STA);
    if (retVal < 0)
    {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }
  Serial.println(F("Mode set to station"));

  // omi8266.status() indicates the ESP8266's WiFi connect
  // status.
  // A return value of 1 indicates the device is already
  // connected. 0 indicates disconnected. (Negative values
  // equate to communication errors.)
  retVal = omi8266.status();
  if (retVal <= 0)
  {
    Serial.print(F("Connecting to "));
    Serial.println(mySSID);
    // omi8266.connect([ssid], [psk]) connects the ESP8266
    // to a network.
    // On success the connect function returns a value >0
    // On fail, the function will either return:
    //  -1: TIMEOUT - The library has a set 30s timeout
    //  -3: FAIL - Couldn't connect to network.
    retVal = omi8266.connect(mySSID, myPSK);
    if (retVal < 0)
    {
      Serial.println(F("Error connecting"));
      errorLoop(retVal);
    }
  }
}

void displayConnectInfo()
{
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);
  // omi8266.getAP() can be used to check which AP the
  // ESP8266 is connected to. It returns an error code.
  // The connected AP is returned by reference as a parameter.
  int retVal = omi8266.getAP(connectedSSID);
  if (retVal > 0)
  {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }

  // omi8266.localIP returns an IPAddress variable with the
  // ESP8266's current local IP address.
  IPAddress myIP = omi8266.localIP();
  Serial.print(F("My IP: ")); Serial.println(myIP);
}

void clientDemo()
{
//  Serial.println("before tcp connect");
//  const int connectResult = omi8266.tcpConnect(2, UDP_IP, UDP_PORT, true);
//  Serial.println(connectResult);
//  Serial.println("after tcp connect");
//  Serial.println("before tcp send");
//  const int sendResult = omi8266.tcpSend(2, "hallo", 5);
//  Serial.println(sendResult);
//  Serial.println("after tcp send");
//  Serial.println("before udp close");
  const int closeResult = omi8266.udpCloseAll();
//  Serial.print("after udp close: ");
//  Serial.println(closeResult);
//  Serial.println("before udp connect");
  const int connectResult = omi8266.udpConnect(UDP_LINK, UDP_IP, UDP_PORT);
//  Serial.print("after udp connect: ");
//  Serial.println(connectResult);
//  Serial.println("before udp send");
for(int i = 0; i < 100; ++i) {
  String msg = "";
  formatTestOSCMessage(msg, i);
//  Serial.println(msg);
//  Serial.println(msg.length());
  char buf[48];
  for(int i = 0; i < 48; ++i) {
    buf[i] = msg.charAt(i);
  }
   int sendResult = omi8266.udpSend(UDP_LINK, buf, 48);
}
//  int sendResult = omi8266.udpSend(UDP_LINK, "/hi,shi", 7);
//  Serial.println("after udp send");
//  Serial.println(sendResult);
}

// errorLoop prints an error code, then loops forever.
void errorLoop(int error)
{
  Serial.print(F("Error: ")); Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}

void formatTestOSCMessage(String& emptyString, int i)
{
  StringStream ss(emptyString);
  OSCMessage msg("/test");
  msg.add(random(3, 12) + (i*10) + (1000 * random(0, 4)));
  msg.send(ss);
//  String& s = ss.str();
//  String copied_string = ss.str();
//  Serial.println(emptyString);
//  Serial.println(ss.str());
//  Serial.println(s);
//  Serial.println(copied_string);
//  Serial.println("here's a thing" + ss.str());
//  return s;
}

// serialTrigger prints a message, then waits for something
// to come in from the serial port.
void serialTrigger(String message)
{
  Serial.println();
  Serial.println(message);
  Serial.println();
  while (!Serial.available())
    ;
  while (Serial.available())
    Serial.read();
}

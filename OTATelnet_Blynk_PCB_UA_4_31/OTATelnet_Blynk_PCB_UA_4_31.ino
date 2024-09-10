
// The support of the Arduino fraternity is acknowledged and also https://somik.org/esp-ota-code-upload/ for the guide on WiFi updating (OTA) of the board software and monitoring/debugging via Telnet.
// Diagnostics are includede.They may be deleted but are a most useful guide if you intend making changes.
// -- GDM, santo@southcom.com.au 200524

#include <WiFiUdp.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "OTA_telnet_2.h"

// Blynk template and token details are comfidential and in creds.h
#include <BlynkSimpleEsp32.h>

const char* ssid = MYssid;
const char* password = MYpassword;
const byte ledPin = 15;  // ESP32 Pin to which my LED is connected
int LEDValue;
const byte tempPin = 4;  //the analog pin the TMP36's Vout (sense) pin is connected to
float TMP36_mV = 0;      // temp sensor voltage
float temp;              // for temp in C
const byte MQ2Pin = 16;  //GAS sensor output pin to Arduino analog A0 pin
int gasPinValue = 0;
const byte buttonPin = 13;  // the number of the pushbutton pin
byte started = 0;           // denotes the pumping system as started up
int pumpSecCounter;         // starts a second count, initiated by Telnet
float numPumpCycles = 0.0;
float lineNowPumping = 0.0;
float aboutPumping = 0.0;
unsigned long timeB4 = millis();  // used in Telnet to get a starting value, then it runs itself...
int V3Pin = 0;                    // virtual pin in Blynk
const char* fileName = "OTATelnet_Blynk_PCB_UA_4-31";
// unsigned long getSecs;  // for getting time since start  // no longer used
// unsigned long getMin;   // for getting time since start

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
////   this section for the triggers  >>>>>>>>>>>>>>>>>>>>>>>>>.
const float ramp = 4.0;         // a sudden rise in temp will start the pump. Degrees C.
float minTemp = 45.0;           // for getting the minumum of an array of temp values. Set it high to start. ramp will compare with this.
const float maxTemp = 50.0;     // startup temp
const int gasTrigr = 4000;      // this value will set off the system
const int gasTrigrLowr = 2500;  // this value will set off the system in combination with elevted temp.
const byte numLines = 7;        // the number of pumping lines connected to the relays
const byte lineTime = 30;       // how long each water line will pump for in seconds

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int countSecs = 0;                                                 //for the count to 10 secs
int decadeComplete = 0;                                            // measures the ten sec interval for average
const byte countTempSecs[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };  //for getting ave temp over a 10 second period
float tempDecade[10] = { 49.0, 49.0, 49.0, 49.0, 49.0, 49.0, 49.0, 49.0, 49.0, 49.0 };
float tenSecAve = 0;
float secTemp[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float lineIndicator[7] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7 };  // designates the water line

// getting average temp
const int c = 35;              // y=mx+c equation for temp sensor calibration; 610 before 5v adj
const float m = 14.6;          // y=mx+c equation for temp sensor calibration; 8.5 before
float aveTemp = 0;             // in Mv
const byte numTempReads = 10;  // delay period x number of reads must be well less than 1000 ; for checksensors C
int thisTempRead = 0;          // in Mvs, note integer, to stabilise the averaging maths...
long tempReadBucket = 0;       //collects the reads

//// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//// reset if Blynk drops out and won't restart after 20m..
int downDecades = 0;   // a variable to count the minutes offline
byte blynkStatus = 0;  // 0 is down, 1 is up.
void Blynk_now() {
  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    blynkStatus = 0;
  } else if (isconnected == true) {
    blynkStatus = 1;
  }
}
// Activates as part of decadecomplete, i.e. each 10 seconds

void downTime() {
  if (blynkStatus == 1) {
    downDecades = 0;
  } else if (blynkStatus != 1) {
    downDecades = downDecades + 1;
  }
}

void restart() {
  if ((downDecades > 120) && (started == 0)) ESP.restart();
}
// In main loop

// getting ready to send temp, gas and LED data
BLYNK_WRITE(V0) {
  Blynk.virtualWrite(V0, param.asFloat());
}

BLYNK_WRITE(V1) {
  Blynk.virtualWrite(V1, param.asFloat());
}

BLYNK_WRITE(V2) {
  Blynk.virtualWrite(V2, param.asInt());
}

BLYNK_WRITE(V3) {  //getting button press from the Blynk app. BLYNK_WRITE both sends and recieves values
  int V3Pin = param.asInt();
  if (V3Pin == 1) { started = 1; }
}

BLYNK_WRITE(V4) {
  Blynk.virtualWrite(V4, param.asInt());
}


/// Pins
// define the pins that will connect to the relays to drive the hose solenoids for sprinklers and sprayers
const byte pumpingPins[8]{ 42, 39, 38, 37, 36, 35, 48, 47 };

byte startFlag = 0;                     // a flag for managing the pump timer
const unsigned long tn_count = 1000UL;  // for counting the loop iteration to 1000 then send telnet stuff
unsigned long timeNow;                  // used in Telnet...

void setup() {
  ArduinoOTA.setHostname("UnitA");
  setupOTA();
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(buttonPin, INPUT);

  // set pumpingPins as OUTPUT
  for (int j = 0; j < 8; j++) {
    pinMode(pumpingPins[j], OUTPUT);
  }
  // // de-activate these
  for (int k = 0; k < 8; k++) {
    digitalWrite(pumpingPins[k], LOW);
  }
}  // end Void Setup


// FUNCTIONS for TRIGGERS.................FUNCTIONS................. FUNCTIONS .................FUNCTIONS................. FUNCTIONS .................FUNCTIONS................. FUNCTIONS .................FUNCTIONS.................

void decades() {
  for (int i = 0; (i < 10); i++) {
    if (countTempSecs[i] == (i + 1)) secTemp[i] = temp;
  }
  if (countSecs == 10) {
    tenSecAve = 0;
    for (int i = 0; (i < 10); i++) {
      tenSecAve = tenSecAve + (secTemp[i] / 10);
    }
    decadeComplete = 1;
    downTime();
  }
}

void allMoveUp() {
  if (decadeComplete > 0) {
    for (int i = 9; i > 0; i--) {
      tempDecade[i] = tempDecade[i - 1];
    }
    tempDecade[0] = tenSecAve;
    countSecs = 0;  // restarting the loop
    decadeComplete = 0;
  }
}

//temperature ramping trigger
void tempRampTrigr() {
  minTemp = tempDecade[0];
  for (int i = 1; i < 10; i++) {
    if (tempDecade[i] < minTemp) {
      minTemp = tempDecade[i];
    }
  }
  if ((tempDecade[0] - minTemp > ramp) && (tempDecade[9] <= 48)) {  // wait until readings settle after startup...
    started = 1;
    digitalWrite(ledPin, HIGH);
    TelnetStream.print(" ! Temp Ramp Trigger!");
  }
}

void tempMaxTrigr() {
  if ((started == 0) && (tenSecAve > maxTemp)) {
    started = 1;
    digitalWrite(ledPin, HIGH);
  }
}

void tempANDsmokeTrigr() {
  if ((tenSecAve > minTemp) && (gasPinValue > gasTrigrLowr) && (started == 0)) {
    started = 1;
    digitalWrite(ledPin, HIGH);
  }
}

void too_smokey() {
  if ((started == 0) && (gasPinValue > gasTrigr)) {
    started = 1;
    digitalWrite(ledPin, HIGH);
    TelnetStream.print(" ! Smoke detected!");
  }
}

void buttonStart() {
  if (digitalRead(buttonPin) == HIGH && digitalRead(ledPin) == LOW) {
    started = 1;
    digitalWrite(ledPin, HIGH);
  }
}

void checkSensorsAve() {
  for (int j = 1; j <= numTempReads && analogRead(tempPin) > 0; j++) {  //  easy maths
    thisTempRead = (analogRead(tempPin));
    tempReadBucket = tempReadBucket + thisTempRead;
  }
  // aveTemp = tempReadBucket;
  aveTemp = (tempReadBucket / 10);
  tempReadBucket = 0;  // empty the bucket ready for next time
  temp = (((aveTemp - 500) - c) / m);
  temp = round(temp * 10) / 10;  // for one decimal place.
  gasPinValue = (analogRead(MQ2Pin));
}

void pumping() {
  if ((started == 1) && (startFlag == 0)) {
    startFlag = 1;
  }
  // set up the array for pumping control :
  int pumpControl[7] = { lineTime * 0, lineTime * 1, lineTime * 2, lineTime * 3, lineTime * 4, lineTime * 5, lineTime * 6 };

  for (int i = 0; i < numLines; i++) {
    if (pumpSecCounter == pumpControl[i] + 1) {
      digitalWrite(pumpingPins[i], HIGH);  // open the line
      lineNowPumping = lineIndicator[i];   // show which line is pumping
    } else if (pumpSecCounter == pumpControl[i] + 3) {
      digitalWrite(pumpingPins[7], HIGH);  // start the pump
    } else if (pumpSecCounter == (pumpControl[i] + lineTime) - 3) {
      digitalWrite(pumpingPins[7], LOW);  // stop the pump
    } else if (pumpSecCounter == (pumpControl[i] + lineTime) - 1) {
      digitalWrite(pumpingPins[i], LOW);  // close the line
    }
  }
  if (pumpSecCounter == (lineTime * numLines) + 1) {  // for one cycle through
    digitalWrite(ledPin, LOW);
    numPumpCycles = numPumpCycles + 1.0;
    lineNowPumping = 0.0;
    started = 0;
    startFlag = 0;
    pumpSecCounter = 0;  // reset counter
  }
}

void telnetSend() {
  timeNow = millis();
  if ((timeNow - timeB4) > tn_count) {
    countSecs = countSecs + 1;  // increments the temperature ramp each sec
    timeB4 = millis();
    TelnetStream.print(F("     File is:  "));
    TelnetStream.print(fileName);
    TelnetStream.println();
    TelnetStream.print(F("    Cycle and Line is:  "));
    TelnetStream.print(aboutPumping);
    TelnetStream.println();
    TelnetStream.print(F("     Smoke PPI = "));
    TelnetStream.print(gasPinValue);
    TelnetStream.print("                   ");
    TelnetStream.print(F("     TEMPERATURE = "));
    TelnetStream.print(temp);  // display temperature value
    TelnetStream.print("*C");
    TelnetStream.println();
    TelnetStream.print(F("     Temp voltage = "));
    TelnetStream.print(thisTempRead);  // display temperature value
    TelnetStream.print(F(" Mv"));
    TelnetStream.println();

    // DIAGNOSTICS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    TelnetStream.print(F("Counter = "));
    TelnetStream.print(countSecs);  // display temperature value
    TelnetStream.println();
    TelnetStream.print(F("Latest Ten Sec Ave = "));
    TelnetStream.print(tenSecAve);  // display this temperature value
    TelnetStream.println();
    for (int i = 0; i < 10; i++) {
      TelnetStream.print("    ");
      TelnetStream.print(tempDecade[i]);  // display this temperature value
      TelnetStream.println();
    }
    TelnetStream.print(F("      minTemp =   "));
    TelnetStream.print(minTemp);
    TelnetStream.print(F("    Down decades = "));
    TelnetStream.print(downDecades);  // display this value
    TelnetStream.println();
    // Check startbutton status
    if (digitalRead(buttonPin) == HIGH) {
      TelnetStream.print(F("Start button is HIGH   "));
      TelnetStream.println();
    }

    // END DIAGNOSTICS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    if (started == 1) {
      TelnetStream.print(F("Started   "));
      TelnetStream.print(started);
      pumpSecCounter = pumpSecCounter + 1;  // for the pump control
      TelnetStream.print("   pumping seconds elapsed ");
      TelnetStream.print(pumpSecCounter);
      TelnetStream.println();
    } else {
      TelnetStream.print(F("   Waiting to start...  "));
      TelnetStream.print(started);
    }
    TelnetStream.print("                                                                  --!--  ");
    TelnetStream.println();
    TelnetStream.println();
    TelnetStream.println();
    // and do Blynk on these occasions...
    Blynk.run();
    BlynkDataSend();
  }
}
void BlynkDataSend() {
  //    Blynk.virtualWrite(V0,tempC);  // sending sensor value to Blynk app
  Blynk.virtualWrite(V0, temp);
  //  sensorValue_gas = analogRead(A1);         // reading sensor from analog pin
  Blynk.virtualWrite(V1, gasPinValue);  // sending sensor value to Blynk app

  // LEDValue = digitalRead(UA_Status);  // Tell Blynk we are pumping...
  LEDValue = started;  // Tell Blynk we are pumping...
  if (started != 0) {
    Blynk.virtualWrite(V3, 0);   //reset the button
    digitalWrite(ledPin, HIGH);  // turn the LEd on
  }
  Blynk.virtualWrite(V2, LEDValue);  // sending Unit A working status
  aboutPumping = numPumpCycles + lineNowPumping;

  Blynk.virtualWrite(V4, aboutPumping);  // number of completed pump cycles & no of current water line
                                         // Blynk.virtualWrite(V5, LineNowPumping);   // the number of the water line
}

void loop() {
  decades();
  allMoveUp();
  pumping();
  Blynk_now();
  buttonStart();
  telnetSend();
  checkSensorsAve();
  tempRampTrigr();
  tempMaxTrigr();
  too_smokey();
  restart();
  ArduinoOTA.handle();
}

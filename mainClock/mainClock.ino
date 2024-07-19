
/* Controller for Body of Work (גוף הזמן)
    at HaMiffal

    TODO
      - fix when minutes roll over from 59 to 0
      - make classes for each device as in the Adafruit Multitasking Tutorial
*/

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"

// Pin definitions

// outputs for relay board
// NOTE THAT RELAY IS ACTIVE LdOW
const int FOURBAR_PIN = 2;
const int unused3 = 3;
const int unused4 = 4;
const int CLICKY_PIN = 5;

// MOSFETs
const int RATTLE_PIN = 6;
const int SPINNING_LAMP_MOTOR_PIN = 7;

// second relay board
const int SECOND_RELAY_1 = 8;
const int SECOND_RELAY_2 = 12;
const int SECOND_RELAY_3 = 13;
const int SECOND_RELAY_4 = A0;

const int unusedA1 = A1;
const int unusedA2 = A2;
const int unusedA3 = A3;

// Note that the RTC uses SDA and SCL which is pins A4 and A5 so don't use them

// globals for recording time
int lastMinute = 0;
int lastSeconds = 0;

RTC_DS1307 rtc;

void setup () {

  // Initialize outputs
  pinMode (FOURBAR_PIN, OUTPUT);
  digitalWrite(FOURBAR_PIN, HIGH); // active LOW
  pinMode (CLICKY_PIN, OUTPUT);
  digitalWrite(CLICKY_PIN, HIGH); // active LOW
  pinMode (SPINNING_LAMP_MOTOR_PIN, OUTPUT);
  digitalWrite(SPINNING_LAMP_MOTOR_PIN, LOW);
  pinMode (RATTLE_PIN, OUTPUT);
  digitalWrite(RATTLE_PIN, LOW);

  Serial.begin(9600);
  Serial.println("Main clock for HaMiffal");

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  // Initialize the previous times
  DateTime now = rtc.now();
  lastMinute = now.minute();

  delay(100);
  Serial.println("setup finished");

}

void loop () {
  DateTime now = rtc.now();
  printTime();

  if (lastSeconds >= now.second()) {
    printTime();
    Serial.println("Resetting seconds");
    lastSeconds = 0;
  }
  if (1 == now.minute()) {
    printTime();
    Serial.println("Resetting minutes");
    lastMinute = 0;
  }

  if (lastMinute + 1 == now.minute()) {
    Serial.println("One minute");
    runSpinningLamp();
    delay(7000);
    runFourBar();
    delay(14000);
    runRattle();
    delay(23000);
    runClickeyThing();
    lastMinute = now.minute();
  }
}

void runSpinningLamp() {

  Serial.println("Spinning Lamp");
  digitalWrite(SPINNING_LAMP_MOTOR_PIN, HIGH);
  delay(3000);
  digitalWrite(SPINNING_LAMP_MOTOR_PIN, LOW);
}

void runFourBar() {

  Serial.println("Four Bar");
  digitalWrite(FOURBAR_PIN, LOW); // active LOW
  delay(10000);
  digitalWrite(FOURBAR_PIN, HIGH); // active LOW
}

void runClickeyThing() {

  Serial.println("Clicky Thing");
  digitalWrite(CLICKY_PIN, LOW); // active LOW
  delay(1000);
  digitalWrite(CLICKY_PIN, HIGH); // active LOW
  delay(1000);
  digitalWrite(CLICKY_PIN, LOW); // active LOW
  delay(1000);
  digitalWrite(CLICKY_PIN, HIGH); // active LOW
  delay(1000);
  digitalWrite(CLICKY_PIN, LOW); // active LOW
  delay(1000);
  digitalWrite(CLICKY_PIN, HIGH); // active LOW
}

void runRattle() {

  Serial.println("Rattle");
  digitalWrite(RATTLE_PIN, HIGH);
  delay(7000);
  digitalWrite(RATTLE_PIN, LOW);
}

void printTime() {
  DateTime now = rtc.now();
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

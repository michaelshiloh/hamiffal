
/* Controller for Body of Work (גוף הזמן)
    at HaMiffal

    TODO
    * fix when minutes roll over from 59 to 0
*/

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"

// Pin definitions
// Note that rtc uses SDA and SCL which is pins A4 and A5 so don't use them

// outputs for relay board
// NOTE THAT RELAY IS ACTIVE LOW
const int FOURBAR_PIN = 2;
const int unused3 = 3;
const int unused4 = 4;
const int unused5 = 5;

// For debugging our own trigger and NeoPixels for output
const int myTriggerPin = 12;
const int neoPixelsPin = 13;

// globals for recording time
int lastMinute = 0;

RTC_DS1307 rtc;

void setup () {
  
  // Initialize outputs
  pinMode (FOURBAR_PIN, OUTPUT);
  digitalWrite(FOURBAR_PIN, HIGH); // active LOW
  
  Serial.begin(9600);

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

}

void loop () {
  DateTime now = rtc.now();

  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  if (lastMinute + 1 == now.minute()) {
    Serial.println("One minute");
    triggerMinutes();
    lastMinute = now.minute();
  }
}

void triggerMinutes() {

  digitalWrite(FOURBAR_PIN, LOW); // active LOW
  delay(10000);
  digitalWrite(FOURBAR_PIN, HIGH); // active LOW

}

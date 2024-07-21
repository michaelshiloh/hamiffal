
/* Controller for Body of Work (גוף הזמן)
    at HaMiffal

    Modification log
    00 Jun 2024 - ms - initial entry; uses RTC
    21 Jul 2024 - ms - don't use the RTC; instead
                        make classes for each device
                        as in the Adafruit Multitasking Tutorial


*/

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
// Now I'm not using the RTC but it's still connected

// Classes for each device

class ClickyThing
{
    int pinNumber;
    int onTime = 1000;
    int offTime = 1000;
    int timeBetweenSequences = 20000;
    int numberClicksPerSequence = 4;
    int clickState = 0;
    int inSequenceState = 0;
    int clickCount = 0;
    unsigned long lastClickStateChange = 0;
    unsigned long lastSequenceStarted = 0;

  public:
    ClickyThing( int _pinNumber)
    {
      pinNumber = _pinNumber;
      pinMode (pinNumber, OUTPUT);
      digitalWrite(pinNumber, HIGH); // active LOW
    }

    void Update()
    {
      Serial.print("clickState = ");
      Serial.print(clickState);
      Serial.print("\tinSequenceState = ");
      Serial.print(inSequenceState);
      Serial.print("\tclickCount = ");
      Serial.print(clickCount);
      Serial.println();

      // we have two cases: either we are in a sequence, or we are between sequences

      if (!inSequenceState) {
        Serial.println("we are between sequences");

        // Is it time to start a new sequence?
        if ((millis() - lastSequenceStarted) > timeBetweenSequences)
        {
          Serial.println("turn on click");
                         digitalWrite(CLICKY_PIN, LOW); // active LOW

                         // update state
                         clickState = 1;
                         inSequenceState = 1;
                         lastClickStateChange = millis();
                         lastSequenceStarted = millis();
                         clickCount = 0;

                       }
                       } else { // otherwise, we are not between sequences
                         // so  we must be in the midst of a sequence
                         if (!clickState) {

                         // click is off so check whether it is time to turn it on
                         if ((millis() - lastClickStateChange) > offTime) {
                         Serial.println("turn on click");
                         digitalWrite(pinNumber, LOW); // active LOW

                         // update state
                         clickState = 1;
                         lastClickStateChange = millis();
                       }
                       } else {
                         // click is on so check whether it's time to turn it off
                         if ((millis() - lastClickStateChange) > onTime) {
                         Serial.println("turn off click");
                         digitalWrite(pinNumber, HIGH); // active LOW

                         // update state
                         clickState = 0;
                         lastClickStateChange = millis();

                         // since we finished a click, increment the click count
                         clickCount++;

                         // check to see if we're done with this sequence
                         if (clickCount > numberClicksPerSequence) {
                         Serial.println("click dequence done");
                         inSequenceState = 0;
                       }
                       }
                       }
                       }
                       }
                       };

                         ClickyThing clickyThing(CLICKY_PIN);


                         void setup () {

                         // Initialize outputs
                         pinMode (FOURBAR_PIN, OUTPUT);
                         digitalWrite(FOURBAR_PIN, HIGH); // active LOW
                         pinMode (SPINNING_LAMP_MOTOR_PIN, OUTPUT);
                         digitalWrite(SPINNING_LAMP_MOTOR_PIN, LOW);
                         pinMode (RATTLE_PIN, OUTPUT);
                         digitalWrite(RATTLE_PIN, LOW);

                         Serial.begin(9600);
                         Serial.println("Main clock for HaMiffal");

                         delay(100);
                         Serial.println("setup finished");

                       }

                         void loop () {

                         clickyThing.Update();
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



                         void runRattle() {

                         Serial.println("Rattle");
                         digitalWrite(RATTLE_PIN, HIGH);
                         delay(7000);
                         digitalWrite(RATTLE_PIN, LOW);
                       }

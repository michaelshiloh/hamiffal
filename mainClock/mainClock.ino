
/* Controller for Body of Work (גוף הזמן)
    at HaMiffal

    Modification log
    00 Jun 2024 - ms - initial entry; uses RTC
    21 Jul 2024 - ms - don't use the RTC; instead
                        make classes for each device
                        as in the Adafruit Multitasking Tutorial

  TODO
  - maybe some randomness ?

*/

// Pin definitions

// outputs for relay board
// NOTE THAT RELAY IS ACTIVE LdOW
const int FOURBAR_PIN = 2;
const int FLYINGSAUCER_PIN = 3;
const int CHAIN_PIN = 4;
const int CLICKY_PIN = 5;

// MOSFETs
const int RATTLE_PIN = 6;
const int SPINNING_LAMP_MOTOR_PIN = 7;

// second relay board
const int SECOND_RELAY_x = 8;
const int SECOND_RELAY_y = 12;
const int SECOND_RELAY_z = 13;
const int SCOOTER_PIN = A0;

const int unusedA1 = A1;
const int unusedA2 = A2;
const int unusedA3 = A3;

// Note that the RTC uses SDA and SCL which is pins A4 and A5 so don't use them
// Now I'm not using the RTC but it's still connected

// Classes for each device

class ClickyThing
{
    int pinNumber;
    int onTime = 905;
    int offTime = 990;
    int timeBetweenSequences = 52220;
    int numberClicksPerSequence = 3;
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
      //      Serial.print("clickState = ");
      //      Serial.print(clickState);
      //      Serial.print("\tinSequenceState = ");
      //      Serial.print(inSequenceState);
      //      Serial.print("\tclickCount = ");
      //      Serial.print(clickCount);
      //      Serial.println();

      // we have two cases: either we are in a sequence, or we are between sequences

      if (!inSequenceState) {
        //   Serial.println("we are between sequences");

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
            if (clickCount >= numberClicksPerSequence) {
              Serial.println("click sequence done");
              inSequenceState = 0;
            }
          }
        }
      }
    }
};

class Rattle
{
    int pinNumber;
    int onTime = 2800;
    int offTime = 19040;
    int state = 0;
    unsigned long lastStateChange = 0;

  public:
    Rattle( int _pinNumber)
    {
      pinNumber = _pinNumber;
      pinMode (pinNumber, OUTPUT);
      digitalWrite(pinNumber, LOW);
    }

    void Update()
    {
      if (!state) {
        // rattle is off so check whether it is time to turn it on
        if ((millis() - lastStateChange) > offTime) {
          Serial.println("turn on rattle");
          digitalWrite(pinNumber, HIGH);

          // update state
          state = 1;
          lastStateChange = millis();
        }
      } else {
        // Rattle is on so check whether it's time to turn it off
        if ((millis() - lastStateChange) > onTime) {
          Serial.println("turn off rattle");
          digitalWrite(pinNumber, LOW);

          // update state
          state = 0;
          lastStateChange = millis();

        }
      }
    }
};

class FourBar
{
    int pinNumber;
    int onTime = 8100;
    int offTime = 17200;
    int state = 0;
    unsigned long lastStateChange = 0;

  public:
    FourBar( int _pinNumber)
    {
      pinNumber = _pinNumber;
      pinMode (pinNumber, OUTPUT);
      digitalWrite(pinNumber, HIGH);
    }

    void Update()
    {
      if (!state) {
        // rattle is off so check whether it is time to turn it on
        if ((millis() - lastStateChange) > offTime) {
          Serial.println("turn on 4bar");
          digitalWrite(pinNumber, LOW);

          // update state
          state = 1;
          lastStateChange = millis();
        }
      } else {
        // Rattle is on so check whether it's time to turn it off
        if ((millis() - lastStateChange) > onTime) {
          Serial.println("turn off 4bar");
          digitalWrite(pinNumber, HIGH);

          // update state
          state = 0;
          lastStateChange = millis();

        }
      }
    }
};


class SpinningLamp
{
    int pinNumber;
    int onTime = 2100;
    int offTime = 32570;
    int state = 0;
    unsigned long lastStateChange = 0;

  public:
    SpinningLamp( int _pinNumber)
    {
      pinNumber = _pinNumber;
      pinMode (pinNumber, OUTPUT);
      digitalWrite(pinNumber, LOW);
    }

    void Update()
    {
      if (!state) {
        //  is off so check whether it is time to turn it on
        if ((millis() - lastStateChange) > offTime) {
          Serial.println("turn on spinning lamp");
          digitalWrite(pinNumber, HIGH);

          // update state
          state = 1;
          lastStateChange = millis();
        }
      } else {
        //  is on so check whether it's time to turn it off
        if ((millis() - lastStateChange) > onTime) {
          Serial.println("turn off spinning lamp");
          digitalWrite(pinNumber, LOW);

          // update state
          state = 0;
          lastStateChange = millis();

        }
      }
    }
};


class FlyingSaucer
{
    int pinNumber;
    int onTime = 1377;
    int offTime = 9579;
    int state = 0;
    unsigned long lastStateChange = 0;

  public:
    FlyingSaucer( int _pinNumber)
    {
      pinNumber = _pinNumber;
      pinMode (pinNumber, OUTPUT);
      digitalWrite(pinNumber, HIGH);
    }

    void Update()
    {
      if (!state) {
        //  is off so check whether it is time to turn it on
        if ((millis() - lastStateChange) > offTime) {
          Serial.println("turn on flying saucer");
          digitalWrite(pinNumber, LOW);

          // update state
          state = 1;
          lastStateChange = millis();
        }
      } else {
        //  is on so check whether it's time to turn it off
        if ((millis() - lastStateChange) > onTime) {
          Serial.println("turn off flying saucer");
          digitalWrite(pinNumber, HIGH);

          // update state
          state = 0;
          lastStateChange = millis();

        }
      }
    }
};

class ChainThing
{
    int pinNumber;
    int onTime = 5857;
    int offTime = 13941;
    int state = 0;
    unsigned long lastStateChange = 0;

  public:
    ChainThing( int _pinNumber)
    {
      pinNumber = _pinNumber;
      pinMode (pinNumber, OUTPUT);
      digitalWrite(pinNumber, HIGH);
    }

    void Update()
    {
      if (!state) {
        //  is off so check whether it is time to turn it on
        if ((millis() - lastStateChange) > offTime) {
          Serial.println("turn on flying saucer");
          digitalWrite(pinNumber, LOW);

          // update state
          state = 1;
          lastStateChange = millis();
        }
      } else {
        //  is on so check whether it's time to turn it off
        if ((millis() - lastStateChange) > onTime) {
          Serial.println("turn off flying saucer");
          digitalWrite(pinNumber, HIGH);

          // update state
          state = 0;
          lastStateChange = millis();

        }
      }
    }
};


class Scooter
{
    int pinNumber;
    int onTime = 23857;
    int offTime = 3941;
    int state = 0;
    unsigned long lastStateChange = 0;

  public:
    Scooter( int _pinNumber)
    {
      pinNumber = _pinNumber;
      pinMode (pinNumber, OUTPUT);
      digitalWrite(pinNumber, HIGH);
    }

    void Update()
    {
      if (!state) {
        //  is off so check whether it is time to turn it on
        if ((millis() - lastStateChange) > offTime) {
          Serial.println("turn on flying saucer");
          digitalWrite(pinNumber, LOW);

          // update state
          state = 1;
          lastStateChange = millis();
        }
      } else {
        //  is on so check whether it's time to turn it off
        if ((millis() - lastStateChange) > onTime) {
          Serial.println("turn off flying saucer");
          digitalWrite(pinNumber, HIGH);

          // update state
          state = 0;
          lastStateChange = millis();

        }
      }
    }
};


ClickyThing clickyThing (CLICKY_PIN);
Rattle rattle (RATTLE_PIN);
FourBar fourBar (FOURBAR_PIN);
SpinningLamp spinningLamp (SPINNING_LAMP_MOTOR_PIN);
FlyingSaucer flyingSaucer (FLYINGSAUCER_PIN);
ChainThing chainThing (CHAIN_PIN);
Scooter scooter (SCOOTER_PIN);

void setup () {
  Serial.begin(9600);
  Serial.println("Main clock for HaMiffal");

  delay(100);
  Serial.println("setup finished");

}

void loop () {

  clickyThing.Update();
  rattle.Update();
  fourBar.Update();
  spinningLamp.Update();
  flyingSaucer.Update();
  chainThing.Update();
	scooter.Update();
}

/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low accelerometer and
magnetometer data registers. They can be converted to units of g and
gauss using the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).

In the LSM303DLHC, LSM303DLM, and LSM303DLH, the acceleration data
registers actually contain a left-aligned 12-bit number, so the lowest
4 bits are always 0, and the values should be shifted right by 4 bits
(divided by 16) to be consistent with the conversion factors specified
in the datasheets.

Example: An LSM303DLH gives an accelerometer Z axis reading of -16144
with its default full scale setting of +/- 2 g. Dropping the lowest 4
bits gives a 12-bit raw value of -1009. The LA_So specification in the
LSM303DLH datasheet (page 11) states a conversion factor of 1 mg/digit
at this FS setting, so the value of -1009 corresponds to -1009 * 1 =
1009 mg = 1.009 g.
*/

#include "LSM303.h"
#include "Adafruit_Soundboard.h"
//#include <SoftwareSerial.h>

// Choose any two pins that can be used with SoftwareSerial to RX & TX
#define SFX_RX 0
#define SFX_TX 1
#define SFX_UG 2 // fake GND used for UG pin

// Connect to the RST pin on the Sound Board
#define SFX_RST 3
#define SFX_VCC 16 // fake VCC
#define SFX_GND 17 // fake GND

// we'll be using software serial
//SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);

// pass the software serial to Adafruit_soundboard, the second
// argument is the debug port (not used really) and the third
// arg is the reset pin
// Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);
// can also try hardware serial with
Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial1, NULL, SFX_RST);

// You can also monitor the ACT pin for when audio is playing!


//#define DEBUG_PRINT

LSM303 imu;
char report[40];
int face = 0;
int oldFace = 0;

void setup()
{
    pinMode(SFX_VCC, OUTPUT);
    digitalWrite(SFX_VCC, HIGH); // fake VCC

    pinMode(SFX_GND, OUTPUT);
    digitalWrite(SFX_GND, LOW); // fake GND

    pinMode(SFX_UG, OUTPUT);
    digitalWrite(SFX_UG, LOW); // fake GND

    pinMode(13, OUTPUT); // LED
    Serial.begin(115200);
    Serial.println("Starting...");

    Serial1.begin(9600);
    while (!sfx.reset()) {
        Serial.println("SFX board not found");
        delay(100);
    }

    Serial.println("SFX board found");
    if (! sfx.playTrack(face) ) {
        Serial.println("Failed to play track?");
    }

    imu.init();
    imu.enableDefault();
}

void loop()
{
    flushInput();

    static int cnt = 0;
    imu.readAcc();
    face = getFace();

    if (face && oldFace == face) {
        // count how long we've been on the same face:
        if (cnt++ == 3) {
            // play(face);
            Serial.print("    >>> PLAY ");
            Serial.println(face);

            if (! sfx.playTrack(face) ) {
                Serial.println("Failed to play track?");
            }
        }
    } else {
        cnt = 0;
    }

    oldFace = face;
    digitalWrite(13, !digitalRead(13));
    delay(100);
}

int getFace() {
    const int threshold = (1 << 14) * 85 / 100; // percentage of max val (=2**12)

#ifdef DEBUG_PRINT
    snprintf(report, sizeof(report), "%d %d %d %d %d %d",
             threshold, -threshold, imu.a.x, imu.a.y, imu.a.z,
             face ? face*32000/6 : oldFace*32000/6);
    Serial.println(report);
#endif

    if      (imu.a.x >  threshold) return 1;
    else if (imu.a.x < -threshold) return 2;
    else if (imu.a.y >  threshold) return 3;
    else if (imu.a.y < -threshold) return 4;
    else if (imu.a.z >  threshold) return 5;
    else if (imu.a.z < -threshold) return 6;

    return 0; // not stopped on a face
}

void flushInput() {
    // Read all available serial input to flush pending data.
    uint16_t timeoutloop = 0;
    while (timeoutloop++ < 40) {
        while(Serial1.available()) {
            Serial1.read();
            timeoutloop = 0;  // If char was received reset the timer
        }
        delay(1);
    }
}


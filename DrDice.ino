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

#include <LSM303.h>

#define DEBUG_PRINT

LSM303 imu;
char report[40];
int face = 0;
int oldFace = 0;

void setup()
{
    Serial.begin(115200);
    imu.init();
    imu.enableDefault();
}

void loop()
{
    imu.readAcc();
    face = getFace();

    if (face && oldFace != face) {
#ifndef DEBUG_PRINT
        Serial.println(face);
#endif
        oldFace = face;
        delay(100);
    }

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

    // TODO: array with x, y, z
    // TODO: test vector norm before
    // TODO: compute dot product with unitary vectors then check sign
    if (imu.a.x >  threshold) return 1;
    if (imu.a.x < -threshold) return 2;
    if (imu.a.y >  threshold) return 3;
    if (imu.a.y < -threshold) return 4;
    if (imu.a.z >  threshold) return 5;
    if (imu.a.z < -threshold) return 6;

    return 0; // not stopped on a face
}


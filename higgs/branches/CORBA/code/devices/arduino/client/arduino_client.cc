// Created on: Oct 2010
// Last Change: Wed Jul 13 05:00 PM 2011 C
/** \author Francisco J. Arjonilla <pacoarjonilla@yahoo.es>
 *
 * \brief Test client for the Arduino module.
 *
 */

#include "ArduinoC.h"
#include "CosNamingC.h"
#include "../../../lib/CORBA_utils.h"

using namespace std;

int main(int argc, char* argv[])
{
    CORBA_BEGIN_CLIENT(argc, argv);
    CORBA_GET_REFERENCE(higgs::Arduino, arduino, "Arduino");

    // Test accelerometer.
    double x,y;
    arduino->acelerometro(x, y);
    std::cout << "Accel readings: X=" << x << " Y=" << y << std::endl;

    // Test compass.
    std::cout << "Compass reading = " << arduino->brujula() * 180. / 3.14159269 << std::endl;

    // Test I/V sensors.
    higgs::iv_data inst = arduino->iv_instrumentation();
    higgs::iv_data mot = arduino->iv_motors();
    higgs::iv_data vaio = arduino->iv_vaio();

    cout << "******************************************" << endl;

    cout << "Uinst: " << inst.volts << " V" << endl;
    cout << "Iinst: " << inst.current << " A" << endl;

    cout << "Umot: " << mot.volts << " V" << endl;
    cout << "Imot: " << mot.current << " A" << endl;

    cout << "Charge: " << vaio.volts * 100 << "%" << endl;
    int m, h, s;
    s = vaio.current;
    m = s / 60;
    s -= m*60;
    h = m / 60;
    m -= h*60;
    cout << "Estimated charge duration: " << h << ":" << m << ":" << s << endl;
    usleep(200000);

    /*

    // Test servo.
    arduino->cambiarReferencia(100);
    sleep(1);
    arduino->cambiarReferencia(95);
    sleep(1);
    arduino->cambiarReferencia(90);
    sleep(1);
    arduino->cambiarReferencia(85);
    sleep(1);
    arduino->cambiarReferencia(80);
    sleep(1);
    arduino->cambiarReferencia(90);


    // Test switches.
    arduino->TurnOff(higgs::DevWrist);
    arduino->TurnOff(higgs::DevLaser);
    arduino->TurnOff(higgs::DevCamera);
    arduino->TurnOff(higgs::DevGPS);
    arduino->TurnOff(higgs::DevServo);
    arduino->TurnOff(higgs::DevSensors);

    sleep(2);
    arduino->TurnOn(higgs::DevCamera);
    sleep(1);
    arduino->TurnOff(higgs::DevCamera);
    sleep(1);
    arduino->TurnOn(higgs::DevGPS);
    sleep(1);
    arduino->TurnOff(higgs::DevGPS);
    sleep(1);
    arduino->TurnOn(higgs::DevServo);
    sleep(1);
    arduino->TurnOff(higgs::DevServo);
    sleep(1);
    arduino->TurnOn(higgs::DevSensors);
    sleep(1);
    arduino->TurnOff(higgs::DevSensors);

    arduino->TurnOn(higgs::DevWrist);
    arduino->TurnOn(higgs::DevLaser);
    arduino->TurnOn(higgs::DevCamera);
    arduino->TurnOn(higgs::DevGPS);
    arduino->TurnOn(higgs::DevSensors);
    arduino->TurnOn(higgs::DevServo);

    */

    CORBA_END_CLIENT;

    return 0;
}

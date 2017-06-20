/*
 * @author Francisco J. Arjonilla
 * Last Change: Thu Feb 17 06:00 PM 2011 C
 */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include "Exception.h"
#include "powercube_telegram.h"
#include "wrist.h"

#define SERIAL_DEVICE "/dev/ttyUSB0"

int main()
{
    TRY;	

    wrist_servant w(SERIAL_DEVICE);

    w.set_max_speed(6.F, higgs::wrist::PITCH);
    w.set_max_accel(2.F, higgs::wrist::PITCH);
    w.set_max_speed(4.F, higgs::wrist::ROLL);
    float f = .1F;
    for (int i = 0; i < 5; i++)
      {
	w.set_position(f, higgs::wrist::PITCH);
	w.set_position(0.5*f, higgs::wrist::ROLL);
	while (!w.is_ready(higgs::wrist::PITCH))
	  {
	    std::cout << w.get_current(higgs::wrist::PITCH) << std::endl;
	  }
	w.wait(higgs::wrist::BOTH);
	f += (f > 0) ? 0.1 : -0.1;
	f *= -1;
      }
    w.set_position(0.F, higgs::wrist::BOTH);
    w.wait(higgs::wrist::BOTH);


    std::cout << std::endl << "****************  List of parameters  ***************" << std::endl;
    std::cout << w.get_full_state(higgs::wrist::ROLL);

    CATCH;
    return 0;
}


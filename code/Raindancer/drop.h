/*
Robotic Lawn Mower
Copyright (c) 2017 by Tom Bradley

Private-use only! (you need to ask for a commercial-use)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Private-use only! (you need to ask for a commercial-use)
*/

#ifndef drop_H
#define drop_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Thread.h"
#include "helpers.h"
#include "hardware.h"
#include "errorhandler.h"
#include "config.h"

class Tdrop : public Thread
{
private:
    uint8_t count;

public:

    bool flagShowDropSensor;

    bool dropLeftOk;
    bool dropRightOk;

    void setup() {
        dropLeftOk = false;
        dropRightOk = false;

        flagShowDropSensor = false;
        count = 20;
    }

    virtual void run() {
        // Wird alle 53ms aufgerufen
        runned();
        // if (CONF_DISABLE_CHARGE_SERVICE) {
        //     chargeVoltage = 0;
        //  chargeCurrent = 0;
        //  return;
        // }

        dropLeftOk = diDropL == LOW;
        dropRightOk = diDropR == LOW;

        if(flagShowDropSensor && (++count > 20) ) {
            sprintf(errorHandler.msg,"!03,DROP leftOk: %d rightOk: %d\r\n", dropLeftOk, dropRightOk);
            errorHandler.setInfo();
            count = 0;
        }

    }

};

#endif

#include "HeartWave.h"

//constructor
HeartWave::HeartWave(){
    battery = new Battery();
    //currentSession = new Session();
}

//destructor
HeartWave::~HeartWave() {

}

/* Function that determines if the devicee has run out of charge
 */
bool HeartWave::isEmptyBattery(void) {
    if(battery->getPercentage() < 0) { //if battery empty
        return true;
    }

    return false; //otherwise, battery not empty
}

/* Function that determines if the device is low on battery
 * low battery is defined as less than or equal to 20 percent
 */
bool HeartWave::isLowCharge(void) {
    if(battery->getPercentage() <= 20) { //if low battery
        return true;
    }

    return false;
}

void HeartWave::setBreathPacerSetting(float newSetting) {
   // if()
}

//TODO: IMPLEMENT FOLLOWING FUNCTIONS AFTER CODE MORE DEVELOPED
//Function that initiates a new session
bool HeartWave::startSession() {

    //TODO: remove later. (testing code)
    std::cout << "In HeartWave::startSession - function working" <<std::endl;

    return false;
}




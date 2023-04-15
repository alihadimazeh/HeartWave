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

/* Function that updates the breath pacer setting to the passed in setting
 * after it checks if teh new setting is within an acceptable range.
 * Parameter:  float newSetting - new setting to be switched to
 */
void HeartWave::setBreathPacerSetting(float newSetting) {
   if((MIN_BP_SETTING <= newSetting) && (newSetting <= MAX_BP_SETTING)) { //if new setting is within range
        breathPacerSetting = newSetting;
   } else {
       std::cerr << "In HeartWave::setBreathPacerSetting - ERROR: new breath pacer setting not within expected range." << std::endl;
   }
}

/* Function that resets/restores device to initial install conditions
 */
void HeartWave::reset(void) {
    breathPacerSetting = DEFAULT_BP_SETTING; //reset BP setting
    currentSession = NULL; //clear current sesison
    sessions.clear(); //clear session history

}

/* Function that updates the LED color
 * Parameters: char color - char code of color to switch to
 * DEVELOPER NOTE: Not sure if we need this atm, so it might be removed in
 *                 a later commit.
 */
void HeartWave::updateLEDColor(char color) {
    if(color == LOW_COHERENCE_COLOR) {
        //TODO: add code later
    } else if(color == MID_COHERENCE_COLOR) {
        //TODO: add code later
    } else if(color == HIGH_COHERENCE_COLOR) {
        //TODO: add code later
    } else {
      std::cerr << "In HeartWave::updateLEDColor - ERROR: unidentified color"  << std::endl;
    }
}

/* Function that prints a message to console to represent a device beep
 * (ie. it do a beep :) )
 */
void HeartWave::beep(void) {
    std::cout << "-BEEP-" << std::endl;
}

//TODO: IMPLEMENT FOLLOWING FUNCTIONS AFTER CODE MORE DEVELOPED
//Function that initiates a new session
bool HeartWave::startSession() {

    //TODO: remove later. (testing code)
    std::cout << "In HeartWave::startSession - function working" <<std::endl;

    return false;
}




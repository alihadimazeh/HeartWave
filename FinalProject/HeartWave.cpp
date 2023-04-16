#include "HeartWave.h"

//constructor
HeartWave::HeartWave(){
    battery = new Battery();
    breathPacerSetting = DEFAULT_BP_SETTING;
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
    // follow use case 1
    // create a new session object
    // pass in a heartbeat and any other data we need
    // start a while loop
    // take in heart beat
    // calculate hrv, calculates coherence
    // update LED according to coherence level
    // update breath pacer level
    // loop through steps 7-9 until user termination
    std::cout << "In HeartWave::startSession - function working" <<std::endl;

    currentSession = new Session();
    sessions.append(currentSession);

    return false;
}

QVector<int> HeartWave::coherentHeartRates(){
    QRandomGenerator randomGenerator;
    QVector<int> heartRates;
    for (int i=0; i<100; i++){
        int heartRate = randomGenerator.bounded(60, 101);
        heartRates.append(heartRate);
    }
    return heartRates;
}

QVector<int> HeartWave::incoherentHeartRates(){
    QRandomGenerator randomGenerator;
    QVector<int> heartRates;
    for (int i=0; i<100; i++){
        int heartRate = randomGenerator.bounded(10, 175);
        heartRates.append(heartRate);
    }
    return heartRates;
}




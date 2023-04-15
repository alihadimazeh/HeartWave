#include "HeartWave.h"

HeartWave::HeartWave(){
    battery = new Battery();
    session = new Session();
}

Battery* HeartWave::getBattery(){
    return battery;
}

Session* HeartWave::getSession(){
    return session;
}

#include "HeartWave.h"

HeartWave::HeartWave(){
    battery = new Battery();
}

Battery* HeartWave::getBattery(){
    return battery;
}

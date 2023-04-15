#include "Battery.h"

Battery::Battery(){
    percentage = 85;
}

int Battery::getPercentage(){
    return percentage;
}


void Battery::drain(){
    percentage -= 1;
}

void Battery::recharge(){
    percentage = 100;
}

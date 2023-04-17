#include "Battery.h"

//constructor
Battery::Battery(){
    percentage = 100;
}

//destructor
Battery::~Battery() {

}

//Function that drains the battery percentage by 1 every function call
void Battery::drain(){
    percentage -= 1;
}

//Function that recharges the battery (resets the percentage to 100)
void Battery::recharge(){
    percentage = 100;
}

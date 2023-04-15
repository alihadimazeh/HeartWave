#include "Battery.h"

//constructor
Battery::Battery(){
    percentage = 85; //change this to 100 later
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

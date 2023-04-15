#ifndef BATTERY_H
#define BATTERY_H

class Battery{

    public:
        //Constructor and destructor
        Battery();
        ~Battery();

        //Getters
        inline int getPercentage(void) { return percentage; }

        //memeber functions
        void drain(void);
        void recharge(void);

    private:
        int percentage; //battery percentage

}; //class Battery

#endif // BATTERY_H

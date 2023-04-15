#ifndef BATTERY_H
#define BATTERY_H

class Battery{

    public:
        //Constructor and destructor
        Battery();
        ~Battery();

        //Getters
        inline double getPercentage(void) { return percentage; }

        //Setters
        inline void setPercentage(double newPercentage) { percentage = newPercentage; }

        //memeber functions
        void drain(void);
        void recharge(void);

    private:
        double percentage; //battery percentage

}; //class Battery

#endif // BATTERY_H

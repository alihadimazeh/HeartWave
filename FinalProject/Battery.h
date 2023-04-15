#ifndef BATTERY_H
#define BATTERY_H


class Battery{
    public:
        Battery();
        ~Battery();
        int getPercentage();
        void drain();
        void recharge();


    private:
        int percentage;
};

#endif // BATTERY_H

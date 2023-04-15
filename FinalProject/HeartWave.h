#ifndef HEARTWAVE_H
#define HEARTWAVE_H

#include <QVector>
#include "Battery.h"
#include "Session.h"


class HeartWave{
public:
    HeartWave();
    ~HeartWave();


protected:
    Battery* battery;
    Session* session;
    QVector<Session*> sessions;
    float breathPacerSetting;

public:
    bool startSession();
    bool isEmptyBattery();
    bool isLowCharge();
    Battery* getBattery();
    Session* getSession();
    bool coherenceLevelChanged(); //checks if the coherence level changed
    void setBreathPacerSetting();
    void reset(); //resets settings
    void updateLEDcolor(char color);
    void beep(); //prints statement to console


};

#endif // HEARTWAVE_H

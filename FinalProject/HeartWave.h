#ifndef HEARTWAVE_H
#define HEARTWAVE_H

#include <QVector>
#include "Battery.h"
#include "Session.h"


class HeartWave{

    public:
        //constructor and destructor
        HeartWave();
        ~HeartWave();

        //Getters
        inline Battery* getBattery(void) { return battery; }
        Session* getCurrentSession(void) { return currentSession; }

        //memeber functions
        bool startSession(void);
        bool isEmptyBattery(void);
        bool isLowCharge(void);
        bool coherenceLevelChanged(void); //checks if the coherence level changed
        void setBreathPacerSetting(float newSetting);
        void reset(void); //resets settings
        void updateLEDcolor(char color);
        void beep(void); //prints statement to console


    protected:
        Battery* battery; //device's battery
        Session* currentSession; //session currentlyy underway
        QVector<Session*> sessions; //all previous sessions
        float breathPacerSetting; //breath pacer setting


}; //class HeartWave

#endif // HEARTWAVE_H

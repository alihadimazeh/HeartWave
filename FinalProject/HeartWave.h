#ifndef HEARTWAVE_H
#define HEARTWAVE_H

#include <QVector>
#include <iostream>
#include <QRandomGenerator>

#include "Battery.h"
#include "Session.h"


#define MAX_BP_SETTING 60
#define MIN_BP_SETTING 0
#define DEFAULT_BP_SETTING 10

#define LOW_COHERENCE_COLOR 'r'
#define MID_COHERENCE_COLOR 'b'
#define HIGH_COHERENCE_COLOR 'g'


class HeartWave{


    public:
        //constructor and destructor
        HeartWave();
        ~HeartWave();

        //Getters
        inline Battery* getBattery(void) { return battery; }
        inline Session* getCurrentSession(void) { return currentSession; }
        inline QVector<Session*> getSessionHistory(void) { return sessions; }
        inline int getHistorySize(void) { return sessions.size(); }
        inline int getBP(void) { return breathPacerSetting; }

        //member functions
        bool startSession(void);
        bool isEmptyBattery(void);
        bool isLowCharge(void);
        bool coherenceLevelChanged(void); //checks if the coherence level changed
        void setBreathPacerSetting(float newSetting);
        void reset(void); //resets settings
        void updateLEDColor(char color);
        void beep(void); //prints statement to console
        // make 3 functions that generate different types of heart rates
        QVector<int> coherentHeartRates();
        QVector<int> incoherentHeartRates();


    private:
        Battery* battery; //device's battery
        Session* currentSession; //session currentlyy underway
        QVector<Session*> sessions; //all previous sessions
        int breathPacerSetting; //breath pacer setting


}; //class HeartWave

#endif // HEARTWAVE_H

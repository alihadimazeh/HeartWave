#ifndef SESSION_H
#define SESSION_H

#include <QVector>
#include <qcustomplot.h>
#include <QTime>
#include <QRandomGenerator>
#include <QString>
#include <QDebug>

class Session {

    public:
        //constructor and destructor
        Session();
        ~Session();

        //Getters
        inline float getDuration(void) { return timeLapsed; }
        inline float getAchievementScore(void) { return achievementScore; }

        //memeber functions
        float calculateHRV(void); // HRV is variabilty between heartbeat. like calculating slope
        float calculateCoherence(void);
        float updateBreathPacer(void); // calculate the new value of the breath pacer. get the ui to update it

    protected:
        float timeLapsed; //time duration of session
        float currentHRV; //current HRV value
        float achievementScore; //session's achievement score
        QVector<int> coherenceScores; //session's coherence scores
        QCustomPlot HRVGraph; //session's HRV graph. x axis: time (our own values), y axis: heartrate
};

#endif // SESSION_H

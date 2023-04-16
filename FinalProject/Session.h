#ifndef SESSION_H
#define SESSION_H

#include <QVector>
#include <qcustomplot.h>
#include <QTime>
#include <QRandomGenerator>
#include <QString>
#include <QDebug>
#include <QDateTime>

#define VECTOR_SIZE 16

class Session {

    public:
        static int currentId;

        //constructor and destructor
        Session();
        ~Session();

        //Getters
        inline double getDuration(void) { return timeLapsed; }
        inline double getAchievementScore(void) { return achievementScore; }
        inline QDateTime getDateTime(void) { return date; }
        inline int getSessionID(void) { return sessionId; }

        //memeber functions
        double calculateHRV(QVector<int>&); // HRV is variabilty between heartbeat. like calculating slope
        double calculateCoherence(int);
        double updateBreathPacer(void); // calculate the new value of the breath pacer. get the ui to update it

    protected:
        double timeLapsed; //time duration of session
        double currentHRV; //current HRV value
        double achievementScore; //session's achievement score
        QVector<int> coherenceScores; //session's coherence scores
        QCustomPlot HRVGraph; //session's HRV graph. x axis: time (our own values), y axis: heartrate
        QDateTime date;
        int sessionId;
};

#endif // SESSION_H

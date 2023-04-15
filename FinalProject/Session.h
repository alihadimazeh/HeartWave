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
        Session();
        ~Session();
        float calculateHRV(); // HRV is variabilty between heartbeat. like calculating slope
        float calculateCoherence();
        void updateBreathPacer(); // calculate the new value of the breath pacer. get the ui to update it

    protected:
        float timeLapsed;
        QVector<int> coherenceScores;
        float current_HRV;
        float achievement_score;
        QCustomPlot HRV_graph;
};

#endif // SESSION_H

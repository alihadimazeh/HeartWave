#include "Session.h"

Session::Session(){
    timeLapsed = 0;
    achievement_score = 0.0;


    coherenceScores.resize(20);
    // populate the coherence scores vector with randomized data
    QRandomGenerator generator;
    for (int i=0; i<coherenceScores.size(); i++){
        coherenceScores[i] = generator.bounded(100);
    }

    // printing out the values
    // delete later. confirmed it works as of 4:46 AM 04/15
    /*
    for (int i=0; i<coherenceScores.size(); i++){
        qDebug() << coherenceScores[i];
    }*/

}


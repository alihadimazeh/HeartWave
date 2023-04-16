#include "Session.h"

int Session::currentId = 0;

//constructor
Session::Session(){
    timeLapsed = 0;
    achievementScore = 0.0f;
    currentHRV = 0.0f;
    sessionId = currentId;


    coherenceScores.resize(VECTOR_SIZE);
    // populate the coherence scores vector with randomized data
    QRandomGenerator generator;
    for (int i=0; i<coherenceScores.size(); i++){
        coherenceScores[i] = generator.bounded(VECTOR_SIZE);
    }

    currentId++;
}

//destructor
Session::~Session() {

}

/* Function that calculates the current heart rate variability (HRV)
 */
double Session::calculateHRV(QVector<double>& heartRates) {
    QVector<double> rrIntervals;
    for (int i=1; i<heartRates.size(); i++){
        double rrInterval = heartRates[i] - heartRates[i-1];
        rrIntervals.append(rrInterval);
    }

    // calculate the mean RR interval
    double meanRRInterval = 0.0;
    for (int i = 0; i < rrIntervals.size(); i++) {
        meanRRInterval += rrIntervals[i];
    }
    meanRRInterval /= rrIntervals.size();

    // calculate the standard deviation of RR intervals
    double variance = 0.0;
    for (int i = 0; i < rrIntervals.size(); i++) {
        variance += pow(rrIntervals[i] - meanRRInterval, 2);
    }
    variance /= rrIntervals.size() - 1;
    double stdDev = sqrt(variance);

    // calculate HRV in milliseconds
    double hrv = stdDev * 1000;

    return hrv;
}

/* Function that calculates a coherence score acording to the current state
 * DEVELOPER NOTE: not sure if we need this if we are using a set of predefined score, function
 *                 might be removed in a future commit
 */
double Session::calculateCoherence(int flag) {
    QRandomGenerator randomGenerator;
    if (flag == 0){
        // generate low coherence data
        double coherenceScore = randomGenerator.bounded(0.5);
        qDebug() << "Generated Low Level Coherence Score: " << coherenceScore;
        return coherenceScore;
    }
    else if (flag == 1){
        // generate medium coherence data
        double coherenceScore = randomGenerator.generateDouble() * 0.5 + 0.5;
        qDebug() << "Generated Medium Level Coherence Score: " << coherenceScore;
        return coherenceScore;
    }
    else if (flag == 2){
        // generate high coherence data
        double coherenceScore = randomGenerator.generateDouble() * 15.0 + 1.0;
        qDebug() << "Generated High Coherence Score";
        return coherenceScore;
    }

    return 0.0;
}

/* Function that calulates the optimal breathPacer setting and returns it
 * Returns: optimal breathPacer setting
 */
double Session::updateBreathPacer() {
    //I have no clue

    return 0.0f; //PLACEHOLDER! CHANGE LATER
}


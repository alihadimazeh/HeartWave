#include "Session.h"

//constructor
Session::Session(){
    timeLapsed = 0;
    achievementScore = 0.0f;
    currentHRV = 0.0f;


    coherenceScores.resize(16);
    // populate the coherence scores vector with randomized data
    QRandomGenerator generator;
    for (int i=0; i<coherenceScores.size(); i++){
        coherenceScores[i] = generator.bounded(16);
    }


    // printing out the values
    // delete later. confirmed it works as of 4:46 AM 04/15
    /*
    for (int i=0; i<coherenceScores.size(); i++){
        qDebug() << coherenceScores[i];
    }*/

}

//destructor
Session::~Session() {

}

//TODO: IMPLEMENT FOLLOWING FUNCTIONS AFTER RESEARCH

/* Function that calculates the current heart rate variability (HRV)
 */
double Session::calculateHRV(QVector<double>& heartRates) {
    //how does one math?? ;-;
    //TODO: figure out math and get gud
    //Helpful resource?? -> https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5624990/#:~:text=It%20is%20calculated%20by%20first,average%20of%20these%20288%20values.

    // loop between all of the heartbeats
    // calculate HRV point between every heartbeat
    // append that calculated HRV to the graph
    // HRV is a measure of the variation in time intervals between heartbeats.

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
    // flag determines which coherence level
    // low coherence
    if (flag == 0){
        // generate low coherence data
    }
    else if (flag == 1){
        // generate medium coherence level
    }
    else if (flag == 2){
        // generate high coherence level
    }

    return 0.0f; //PLACEHOLDER! CHANGE LATER
}

/* Function that calulates the optimal breathPacer setting and returns it
 * Returns: optimal breathPacer setting
 */
double Session::updateBreathPacer(void) {
    //I have no clue

    return 0.0f; //PLACEHOLDER! CHANGE LATER
}


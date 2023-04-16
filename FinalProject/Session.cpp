#include "Session.h"

int Session::currentId = 0;

//constructor
Session::Session(){
    timeLapsed = 0;
    achievementScore = 0.0f;
    currentHRV = 0.0f;
    sessionId = currentId;


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

    currentId++;
}

//destructor
Session::~Session() {

}

//TODO: IMPLEMENT FOLLOWING FUNCTIONS AFTER RESEARCH

/* Function that calculates the current heart rate variability (HRV)
 */
float Session::calculateHRV() {
    //how does one math?? ;-;
    //TODO: figure out math and get gud
    //Helpful resource?? -> https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5624990/#:~:text=It%20is%20calculated%20by%20first,average%20of%20these%20288%20values.

    // loop between all of the heartbeats
    // calculate HRV point between every heartbeat
    // append that calculated HRV to the graph
    return 0.0f; //PLACEHOLDER! CHANGE LATER
}

/* Function that calculates a coherence score acording to the current state
 * DEVELOPER NOTE: not sure if we need this if we are using a set of predefined score, function
 *                 might be removed in a future commit
 */
float Session::calculateCoherence(void) {
    //send help T-T

    return 0.0f; //PLACEHOLDER! CHANGE LATER
}

/* Function that calulates the optimal breathPacer setting and returns it
 * Returns: optimal breathPacer setting
 */
float Session::updateBreathPacer(void) {
    //I have no clue

    return 0.0f; //PLACEHOLDER! CHANGE LATER
}


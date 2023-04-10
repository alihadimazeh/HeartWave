#ifndef SESSION_H
#define SESSION_H

#include <vector>

class Session {

    public:
        Session();
        ~Session();

    protected:
        float time_lapsed;
        std::vector<float> coherence_scores;
        float current_HRV;
        float achievement_score;
        //QCustomPlot HRV_graph;
};

#endif // SESSION_H

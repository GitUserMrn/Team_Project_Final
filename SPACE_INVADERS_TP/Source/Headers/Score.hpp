#ifndef PP_SPACE_INVASION_SCORE_HPP
#define PP_SPACE_INVASION_SCORE_HPP

#include <string>

class Score {

private:
    unsigned int enemiesShot;
    unsigned int wavesSurvived;
    unsigned int powerupsTaken;
    unsigned int shotsFired;
    unsigned int shotsHit;

public:
    Score();

    void increaseEnemiesShot();
    void increaseWavesSurvived();
    void increasePowerupsTaken();
    void increaseShotsFired();
    void increaseShotsHit();

    unsigned int getEnemiesShot() const;
    unsigned int getWavesSurvived() const;
    unsigned int getPowerupsTaken() const;
    unsigned int getShotsFired() const;
    unsigned int getShotsHit() const;
    float getShootAccuracy() const;

    void reset();
};

#endif


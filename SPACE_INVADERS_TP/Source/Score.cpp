#include <iomanip>
#include <cmath>

#include "Headers/Score.hpp"


Score::Score()
        : enemiesShot(0),
          wavesSurvived(0),
          powerupsTaken(0),
          shotsFired(0),
          shotsHit(0)
{}

void Score::increaseEnemiesShot() {
    enemiesShot++;
}

void Score::increaseWavesSurvived() {
    wavesSurvived++;
}

void Score::increasePowerupsTaken() {
    powerupsTaken++;
}

void Score::increaseShotsFired() {
    shotsFired++;
}

void Score::increaseShotsHit() {
    shotsHit++;
}

unsigned int Score::getEnemiesShot() const {
    return enemiesShot;
}

unsigned int Score::getWavesSurvived() const {
    return wavesSurvived;
}

unsigned int Score::getPowerupsTaken() const {
    return powerupsTaken;
}

unsigned int Score::getShotsFired() const {
    return shotsFired;
}

unsigned int Score::getShotsHit() const {
    return shotsHit;
}

float Score::getShootAccuracy() const {
    if (shotsFired == 0) {
        return 0.0f;
    }
    float accuracy = static_cast<float>(enemiesShot) / shotsFired * 100.0f; // calculate accuracy percentage
    return std::floor(accuracy * 10.0f) / 10.0f; // ret accuracy
}

void Score::reset() {
    this->enemiesShot = 0;
    this->powerupsTaken = 0;
    this->shotsFired = 0;

}
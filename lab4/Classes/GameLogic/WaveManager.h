#define WAVE_COOLDOWN 60
#define ADDITIONAL_ENEMY_A_WAVE 3

#include "Wave.h"

#include <cmath>

#include <SFML/System/Clock.hpp>

class WaveManager {
public:
    WaveManager();

    unsigned int getCurrentWaveNo();

    Wave *getCurrentWave();

    void setCurrentWaveNo(unsigned int wave);

    void forceWave();

    unsigned int getWaveCooldown();

private:
    sf::Clock m_waveClock;
    unsigned int m_waveNo;

    Wave m_currentWave;
};

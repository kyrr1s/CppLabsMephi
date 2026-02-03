#include "WaveManager.h"

WaveManager::WaveManager() : m_waveNo(0), m_currentWave(0, 0) {

}

unsigned int WaveManager::getCurrentWaveNo() {
    return m_waveNo;
}

void WaveManager::setCurrentWaveNo(unsigned int wave) {
    m_waveNo = wave;
    m_waveClock.restart();

    // We use 500 as of now.. seems good enough value to, test with.
    m_currentWave = Wave{m_waveNo * ADDITIONAL_ENEMY_A_WAVE, 500};
}

unsigned int WaveManager::getWaveCooldown() {
    return static_cast<unsigned int>(std::floor(std::abs(WAVE_COOLDOWN - m_waveClock.getElapsedTime().asSeconds())));
}

void WaveManager::forceWave() {
    setCurrentWaveNo(m_waveNo + 1);
}

Wave *WaveManager::getCurrentWave() {
    return &m_currentWave;
}

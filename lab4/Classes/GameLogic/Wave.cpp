#include "Wave.h"

Wave::Wave(unsigned int enemyCount, unsigned int enemySpawnInterval) : enemyCount(enemyCount),
                                                                       enemySpawnInterval(enemySpawnInterval),
                                                                       enemiesSpawned(0) {

}

unsigned int Wave::getEnemyCount() const {
    return enemyCount - enemiesSpawned;
}

unsigned int Wave::getEnemySpawnInterval() const {
    return enemySpawnInterval;
}

void Wave::enemyGotSpawned() {
    enemiesSpawned++;
}
class Wave {
    unsigned int enemiesSpawned;
    unsigned int enemyCount;
    unsigned int enemySpawnInterval;

public:
    explicit Wave(unsigned int enemyCount, unsigned int enemySpawnInterval = 100);

    /// Amount of enemies this wave will contain
    unsigned int getEnemyCount() const;

    /// This is in milliseconds
    unsigned int getEnemySpawnInterval() const;

    /// To keep track to how many enemies have been spawned of the maximum amount of this wave
    void enemyGotSpawned();
};

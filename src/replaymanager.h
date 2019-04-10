#ifndef REPLAYMANAGER_H
#define REPLAYMANAGER_H

#include <QtCore>
#include <map>

#include "replay.h"

class ReplayManager: public QObject
{
    // Singleton class containing replay data used inside the whole Application.

    Q_OBJECT

public:
    // Singleton instance
    static ReplayManager& Instance();
    Replay* GetReplay(uint64_t game_id);
    void AddReplay(Replay *replay);


	// Storing all replay informations
	std::map<uint64_t, Replay*> replays_;

private:
    // Singleton definition
    ReplayManager();
    ~ReplayManager();
    static ReplayManager instance_;
};

#endif // REPLAYMANAGER_H

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
    Replay* GetReplay(QString game_id);
    void AddReplay(Replay *replay);

private:
    // Singleton definition
    ReplayManager& operator= (const ReplayManager&){}
    ReplayManager (const ReplayManager&){}
    ReplayManager();
    ~ReplayManager();
    static ReplayManager instance_;

    // Storing all replay informations
    std::map<QString, Replay*> replays_;

};

#endif // REPLAYMANAGER_H

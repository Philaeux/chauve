#ifndef REPLAY_H
#define REPLAY_H

#include <QString>

class Replay
{
    // Class containing all the replay informations
    // - game_id_ Valve game id
    // - dem_path_ Full path to the dem file if it exists on disk, 0 otherwise
    // - replay_parsed_ info if the replay has been parsed or not

public:
    Replay(QString game_id, QString dem_path, bool replay_parsed);
    bool HasReplayOnDisk();
    void Parse();
    QString GetGameId();
    QString GetDemPath();
    bool IsReplayParsed();

private:
    QString game_id_;
    QString dem_path_;
    bool replay_parsed_;

    // Parsed info
    QString radiant_team_name_;
    QString dire_team_name_;
    int radiant_team_id_;
    int dire_team_id_;
    QString game_mode_;
    int winner_;
    int end_;
    int duration_;
};

#endif // REPLAY_H

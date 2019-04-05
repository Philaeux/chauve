#ifndef REPLAY_H
#define REPLAY_H

#include <QString>

struct team {
	uint32_t id;
	std::string tag;
};

struct game_info {
	uint64_t id;
	uint32_t league;
	int32_t mode;
	int32_t winner;
	uint32_t end_time;
};

class Replay
{
    // Class containing all the replay informations
    // - game_id_ Valve game id
    // - dem_path_ Full path to the dem file if it exists on disk, 0 otherwise
    // - parse_state_ info if the replay has been parsed or not

public:
    Replay(QString game_id, QString dem_path);
    bool HasReplayOnDisk();
    void Parse();
    QString GetGameId();
    QString GetDemPath();
    bool IsReplayParsed();

	team GetRadiantTeam();
	team GetDireTeam();
	game_info GetGameInfo();

private:
    QString game_id_;
    QString dem_path_;
    QString parse_state_;

    // Parsed info
	team radiant_team_;
	team dire_team_;
	game_info game_info_;
};

#endif // REPLAY_H

#include <QDebug>
#include <QString>
#include <iostream>
#include <fstream>

#include "replay.h"
#include "protobuf/demo.pb.h"

using namespace std;

// Replay file stuff
Replay::Replay(QString game_id, QString dem_path = nullptr)
{
    game_id_ = game_id;
    dem_path_ = dem_path;
    parse_state_ = QString("NOT_PARSED");
}

bool Replay::HasReplayOnDisk() {
    return dem_path_ != nullptr;
}

QString Replay::GetGameId() {
    return game_id_;
}

QString Replay::GetDemPath() {
    return dem_path_;
}

bool Replay::IsReplayParsed() {
    return parse_state_ != QString("NOT_PARSED");
}

uint32_t ReadVarUint32(fstream *is) {
    uint32_t x = 0;
    uint32_t y = 0;

    char b;
    uint32_t u;
    while (true) {
        is->read(&b, 1);
        u = static_cast<uint32_t>(b);
        x |= (u & 0x7F) << y;
        y += 7;
        if (((u & 0x80) == 0) || (y == 35)) {
            break;
        }
    }

    return x;
}

// Load the replay file and parse the necessary information for the application
void Replay::Parse() {
    if (!HasReplayOnDisk()) return;

    parse_state_ = QString("PARSE_IN_PROGRESS");
    fstream is (dem_path_.toStdString(), std::ios::in | std::ios::binary);
    if (is) {
        // HEADER check
        char * buffer = new char [8];
        is.read(buffer, 8);

        string magic = { 'P', 'B', 'D', 'E', 'M', 'S', '2', '\000' };
        if (!magic.compare(buffer)) {
            parse_state_ = QString("ERROR_INVALID_HEADER");
            return;
        }

        // Skip 8 bytes
        is.read(buffer, 8);

        // Read message
        uint32_t command = ReadVarUint32(&is);
        uint32_t tick = ReadVarUint32(&is);
        if (tick == 4294967295) tick = 0;

        bool compressed = false;
        if ( command & DEM_IsCompressed) {
          compressed = true;
          command = command ^ DEM_IsCompressed;
        }

        qDebug() << "command = '" << command << "'";
        qDebug() << "tick = '" << tick << "'";
        qDebug() << "compressed = '" << compressed << "'";

    }

    // TODO: Decode protobuff

    parse_state_ = QString("PARSED");
}

// Replay info getters

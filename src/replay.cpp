#include <QDebug>
#include <QString>
#include <iostream>
#include <fstream>
#include <iostream>

#include "replay.h"
#include "snappy.h"
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

struct dem_header {
	/** Used for verification purposes, needs to equal DOTA_HEADERID */
	char headerid[8];
	/** Points to the location of the game summary */
	int32_t offset_summary;
	/** Points to another packet @todo: verify */
	int32_t offset_2;
};

/** A single dem message */
struct dem_packet {
	/** Tick this messages was emitted at */
	int32_t tick;
	/** Message type */
	uint32_t type;
	/** Size of data */
	uint32_t size;
	/** Points to start of message */
	char* data;
};

uint32_t read_varint32(const char* data, uint8_t& read, std::size_t size = 0, std::size_t position = 0) {
	uint32_t result = 0; // result
	char tmp;            // holds last read value
	read = 0;            // make sure read is zeroed

	do {
		tmp = data[position++];
		result |= (uint32_t)(tmp & 0x7F) << (7 * read);
		++read;
	} while (tmp & 0x80);

	return result;
}

char* read_packet(dem_packet& msg, char* buffer, char* snappyBuffer) {
	uint8_t bytes_read;

	msg.type = read_varint32(buffer, bytes_read);
	buffer += bytes_read;
	
	msg.tick = read_varint32(buffer, bytes_read);
	buffer += bytes_read;

	msg.size = read_varint32(buffer, bytes_read);
	buffer += bytes_read;

	msg.data = buffer;

	auto new_head = buffer + msg.size;

	if (msg.type & DEM_IsCompressed) {
		size_t uncompressed_size = 0;
		snappy::GetUncompressedLength(msg.data, msg.size, &uncompressed_size);
		snappy::RawUncompress(msg.data, msg.size, snappyBuffer);

		msg.type = msg.type & ~DEM_IsCompressed;
		msg.data = snappyBuffer;
		msg.size = (uint32_t) uncompressed_size;
	}

	return new_head;
}


// Load the replay file and parse the necessary information for the application
void Replay::Parse() {
    if (!HasReplayOnDisk()) return;

    parse_state_ = QString("PARSE_IN_PROGRESS");
    fstream is(dem_path_.toStdString(), std::ios::in | std::ios::binary);
	if (!is) {
		parse_state_ = QString("Impossible to open file");
		return;
	}

	// Read all file
	uint32_t dem_size = 0;
	char* dem_data;

	const auto file_start = is.tellg();
	is.seekg(0, ios::end);
	dem_size = is.tellg() - file_start;
	is.seekg(0, ios::beg);

	dem_data = new char[dem_size];
	is.read(dem_data, dem_size);

	// Start parsing
	char* head = dem_data;
	char* snappyBuffer = new char[409600];
	dem_header* header = (dem_header*)head;

	if (string(header->headerid) != string("PBDEMS2")) {
		parse_state_ = QString("ERROR_INVALID_HEADER");
		return;
	}
	head += sizeof(dem_header); // Set to the first packet

	// Only parse summary
	head = dem_data + header->offset_summary;

	dem_packet packet;
	head = read_packet(packet, head, snappyBuffer);


	CDemoFileInfo info;
	info.ParseFromArray(packet.data, packet.size); // Here info has all
	cout << info.game_info().dota().match_id() << endl;

	// Clean data used
	delete[] snappyBuffer;
	delete[] dem_data;

    parse_state_ = QString("PARSED");

}

// Replay info getters

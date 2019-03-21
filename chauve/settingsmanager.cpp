#include "settingsmanager.h"


// Singleton constructor
SettingsManager::SettingsManager():
    QObject()
{

}

SettingsManager::~SettingsManager()
{

}

// Singleton instance
SettingsManager SettingsManager::instance_=SettingsManager();

SettingsManager& SettingsManager::Instance()
{
    return instance_;
}

// steam_replay_path_ getter
QString SettingsManager::GetSteamReplayPath()
{
    return steam_replay_path_;
}

// steam_replay_path_ setter
void SettingsManager::SetSteamReplayPath(QString steam_replay_path){
    steam_replay_path_ = steam_replay_path;
    emit SteamReplayPathUpdated(steam_replay_path_);
}

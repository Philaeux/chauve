#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QtCore>

class SettingsManager : public QObject
{
  // Singleton class containing application settings accessible into the whole Application.
  // - steam_replay_path_ path to the dota replays
  Q_OBJECT

public:
  // Singleton instance
  static SettingsManager& Instance() {
    static SettingsManager instance;
    return instance;
  };
  SettingsManager(SettingsManager const&) = delete;
  void operator=(SettingsManager const&) = delete;

  // steam_replay_path_ getter and setter
  QString GetSteamReplayPath();
  void SetSteamReplayPath(QString steam_replay_path);

private:
  SettingsManager();

  // Contain the path where dota replays are
  QString steam_replay_path_;

signals:
  void SteamReplayPathUpdated(QString new_path);
};

#endif // SETTINGSMANAGER_H

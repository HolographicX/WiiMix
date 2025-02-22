#pragma once

#include <map>
#include <string>


class WiiMixWebAPI {
  public:
    // static void RALoginCallback(std::string username, std::string token); // currently unused
    static std::map<int, std::string> getGameAchievements(int game_id);
    static std::map<std::string, int> getGameList(int console_id); // 16 for gamecube
    static int getGameID(int achievement_id);
  private:
    static std::string m_username;
    static std::string m_token;


};

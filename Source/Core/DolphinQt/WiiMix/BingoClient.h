// Copyright 2017 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "DolphinQt/WiiMix/Enums.h"
#include "DolphinQt/WiiMix/Objective.h"

// This is a file for syncing bingo cards between players
class WiiMixBingoClient : public QObject
{
  Q_OBJECT

public:
  explicit WiiMixBingoClient(QObject *parent = nullptr, QTcpSocket *socket = nullptr);

  bool Connect(QString lobby_name, QString player_name, QString lobby_password);

  bool CreateLobby(QString lobby_name, QString player_name, QString lobby_password);

  // Bingo card objectives are read top to bottom left to right and are 0 indexed
  bool UpdateBingoCard(int objective, WiiMixEnums::Player player);

  // Runs when the bingo card is completed
  bool BingoEnd();

  // Getters (from server)
  WiiMixEnums::BingoType GetBingoType() const;
  std::list<WiiMixEnums::Player> GetPlayers() const;
  std::list<WiiMixObjective> GetBingoCard() const;

// If desired, this can be optimized by storing in members and only sending the updated data
// But for simplicity and to reduce desync issues, we're currently sending the entire card each time
private:
  // TODOx: I'd like to have an instance of settings on the server and just send a request
  // to update that instance; this means that config widget should have an instance of settings
  // and that instance of settings should just be passed to SettingsWindow 
  QTcpSocket* m_socket;
//     std::list<WiiMixEnums::Player> m_players;
//     std::list<WiiMixObjective> m_bingo_card;
//     WiiMixEnums::BingoType m_bingo_type;
};
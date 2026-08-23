# Texas Hold'em Poker Source Code | 德州扑克源码

## Overview

This document introduces the Texas Hold'em Poker source code architecture
included in the TexasHoldem-Poker-Complete-Solution project.

本项目是一套面向多人德州扑克游戏开发的完整解决方案，采用 Unity 客户端
与 C++ 游戏服务器架构，可用于 Texas Hold'em Poker 游戏开发、技术研究
以及合法商业项目的二次开发。

Main repository:

https://github.com/masterai-top/TexasHoldem-Poker-Complete-Solution

## What Is Texas Hold'em?

Texas Hold'em is one of the most widely used poker game formats.

A standard Texas Hold'em game uses:

- Two private cards for each player
- Five community cards
- Pre-flop
- Flop
- Turn
- River
- Multiple betting rounds
- Final showdown

The game engine needs to handle player actions, betting states, pot calculation,
hand evaluation, room state synchronization and game settlement.

## Source Code Architecture

The project is organized around several major components:

```text
Texas Hold'em Poker
│
├── Unity Client
│   ├── UI
│   ├── Game Table
│   ├── Lobby
│   ├── Player System
│   └── Club System
│
├── C++ Game Server
│   ├── Room Management
│   ├── Game Logic
│   ├── Player Actions
│   ├── Betting
│   ├── Pot Management
│   └── Settlement
│
├── Backend Services
│   ├── Account
│   ├── User Data
│   ├── Club
│   └── Tournament
│
└── Database
    ├── MySQL
    └── Redis
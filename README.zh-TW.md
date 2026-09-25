[简体中文](README.md) | [繁體中文](README.zh-TW.md) | [English](README.en.md)

# 德州撲克源碼 / 德州源碼完整解決方案 - Unity 用戶端與 C++ 遊戲伺服器

這是一套面向多人即時遊戲的德州撲克源碼完整解決方案，包含 Unity 用戶端、C++ 多人遊戲伺服器、MySQL 與 Redis 資料層，以及俱樂部、聯盟、私人桌、MTT、SNG、戰績與營運管理模組。

[繁體中文網站](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/zh-tw/) · [简体中文网站](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/zh-cn/) · [English website](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/en/)

## 核心功能

| 分類 | 功能 |
| --- | --- |
| 撲克玩法 | 德州撲克、奧馬哈、短牌、大菠蘿、MTT、SNG、牛仔德州 |
| 俱樂部生態 | 俱樂部、聯盟、代理、私人桌、好友局及俱樂部幣管理 |
| 即時對戰 | 2 至 6 人牌桌、即時訊息、自訂通訊協議及斷線狀態處理 |
| 賽事系統 | MTT 多桌錦標賽、SNG 坐滿即玩、報名及排名流程 |
| 擴充功能 | 保險、戰績統計、機器人陪練、即時語音、視訊聊天及禮物系統 |
| 營運管理 | 管理員面板、儲值、商城、排行榜及使用者訂單管理 |

## 俱樂部、聯盟與私人桌玩法

1. 玩家建立俱樂部並設定基本資料。
2. 其他玩家申請加入，俱樂部管理者處理成員關係。
3. 俱樂部使用俱樂部幣及相關管理功能組織內部活動。
4. 俱樂部可加入聯盟，擴充跨俱樂部牌局及賽事情境。
5. 玩家建立好友局或私人桌，進入 2 至 6 人即時牌桌。
6. 賽事模組提供 MTT 多桌錦標賽及 SNG 坐滿即玩流程。

## 技術架構

| 元件 | 技術與職責 |
| --- | --- |
| 用戶端 | Unity、C#，支援 iOS 與 Android |
| 遊戲伺服器 | C++，負責房間、牌局狀態、下注、結算及即時訊息 |
| 資料層 | MySQL 持久化資料，Redis 負責快取與工作階段 |
| SDK 與平台 | Android SDK、iOS Workspace、用戶端資源及編輯器工具 |

## 德州撲克產品截圖

以下8張圖片均為儲存庫 `Screenshots/` 目錄中的現有檔案。

### 建立和加入俱樂部

![建立德州撲克俱樂部](Screenshots/创建俱乐部.jpg)  
**建立俱樂部 | Create Poker Club**

![申請加入德州撲克俱樂部](Screenshots/申请加入俱乐部.jpg)  
**申請加入俱樂部 | Join Poker Club**

### 俱樂部幣與聯盟

![德州撲克俱樂部幣管理](Screenshots/俱乐部币.jpg)  
**俱樂部幣管理 | Club Coin Management**

![德州撲克俱樂部加入聯盟](Screenshots/加入联盟.jpg)  
**加入聯盟 | Join Poker Alliance**

### 好友局與即時牌桌

![德州撲克好友局及私人桌](Screenshots/好友局.jpg)  
**好友局房間 | Private Poker Game Room**

![德州撲克即時打牌房間](Screenshots/打牌房间.jpg)  
**2 至 6 人即時牌桌 | Multiplayer Poker Table**

### MTT 賽事與個人中心

![德州撲克 MTT 多桌錦標賽](Screenshots/MTT赛事.jpg)  
**MTT 多桌錦標賽 | MTT Tournament**

![德州撲克玩家個人中心](Screenshots/个人中心.jpg)  
**個人中心 | Player Profile**

## 文件

- [俱樂部與聯盟玩法](docs/club-and-league.md)
- [德州撲克源碼概覽](docs/texas-holdem-source-code.md)
- [C++ 遊戲伺服器說明](docs/poker-game-server.md)
- [繁體中文產品網站](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/zh-tw/)

## 授權與合規

使用前請閱讀 [LICENSE](LICENSE)。商業部署、支付、隱私、未成年人保護、遊戲規則及地區監管要求必須由使用者獨立審查。

## 聯絡方式

- **Telegram：** [@xuzongbin001](https://t.me/xuzongbin001)
- **Email：** [masterai918@gmail.com](mailto:masterai918@gmail.com)

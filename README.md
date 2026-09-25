[简体中文](README.md) | [繁體中文](README.zh-TW.md) | [English](README.en.md)

# 德州扑克源码 / 德州撲克源碼完整解决方案 - Unity 客户端与 C++ 游戏服务端

[![客户端](https://img.shields.io/badge/客户端-Unity%20C%23-239120)](https://unity.com/)
[![服务端](https://img.shields.io/badge/服务端-C%2B%2B-00599C)](https://isocpp.org/)
[![平台](https://img.shields.io/badge/平台-iOS%20%7C%20Android-444444)](#技术架构)
[![许可证](https://img.shields.io/badge/许可证-查看%20LICENSE-blue)](LICENSE)

面向多人实时游戏的德州扑克源码（德州源码）完整解决方案，包含 Unity 客户端、C++ 游戏服务端、MySQL 与 Redis 数据层，以及俱乐部、联盟、私人房、MTT、SNG、战绩和运营管理模块。

**繁體中文摘要：** 德州撲克源碼（德州源碼）完整解決方案，包含 Unity 用戶端、C++ 多人遊戲伺服器、MySQL、Redis、俱樂部、聯盟、私人桌、SNG 與 MTT 錦標賽。

**English summary:** Texas Holdem poker source code with Unity clients, a C++ multiplayer game server, poker clubs, private tables, SNG and MTT tournaments, MySQL, and Redis.

[在线文档（简体中文）](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/zh-cn/) · [繁體中文網站](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/zh-tw/) · [English website](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/en/)

> 项目资料显示，该系统曾在生产环境持续运行两年以上，支持十余种游戏模式。实际部署能力、并发规模和第三方依赖请在使用前独立验收。

## 核心功能

| 分类 | 功能 |
| --- | --- |
| 扑克玩法 | 德州扑克、奥马哈、短牌、大菠萝、MTT、SNG、牛仔德州 |
| 俱乐部生态 | 俱乐部、联盟、代理、私人房、好友局和俱乐部币管理 |
| 实时对战 | 2 至 6 人牌桌、实时消息、自定义通信协议和断线状态处理 |
| 赛事系统 | 多桌锦标赛 MTT、坐满即玩 SNG、报名和排名流程 |
| 扩展功能 | 保险、战绩统计、机器人陪练、实时语音、视频聊天和礼物系统 |
| 运营管理 | 管理员面板、充值、商城、排行榜和用户订单管理 |

## 俱乐部、联盟与私人局流程

仓库中的真实产品截图展示了俱乐部玩法的主要用户流程：

1. 玩家创建俱乐部，设置俱乐部基础信息。
2. 其他玩家提交加入申请，俱乐部管理者处理成员关系。
3. 俱乐部使用俱乐部币及相关管理功能组织内部活动。
4. 俱乐部可以申请加入联盟，扩展跨俱乐部牌局与赛事场景。
5. 玩家可以创建好友局或私人房，进入 2 至 6 人实时牌桌。
6. 赛事模块提供 MTT 多桌锦标赛以及 SNG 坐满即玩流程。

更多简繁体说明见 [俱乐部与联盟玩法](docs/club-and-league.md)。具体权限、结算和配置以实际代码与部署版本为准。

## 技术架构

| 组件 | 技术与职责 |
| --- | --- |
| 客户端 | Unity、C#，支持 iOS 与 Android |
| 游戏服务端 | C++，负责房间、牌局状态、下注、结算和实时消息 |
| 数据层 | MySQL 持久化数据，Redis 负责缓存与会话 |
| SDK 与平台 | Android SDK、iOS Workspace、客户端资源和编辑器工具 |
| 部署 | 支持云服务器或物理机部署，具体依赖以实际代码和环境为准 |

```mermaid
flowchart LR
    A[Unity iOS / Android Client] -->|Real-time protocol| B[C++ Game Server]
    B --> C[(MySQL)]
    B --> D[(Redis)]
    E[Admin and Operations] --> B
```

## 主要目录

```text
Android SDK/client/       Android 客户端 SDK
ColiSDK.xcworkspace/      iOS Workspace
ColiSDK_Runner/           iOS SDK Runner
AssetGraphs/              Unity 资源依赖配置
Editor/                   Unity 编辑器工具
Screenshots/              产品真实截图
Doc/                      原始项目文档
docs/                     GitHub Pages 与技术文档
*.cpp / *.h               C++ 游戏服务端模块
```

## 产品截图与玩法说明

所有图片均来自仓库现有的 `Screenshots/` 目录，不添加未经确认的产品图。

### 创建和加入俱乐部

![创建德州扑克俱乐部](Screenshots/创建俱乐部.jpg)  
**创建俱乐部界面 | Create Poker Club**

![申请加入德州扑克俱乐部](Screenshots/申请加入俱乐部.jpg)  
**申请加入俱乐部 | Join Poker Club**

### 俱乐部币与联盟

![德州扑克俱乐部币管理](Screenshots/俱乐部币.jpg)  
**俱乐部币管理 | Club Coin Management**

![德州扑克俱乐部加入联盟](Screenshots/加入联盟.jpg)  
**加入联盟 | Join Poker Alliance**

### 好友局与实时牌桌

![德州扑克好友局和私人房](Screenshots/好友局.jpg)  
**好友局房间 | Private Poker Game Room**

![德州扑克实时打牌房间](Screenshots/打牌房间.jpg)  
**2 至 6 人实时牌桌 | Multiplayer Poker Table**

### MTT 赛事与个人中心

![德州扑克 MTT 多桌锦标赛](Screenshots/MTT赛事.jpg)  
**MTT 多桌锦标赛 | MTT Tournament**

![德州扑克玩家个人中心](Screenshots/个人中心.jpg)  
**个人中心 | Player Profile**

## 文档

- [德州扑克源码概览](docs/texas-holdem-source-code.md)
- [俱乐部与联盟玩法](docs/club-and-league.md)
- [C++ 游戏服务端说明](docs/poker-game-server.md)
- [产品功能页面](docs/features.html)
- [系统架构页面](docs/architecture.html)
- [部署与验收页面](docs/deployment.html)
- [GitHub Pages 项目网站](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/)
- [简体中文产品页](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/zh-cn/)
- [繁體中文產品頁](https://masterai-top.github.io/TexasHoldem-Poker-Complete-Solution/zh-tw/)

仓库中原有的 MTT、SNG、Unity、俱乐部和多人扑克专题文档继续保留在 `docs/` 目录。

## MasterAI 相关德州扑克项目

- [MasterAI 项目主页](https://github.com/masterai-top)
- [德州扑克赛事平台](https://github.com/masterai-top/Texas-Holdem-Poker-Tournament-Event-Platform)
- [德州金币大厅](https://github.com/masterai-top/Texas-Hold-em-Points-Lobby)
- [CFR 德州扑克 AI](https://github.com/masterai-top/cfr-poker-ai-masterai)

## 授权与合规

请在使用前阅读 [LICENSE](LICENSE)。当前许可证包含学习、研究、演示用途和单独商业授权要求，不属于未经限制的标准 MIT 许可证。商业部署、支付、隐私、未成年人保护、游戏规则及地区监管要求必须由使用者独立审核。

不要把生产环境密码、密钥、证书、真实用户数据或支付配置提交到公开仓库。安全问题请按照 [SECURITY.md](SECURITY.md) 私下报告。

## 联系方式

- **Telegram：** [@xuzongbin001](https://t.me/xuzongbin001)
- **Email：** [masterai918@gmail.com](mailto:masterai918@gmail.com)

如果该项目对你有参考价值，欢迎 Star 并关注后续更新。


---

# 10. `deployment-guide.md`

```markdown
# Poker Game Server Deployment Guide

## Overview

This document provides a high-level deployment guide for a multiplayer
Texas Hold'em Poker game server.

The exact deployment process depends on the project's build configuration,
operating system and infrastructure.

## Recommended Architecture

```text
Internet
   │
   ▼
Load Balancer / Gateway
   │
   ├───────────────┐
   ▼               ▼
Game Server 1   Game Server 2
   │               │
   └───────┬───────┘
           ▼
       Redis / Cache
           │
           ▼
         MySQL
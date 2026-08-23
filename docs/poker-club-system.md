
---

# 6. `poker-club-system.md`

```markdown
# Poker Club System | Poker Club Source Code

## Overview

A poker club system provides an organizational layer above individual game
rooms.

It can allow users to create clubs, manage members and access private poker
rooms.

## Club Architecture

```text
Platform
   │
   ├── Club A
   │     ├── Members
   │     ├── Rooms
   │     └── Statistics
   │
   ├── Club B
   │     ├── Members
   │     ├── Rooms
   │     └── Statistics
   │
   └── Club C
# C++ Poker Game Server

The repository includes C++ modules for a real-time multiplayer poker server. The public file structure shows responsibilities for game lifecycle, rooms, client and room messages, player actions, timers, database access, and selected automated decisions.

## Representative responsibilities

| Area | Examples from the repository |
| --- | --- |
| Game lifecycle | `gamebegin`, `gameend`, `gameroot` |
| Player actions | `allin`, `autobet`, `autofold` |
| Messaging | `onclientmessage`, `onroommessage`, `sendclientmessage`, `sendroommessage` |
| Timing | `begintimer`, `endtimer` |
| Persistence | `DBOperator` and order-related modules |

## Production review

Before deployment, review authentication, authorization, input validation, server-authoritative game state, reconnect handling, idempotency, transaction boundaries, randomness, logging, monitoring, rate limiting, backup recovery, and horizontal-scaling behavior.

Do not infer tested concurrency or production readiness from filenames or marketing descriptions alone. Validate the complete implementation under representative load.

## Related documentation

- [Architecture](architecture.html)
- [Deployment and acceptance](deployment.html)
- [Security policy](../SECURITY.md)

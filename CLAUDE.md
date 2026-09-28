# Hub project: shared brain for every agent
Read this file and LESSONS.md before doing anything. Update LESSONS.md before you finish.
## What we are building
An OASIS-style virtual universe called Hub, in one file: index.html (three.js r128, no build step). Realms: Hub Spaceport, Glass Dunes, Neon Grid, Night Grove, Sky Isles. Portals link them.
## Fixed decisions (do not change without the owner)
- Each realm has its own fixed look that does not change between visits.
- The player's avatar only changes when the player customises it.
- The ground must be solid and stable like GTA: real 3D geometry and fixed textures, not live AI repainting.
- Live AI mode (R key, Decart) is an optional filter; avatars are drawn by the game on top of it.
- Real photo-scanned textures come from Poly Haven (CC0) and are cached in IndexedDB.
- Online multiplayer is parked for later. Do not start it.
- Never use copyrighted Ready Player One names (OASIS, Halliday, etc.) inside the game.
## How we work
- Small steps, one task at a time, commit after every working step.
- Two agents: the builder plans and builds, the tester checks. Nothing is done until the tester passes it.
- If two attempts at something fail, stop and write what happened in LESSONS.md for the owner.

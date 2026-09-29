# Hub project: shared brain for every agent
Read this file and LESSONS.md before doing anything. Update LESSONS.md before you finish.
## What we are building
An OASIS-style virtual universe called Hub, in one file: index.html (three.js r128, no build step). Realms: Hub Spaceport, Glass Dunes, Neon Grid, Night Grove, Sky Isles. Portals link them.
The long-term target is a universe with the same structure, systems, rules and feel as the OASIS in Ready Player One (book and film), built with Hub's own names and Hub's own invented culture. UNIVERSE-BLUEPRINT.md is the reference for every part of that: the layout, travel, money, avatars, death, quests, the Hunt, the villains, and the phased roadmap. Read it before planning any goal, and take goals from its roadmap in order.
The mission behind it: real classrooms in Hub, and Orox glasses for children in need so they can go to school (UNIVERSE-BLUEPRINT.md section 11b, Phase 5). Anything that real children will use is safety-first: school- or guardian-made accounts, class-only contact, minimal data, and a qualified child-safety review before it ships.
## Fixed decisions (do not change without the owner)
- Picture quality comes first: full-resolution rendering, anti-aliased edges, soft shadows, ambient occlusion, high-resolution textures (UNIVERSE-BLUEPRINT.md section 11a). Never trade sharpness or frame rate for a feature.
- Each realm has its own fixed look that does not change between visits.
- The player's avatar can be anything: the player describes it in words and the game builds it (UNIVERSE-BLUEPRINT.md section 5a). It only changes when the player customises it, and describing it is customising it.
- The ground must be solid and stable like GTA: real 3D geometry and fixed textures, not live AI repainting.
- Live AI mode (R key, Decart) is an optional filter; avatars are drawn by the game on top of it.
- Real photo-scanned textures come from Poly Haven (CC0) and are cached in IndexedDB.
- Online multiplayer is parked for later. Do not start it.
- Never use copyrighted Ready Player One names (OASIS, Halliday, etc.) inside the game. Use the Hub names in UNIVERSE-BLUEPRINT.md section 2.
- No real films, games, music, characters or brands inside the game either. Hub has its own invented culture (UNIVERSE-BLUEPRINT.md section 9).
## How we work
- Small steps, one task at a time, commit after every working step.
- Two agents: the builder plans and builds, the tester checks. Nothing is done until the tester passes it.
- If two attempts at something fail, stop and write what happened in LESSONS.md for the owner.
- Work the roadmap in UNIVERSE-BLUEPRINT.md section 12 in order. Each numbered goal has a "done means" line; the tester checks that line before the goal counts.
- When a phase finishes, give the owner a short summary of what changed and what is next.

## The Unreal version
`hub-unreal/` is the photoreal rebuild in Unreal Engine 5 (see UNREAL-PLAN.md). It has its own CLAUDE.md and LESSONS.md and runs on the owner's computer, not in the cloud. This browser game and the Unreal project share UNIVERSE-BLUEPRINT.md; a gameplay decision made in one applies to the other.

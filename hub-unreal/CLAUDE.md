# Hub (Unreal Engine 5): shared brain for every agent
Read this file, ../UNIVERSE-BLUEPRINT.md and ../UNREAL-PLAN.md before doing anything. Update LESSONS.md before you finish.

## What we are building
The same Hub universe as the browser game in ../index.html, rebuilt in Unreal Engine 5 for photoreal quality: Lumen, Nanite, virtual shadow maps, Megascans surfaces, a MetaHuman player. One map per realm in Content/Maps. Gameplay is C++ in Source/Hub (character, progress, portals, coins, hoverbike, time trial, kiosk, avatar recipe, HUD); levels, materials and meshes are made in the editor.

## Fixed decisions (do not change without the owner)
- Quality first: Lumen GI and reflections, Nanite on every static mesh that supports it, virtual shadow maps, TSR. Never trade that for a feature.
- Each realm has its own fixed look that does not change between visits. Time of day is fixed per map.
- The player's avatar only changes when the player changes it. "Describe your avatar" (UHubAvatarLibrary::ParseDescription) is the contract; the editor binds the recipe to a MetaHuman or modular character in BP_HubCharacter::ApplyRecipe.
- Real scanned assets only: Megascans (Fab) surfaces and 3D assets, MetaHumans. No hand-painted placeholders left in a finished realm.
- Never use copyrighted Ready Player One names or real films, games, music or brands inside the game. Hub's own names are in ../UNIVERSE-BLUEPRINT.md section 2.
- Online multiplayer is parked. Do not start it.

## How we work
- This project runs on the owner's computer with the engine installed. The cloud session cannot open the editor; it can only edit code and text. Editor work (placing assets, MetaHumans, materials) is described step by step in UNREAL-PLAN.md for the owner or a local Claude Code session.
- Build: `Engine/Build/BatchFiles/Build.bat HubEditor Win64 Development -project=<path>/Hub.uproject` (Windows) or `Engine/Build/BatchFiles/Mac/Build.sh HubEditor Mac Development -project=...` (Mac). The first build surfaces any compile errors in Source/Hub; fix them before anything else.
- Small steps, one task at a time, commit after every step. Binary assets go through Git LFS (.gitattributes is set up).
- Two agents: the builder plans and writes code and editor instructions; the tester runs the build, the automation tests (`-ExecCmds="Automation RunTests Hub"`) and plays the map with `-game -windowed -resx=1280 -resy=720 -log`, then reports pass or fail with the exact error.
- If two attempts at something fail, stop and write what happened in LESSONS.md for the owner.

# Hub in Unreal Engine 5: the plan

The browser game (index.html) stays as the quick-to-share version. The photoreal version is an Unreal Engine 5 project in `hub-unreal/`. This file is the owner's checklist and the agents' map. UNIVERSE-BLUEPRINT.md still says *what* Hub is; this says how it is built in Unreal.

## 1. What you need on your computer

- A PC with Windows 10/11, an NVIDIA RTX 3060 / AMD 6700 or better, 32 GB RAM, 150 GB free on an SSD. A Mac with Apple silicon (M2 Pro or better, 32 GB) also works, with Lumen and Nanite, but slower to compile and with fewer Fab assets tested on it.
- An Epic Games account (free). Install the **Epic Games Launcher**, then **Unreal Engine 5.4** from its Library tab (about 60 GB). If you install 5.5 instead, change `"EngineAssociation": "5.4"` in `hub-unreal/Hub.uproject` to `"5.5"` and replace the `Bridge` plugin entry with `"Name": "Fab"`.
- Visual Studio 2022 Community (Windows) with the "Game development with C++" workload, or Xcode (Mac). The engine needs it to compile the project's C++.
- Git with Git LFS (`git lfs install`) so the binary assets (maps, meshes, textures) go into the repo properly.
- Claude Code installed locally (`npm install -g @anthropic-ai/claude-code`), run inside `hub-unreal/`. The cloud session that built the browser game cannot open Unreal; the local one can build, run and test it.

## 2. First open (once)

1. Clone the repo and check out the branch. Open `hub-unreal/Hub.uproject`. Unreal asks to rebuild the missing modules: say yes. This compiles `Source/Hub`. The scaffold was written without a compiler, so expect a few errors on this first build; open the project in Visual Studio (right-click the .uproject, Generate Visual Studio project files, open the .sln, build `HubEditor`) or let local Claude Code fix them: "build HubEditor and fix every compile error in Source/Hub without changing behaviour".
2. In the editor: Edit, Plugins: confirm Enhanced Input, Bridge (or Fab) and Water are enabled. Restart if asked.
3. Project Settings, Rendering: confirm Dynamic Global Illumination = Lumen, Reflections = Lumen, Shadow Map Method = Virtual Shadow Maps, Anti-Aliasing = TSR, Nanite enabled. `Config/DefaultEngine.ini` sets these already.
4. Make the first map: File, New Level, Open World (this gives World Partition, a landscape and a sky). Save as `Content/Maps/HubSpaceport`. World Settings: GameMode Override = `HubGameMode`. Press Play: you should have a third-person mannequin with WASD, mouse look, Space to jump twice, Shift to sprint, and the code-drawn HUD in the corner. If the character has no visible mesh, open the Content Browser, add the Third Person feature pack (Add, Add Feature or Content Pack, Third Person), make a Blueprint child of `HubCharacter` (right-click HubCharacter in the C++ Classes folder, Create Blueprint class, name it `BP_HubCharacter`), set its Mesh to the mannequin with its animation blueprint, and in `HubGameMode` (or a `BP_HubGameMode` child) set Default Pawn Class to `BP_HubCharacter`.

That is milestone 0: it runs.

## 3. Milestones (the builder's roadmap; each one is small and testable)

**M1. The Spaceport looks photoreal.** In HubSpaceport: Quixel Bridge (Window, Quixel Bridge) or Fab: download a ground surface (e.g. a cobblestone or concrete plaza scan), grass and moss surfaces, six to eight 3D assets (boulders, planters, a bench, a lamp post), and a tree pack. Paint the landscape with the surfaces (Landscape mode, one layer per surface), place the plaza as a flat area at the origin with a circular kerb, drop in the assets with Nanite on (it is on by default for Megascans), foliage-paint the trees and grass (Foliage mode). Lighting: keep the sky, set the Directional Light to about 4 degrees above the horizon for the golden-hour look, Sky Atmosphere on, Volumetric Fog on in the Exponential Height Fog, a Post Process Volume set to Infinite Extent with a slight filmic look (bloom 0.3, vignette 0.4, film grain 0.02 in 5.4's Film settings, auto exposure min/max 0.8/1.2). Done means: standing at the origin, nothing on screen is a flat colour or a smooth primitive; a screenshot could pass as a photo of a real plaza at sunset.

**M2. A real human.** Window, Quixel Bridge, MetaHumans: create one in MetaHuman Creator (free, in the browser at metahuman.unrealengine.com), download it into the project, and set `BP_HubCharacter`'s mesh to it with its face and body. Then implement `ApplyRecipe` in `BP_HubCharacter`: main colour drives the outfit material's base colour parameter, second colour the accents, glow colour an emissive parameter, height scales the capsule and mesh (0.9 to 1.2), build widens the mesh scale, features attach meshes to sockets (cape to the spine socket, halo above the head, wings to the back). Done means: "a tall chrome knight with a red cape" changes the MetaHuman's outfit to chrome with a red cape and makes it taller, and it walks and runs with MetaHuman animation.

**M3. Portals and Glass Dunes.** Second map `GlassDunes` (Open World), landscape sculpted into dunes, Megascans sand and sandstone surfaces, sandstone cliff assets scaled up as mesas, Sky Atmosphere with a low warm sun and a dusty Exponential Height Fog. A `HubPortal` in each map pointing at the other (Target Map soft reference). `BP_HubGameMode_Dunes` child with Danger Realm = true. Done means: walk into the Spaceport portal, arrive in the dunes, walk back; credits and XP survive the trip (they are in the save game).

**M4. Coins, the kiosk, the bike, the time trial.** Place `HubCoin` actors (mesh: a Megascans gold coin or a simple cylinder with a metallic material) in both maps; a `HubKiosk` on the Spaceport with a shop widget (`WBP_Shop` listing `Items`, each button calls `BuyOrToggle`); a `HubHoverbike` with a mesh (a Fab hoverbike or a kit-bashed body), and a `HubTimeTrial` with nine ring actors (a torus mesh with an emissive material) placed around the plaza. Done means: E buys a cape and it appears; E mounts the bike and it rides through the rings against the clock with the reward at the end.

**M5. Neon Grid, Night Grove, Sky Isles, Campus.** One map each, Megascans for anything natural, emissive materials for neon. Danger realms get their damage sources (Neon Grid laser volumes calling `Progress->Hurt`).

**M6. The Hunt.** The Archive, the Ledger, the three shard challenges and the Citadel, exactly as UNIVERSE-BLUEPRINT.md sections 9 and 12 describe, using the C++ pieces above.

## 4. How the C++ maps to the blueprint

| Blueprint idea | Unreal piece |
|---|---|
| Player, movement, boost, sprint, views | `AHubCharacter` (Character with spring-arm camera, Enhanced Input built at runtime, three views on V) |
| Credits, XP, level, HP, zero-out | `UHubProgress` component on the character; `OnZeroedOut` event for the bundle and effects |
| Save between realms and sessions | `UHubSaveGame` (slot "HubSave") |
| Describe your avatar | `UHubAvatarLibrary::ParseDescription` -> `FHubAvatarRecipe`; `BP_HubCharacter::ApplyRecipe` binds it to the MetaHuman |
| Portals, fares | `AHubPortal` (box trigger, soft map reference, fare) |
| Coins | `AHubCoin` (remembered per map) |
| Outfitters | `AHubKiosk` (item list, `BuyOrToggle`, `OpenShop` event for the widget) |
| Hoverbike | `AHubHoverbike` (E mounts, kinematic hover, chase camera) |
| Time trial | `AHubTimeTrial` (pad, ordered rings, par, best times) |
| Realm rules | `AHubGameMode` per map (magic, tech, danger, sector) |
| HUD | `AHubHUD` draws with Canvas until proper widgets replace it |

## 5. The two agents, locally

Run `claude` inside `hub-unreal/`. It reads `hub-unreal/CLAUDE.md`, which carries the same builder/tester rules as the browser game. The builder writes C++ and step-by-step editor instructions; the tester builds (`Build.bat HubEditor Win64 Development -project=...`), runs the automation tests and launches the map in a window to check the done line. Editor-only work (placing Megascans, MetaHuman setup) is yours or the builder's instructions for you: the agents cannot click inside Unreal.

## 6. Honest expectations

Milestone 1 already looks like a different game: Megascans plus Lumen is what makes Unreal screenshots look like photographs. Milestone 2 removes the last "Roblox" tell. What it costs: a proper GPU, tens of gigabytes of assets, and editor work you or a local session do by hand. The browser game stays the thing you can send anyone a link to.

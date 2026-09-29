# Hub universe blueprint

The owner's goal: Hub becomes the same kind of place as the OASIS in Ready Player One (the 2011 novel and the 2018 film). Same structure, same systems, same rules, same feeling of scale. This file is the builder's and tester's reference for what "the same" means. Read it before planning any goal.

Two boundaries come first, because they never move:

1. Nothing from Ready Player One's text, names or artwork goes inside the game. No OASIS, Halliday, Anorak, Parzival, Art3mis, Aech, Ludus, Incipio, IOI, Sixers, Gregarious, Copper/Jade/Crystal Key, Cataclyst, and so on. Hub has its own names (section 2). This file may use the original names because it is a reference, not game content.
2. The OASIS is built on real 1980s films, games and music. Those belong to other people. Hub has its own invented culture instead: the founder's own invented games, songs, films and catchphrases (section 9). No real film, game, band, song, character or brand appears in the game.

Everything else about the OASIS is fair game to copy: how it is laid out, how travel and money work, how avatars level and die, how the Hunt is built, how it feels to walk around in it.

## 1. What the OASIS is, in one paragraph

A single, enormous, persistent virtual universe that started life as an online role-playing game and became the place most of humanity spends its days: school, work, shopping, dating, gaming. Joining costs almost nothing once, forever, so everyone is in it. Inside, almost everything costs money, and the in-world currency became more trusted than real money. It is organised as thousands of planets grouped into sectors, each planet a self-contained world with its own genre, look and rules. Players are avatars that can look like anything, gain levels, collect gear, and can lose it all if they die. When its reclusive creator died, he left a video will: three keys hidden somewhere in the universe open three gates, and whoever passes the last gate inherits the universe. That hunt is the spine of the story.

## 2. Hub's own names (use these inside the game)

| The OASIS has | Hub has | Notes |
|---|---|---|
| The OASIS | **Hub** | Already the name of the game. |
| James Halliday, the creator; his wizard avatar Anorak | **Lyle Ashcombe**, "the Architect"; his avatar **Wick**, a tall figure in a grey coat with a lantern | Owner can rename. |
| Ogden Morrow, the co-founder | **Mara Quist**, co-founder, who left the company years ago | |
| Gregarious Simulation Systems | **Ashcombe Simulations** | |
| Incipio (starting planet, Sector 1) | **Hub Spaceport** | Already exists: spawn point. |
| Ludus (school planet) | **Campus** | New realm, Sector 1. |
| Sectors 1 to 27 | **Sectors 1 to 27** | Generic word, fine to keep. |
| OASIS credits | **credits (₵)** | Already exists. |
| Copper, Jade and Crystal Keys | **Amber, Rose and Cyan Shards** | Already exist as the three shards (dunes, grid, sky). |
| Copper, Jade and Crystal Gates | **First, Second and Third Gate** | |
| The Egg | **The Seed** | What the last gate holds. |
| Anorak's Almanac (the creator's book of notes and clues) | **The Ashcombe Ledger** | |
| Anorak's Invitation (the video will) | **The Architect's Last Broadcast** | |
| Halliday's Journals (the film's walk-through archive of his memories) | **The Archive** | Building on Hub Spaceport. |
| The Curator (the Archive's librarian) | **The Registrar** | An NPC. |
| The Scoreboard | **The Ledger Board** | Already exists as the Hunt board. |
| Gunters (egg hunters) | **Seekers** | |
| Clans | **Crews** | |
| IOI (the villain corporation) | **Meridian** | |
| Sixers (IOI's numbered, identical avatars) | **Units** (identical grey avatars, ID numbers starting with 9) | |
| The Cataclyst (sector-wiping bomb) | **The Blackout** | |
| Castle Anorak on Chthonia (dark world with the final gate) | **The Citadel** on **Ashfall** | New realm. |
| Planet Doom (war world) | **Warfront** | New realm, later phase. |
| The Distracted Globe (zero-g dance club) | **The Drift** | A club inside Neon Grid. |
| The Tomb of Horrors (dungeon hiding the first key) | **The Hollow** | A dungeon in Campus's forest. |
| Avatar Outfitters (shop) | **Outfitters** | Shop on Hub Spaceport. |
| Extra Life coin | **The Second Breath** | Unique artifact. |
| Orb of Osuvox (force-field artifact) | **The Bell Jar** | Unique artifact. |

## 3. Layout of the universe

- The OASIS is a cube of 27 sectors, 3 by 3 by 3. Each sector holds many planets. Sector 1 is where new avatars start and where the school planet is. Distance between sectors is real: travel takes time or money in proportion to it.
- Every planet has its own fixed genre and look (a noir city in permanent night, a school world in permanent daytime, a war world, a holiday world, a casino world, a dungeon world, worlds copied from the creator's home town). A planet never changes its look between visits. This already matches Hub's fixed-look rule.
- Planets carry rule flags: magic works or not, technology works or not, both, or neither (a null zone). Player-versus-player combat is allowed on some worlds and banned on others (school and start worlds are safe).
- Each planet has teleport terminals, and bigger planets have malls, quest portals, dungeons, arenas and social spaces.

**Hub version.** A 27-sector cube shown as a star map (the Warp screen grows into it). Sector 1 holds Hub Spaceport, Campus and the four current realms. Other sectors start empty on the map ("uncharted") and fill in as realms are built. Every realm gets a rules line: `{magic, tech, danger}`. `danger:false` means nothing can hurt you there (Spaceport, Campus). `tech:false` disables the jet boost and any gadget; `magic:false` disables any spell item. Realms are real 3D geometry with fixed textures (Poly Haven where possible), never repainted.

## 4. Getting around

- Teleport: instant, from any terminal, priced by distance. New students get school trips free. Poor players walk or fly instead.
- Vehicles: ships and cars that need fuel (costs credits) and take real time to cross space. The hero's own car is a one-off custom build he is proud of.
- Portals between neighbouring locations are free.

**Hub version.** Walking through a portal stays free. Warp fares scale with sector distance: same sector 10₵ (as now), one sector away 25₵, two away 60₵, three or more 120₵. Hub Spaceport is always free to return to. Campus warps are free while the player is "enrolled" (Phase 1). Vehicles come in Phase 3: a hoverbike on the Spaceport pad that costs fuel per second and can fly between realms in the same sector without paying a fare.

## 5. Avatars

- Any shape or size. Real name is private. The school world forces a human look and the real name during class.
- Level 1 to 99. Experience comes from quests, monsters, dungeons and challenges. Level unlocks better gear and shows on the name tag.
- Hit points. Weapons, armour, spells (in magic zones), gadgets (in tech zones).
- Death ("zeroing out"): the avatar drops everything it carried for anyone to loot, the level resets to 1, and it respawns on the start world. In the film, coins burst out of the avatar too. Only a one-of-a-kind extra-life artifact can save you, once. This rule is what makes the whole hunt tense.
- Inventory: items, artifacts, vehicles, credits. Artifacts are unique: exactly one copy exists in the entire universe, each with a named power.

**Hub version.** The avatar can be anything, and the player gets it by describing it in words. See section 5a for the whole system. Keep the rule that the avatar only changes when the player changes it (describing it is changing it). Add: HP (100 at level 1, +5 per level), a level cap of 99, an inventory panel (I key), items with rarity, artifacts as unique named items. Zero-out rule exactly as above: on death in a danger realm the player drops a loot bundle containing every item and all credits at the death spot, level and XP reset to 1, respawn on Hub Spaceport, and the bundle stays for that session so the player can run back for it. The Second Breath artifact cancels one death and is consumed.

## 5a. Describe your avatar and the game makes it

The owner's rule: the avatar can be whatever the player wants. They type a description, the AI turns it into an avatar. "A tall chrome knight with a red cape and glowing blue eyes." "A small fox in a hoodie." "A blob of green jelly with one eye." All of these must produce something that looks like the words.

**Recipe.** Every avatar in the game is built from one JSON recipe. The recipe is the contract between the words and the mesh:

```
{ body: "humanoid" | "robot" | "beast" | "blob",
  height: 0.6–2.4 (metres), build: "slim" | "normal" | "heavy" | "huge",
  head: "helmet" | "visor" | "bare" | "animal" | "skull" | "screen",
  features: ["ears","snout","horns","tail","wings","cape","hood","backpack","jetpack","sword","staff","antenna","halo","crown","mask","spikes"],
  material: "cloth" | "matte" | "plate" | "chrome" | "glass" | "fur" | "jelly" | "stone" | "neon",
  pattern: "none" | "stripes" | "plates" | "circuits" | "camo" | "checks",
  colours: { main, second, trim, glow } (hex), eyes: { style: "visor" | "dots" | "wide" | "slits" | "one", glow: hex },
  face_texture: <optional data-URL, from the AI image model>,
  voice_line: <one line the avatar says on the Ledger Board, optional> }
```

**Recipe to mesh.** The current avatar builder (hips, spine, head, arms, legs, walk and jump animation) becomes the humanoid skeleton every body type hangs off. Robot: harder shapes, joints visible, screen or visor head. Beast: same skeleton, digitigrade legs, snout, ears, tail, fur material (dense short fins along the silhouette, not a fur shader). Blob: a displaced sphere on the hips node that squashes with the walk cycle, features stuck on. Height and build scale the skeleton; the walk animation, collider radius and camera height read the scale. Every feature is a small procedural part attached to a named node (cape on the shoulders, tail on the hips, wings on the spine, horns on the head). Materials are MeshStandard or MeshPhysical presets. Patterns are canvas textures. The name tag and the halo still work.

**Words to recipe, three paths, best available one wins.**
1. Always works, no key, no network: an on-device parser with a big vocabulary. Colours (all common names plus "gold", "chrome", "neon pink"), sizes ("tall", "tiny", "giant", "short"), builds ("slim", "muscular", "chunky"), species and body words ("robot", "android", "knight", "fox", "wolf", "cat", "dragon", "blob", "ghost", "astronaut"), materials, features, eye words. Unknown words are ignored. This is the floor: every description gives a sensible avatar.
2. Local file plus a key: the description goes to a language model that returns the recipe JSON directly, so any wording works ("looks like a lighthouse keeper who fell in a vat of paint"). The game validates the JSON against the recipe schema and falls back to path 1 for anything invalid. Use an OpenAI-compatible chat endpoint or the Anthropic messages endpoint with the player's own key, stored on the device like the Decart key. The prompt to the model carries the schema and three examples.
3. Local file plus the Decart key: the description also goes to the image model (lucy-image-2, already used for textures) to make a 1024px face or skin panel and a portrait; the face goes on the head or chest as a decal, the portrait sits beside the name on the Ledger Board. Cached in IndexedDB with the recipe.

**Flow.** On the intro card: a text box "Describe your avatar", a "Make it" button, a live preview of the avatar turning slowly, "Try again" (re-runs with a different seed for the details the words do not fix), and the old suit and glow swatches under "Fine-tune". The recipe saves with the game. The avatar is exactly the same on every visit until the player describes a new one. "Reset" gives the default suit.

**NPCs.** Every NPC gets a random recipe from a list of two hundred short descriptions run through path 1, so the Spaceport is full of different shapes, sizes and species. That is the single biggest thing that makes the universe feel like the OASIS.

**Done means.** Typing "a tall chrome knight with a red cape and glowing blue eyes" gives a visibly tall, chrome, caped avatar with blue eye glow that walks, runs, jumps and boosts with the existing animation, collides with the world at its new size, keeps its name tag, and is still there after a reload. "A small fox in a hoodie" gives a short beast body with ears, snout, tail and a hood. Ten NPCs on the Spaceport look different from each other. Path 2 and path 3 are only checked in the local file with keys present; without keys the game never asks for them just to make an avatar.

## 5b. The Worldsmith: describe a realm and the game builds it (built; keep it working)

The OASIS let anyone build a world. Hub's version is the Worldsmith (F key, the Forge button, or the Worldsmith stand on the Spaceport): the player types or speaks a sentence and a realm is built from it, seeded by the sentence so the same words always give the same realm. `parseRealm` reads the land (plains, hills, mountains, island, archipelago, coast, canyon, crater, valley, dunes, flat, swamp), the ground (grass, lawn, meadow, sand, snow, ash, rock, gravel, forest floor, moss, soil, martian), water (lake, sea, lava, acid, ice, swamp), the time of day (dawn to midnight), weather (clear, cloudy, overcast, fog, storm, rain, snow, sandstorm, embers), trees (leaf, jungle, pine; dense or sparse; dead; autumn; blossom), extras (mushrooms, crystals, flowers, fireflies, lanterns, aurora, moons, a ringed planet, cactus, bamboo, boulders, geysers, a volcano), buildings (ruins, temple, tower, castle, village, city, lighthouse, statues, monoliths, pyramid, arch, windmill), colours next to a thing ("purple sky", "black sand", "red trees"), and a name ("called X"). Realms are saved on the player's computer (`hub-realms-v1`), get a sector of their own on the star map (2 to 27), have a portal back to the Spaceport, and warping to your own realm is free. They have no coins (the coin total belongs to the charted universe). Done means: ten different sentences give ten realms that match their words, and a saved realm comes back identical after a reload.

## 5c. Endless realms and the Dreamer (built; keep it working)

A forged realm has no edge. The ground disc is re-centred on the player as they walk (`recenterTerrain`), the grass field refills around them, water follows them, and the land is built in 48 m cells as they approach (`buildChunk`) and taken down behind them (`dropChunk`). About one cell in five holds a landmark with a name and a line of lore: a "dream". Dreams come from the Dreamer (`askDreamer`): on the claude.ai link the page asks Claude (the `sample` capability, the viewer allows it once, eight landmarks per ask, "quick" tier); in the downloaded file an Anthropic API key pasted in the Worldsmith panel does the same; with neither, the game invents them from its own word lists (`dreamOffline`). Every dream is a sentence built from the Worldsmith's building blocks, so the same parser builds it. Walking within 26 m of a landmark reads its lore, pays 15 XP and 3 credits, and writes it to the realm's log (saved with the realm, shown in the Worldsmith panel). Done means: walking 500 m in any direction never reaches an edge, landmarks keep appearing, and with Claude allowed the names and lore are ones the code does not contain. "small" or "bounded" in a description keeps the old walled realm.

## 5d. VR (built; untested on a headset so far)

`vrSetup` shows a VR button when WebXR reports an immersive-vr device. Entering VR puts the camera on a rig standing where the avatar stands (`vr.rig`, local-floor reference space): the left stick walks relative to where you look, the right stick snap-turns 30 degrees, the trigger jumps, the grip or A is E. VR renders without the post chain (two eyes, plain render). The claude.ai link's frame does not allow WebXR; the downloaded file served over https (or opened in a headset browser) does.

## 6. Money

- Joining is a one-off tiny fee; after that everything inside costs: teleports, fuel, ammunition, gear, food, clothing, rent for private rooms.
- Credits come from monsters, dungeon treasure, quests, selling loot, and, for the rich, real money.
- The currency is stable enough that people are paid in it.

**Hub version.** Coins on the ground stay as the beginner's income. Add credit rewards to quests and monster kills, a sale price for every item, and shops that buy and sell: Outfitters (suits, glows, capes, helmets) and a vending terminal on each realm (fuel cells, ammo, health kits). Prices in whole credits. Nothing costs real money, ever.

## 7. Things to do on a planet

- Quest portals: step in, get a self-contained mission with a reward of credits, XP and sometimes an item.
- Dungeons: hand-built, dangerous, with monsters, traps and a treasure hoard. The first key was hidden in one.
- Arenas and arcades: the creator loved old arcade cabinets; several challenges are played on one.
- Social spaces: malls, clubs (the zero-g dance club), a haunted hotel, holiday resorts, casinos.
- Private chat rooms: instanced spaces a player owns and decorates, where friends meet. The hero's best friend hosts one styled as a basement.
- Schools: identical campuses across the school planet, marble halls, cathedral classrooms, zero-g gym, teachers freed from discipline because the software handles it.

**Hub version.** Each realm gets at least one quest portal (a glowing doorway with a name and reward on its label). Campus gets the school building (walk-in, a classroom, a zero-g gym you can bounce in) and, hidden in its forest, The Hollow: a dungeon with three rooms, traps, monsters, a treasure room, and an arcade cabinet where the first shard is won. Neon Grid gets The Drift: a zero-g dance floor where gravity is off inside the sphere. The player gets one private room ("Den") reachable from the Spaceport, with a few decor items to buy and place; it saves.

## 8. Enemies and danger

- Monsters and NPC enemies on danger worlds, from small creatures to giant robots.
- The villain corporation: it hunts with thousands of identical numbered avatars, buys the best gear, cheats with force fields around key sites, drains debtors into indentured work, and in the end drops a bomb that kills every avatar in a sector.
- The last battle: every seeker in the universe against the corporation's army in front of the final gate.

**Hub version.** Phase 3. Monster types per realm (sand wraiths in Glass Dunes, grid drones in Neon Grid, grove stalkers in Night Grove, sky harpies in Sky Isles). Meridian Units patrol key sites once the player holds a shard, identical grey avatars with 9-prefixed IDs. The Bell Jar artifact throws a force field over the Citadel until the player finds the way to break it. The Blackout is a scripted event at the end of the Hunt: every avatar on Ashfall zeroes out, including the player, and only The Second Breath brings them back.

## 9. The Hunt

The creator's will: a video (the Architect's Last Broadcast) announcing that three keys hidden in the universe open three gates, and the Seed behind the last gate is ownership of everything. He left a book of notes full of riddles (the Ledger). Five years pass before anyone finds the first key. A public scoreboard shows the leaders.

Shape of it in the book: each key is found by solving a riddle from the book, going to the right place, and beating a challenge there (an arcade duel against the creator's ghost in a dungeon; a perfect game on an arcade cabinet; playing a piece of music correctly on a particular instrument). Each key opens a gate, and each gate is a test of devotion (reciting a whole film word for word, playing a game, re-enacting scenes). The last gate needs three players with all three keys at once, so nobody can win alone. Inside the final gate: more games, then the creator's ghost, who asks whether the winner will look after the place.

Shape of it in the film: a race nobody can win until someone drives backwards; a dance club that opens into a horror hotel where you must not be fooled by fear; and the creator's favourite old game where the prize is refusing to take the bait at the end. The archive of the creator's memories holds the clues.

**Hub version.** Everything about the Hunt is original content written for Hub: the Architect's life, the Ledger's riddles, the invented arcade games, the invented songs.

- The Ledger: a readable in-game book (from the Archive or the ? menu) with one riddle per shard, plus red herrings.
- The Archive on Hub Spaceport: a library where each room replays one memory of Lyle Ashcombe's life as a still scene with a short text and a hidden detail. The Registrar NPC answers questions with quotes from the Ledger. Clues live here.
- Amber Shard (Glass Dunes): riddle points to a specific sandstone pillar at a specific time of day; a challenge cabinet inside a buried chamber runs **Comet Rally**, an invented top-down racer, and the shard is won by driving the wrong way round the track on the last lap.
- Rose Shard (Neon Grid): riddle points to The Drift; the club's back wall opens into a hotel corridor that tries to scare the player off with fake-outs; keep walking without turning back to reach the shard.
- Cyan Shard (Sky Isles): riddle is a musical phrase; a set of wind chimes on the highest isle must be struck in the right order (the Architect's invented lullaby, "Low Tide").
- Each shard opens a gate on Ashfall. Gate One: repeat the Architect's broadcast, line by line, choosing the right line from three each time. Gate Two: play **Starling**, an invented one-screen shooter, to a set score. Gate Three: walk the Architect's childhood street (a memory from the Archive) and choose not to take the credits pile at the end; the Seed is behind the empty choice.
- The Citadel on Ashfall: dark world, permanent dusk, the three gates set in a castle wall, the Bell Jar field over it until the Bell Jar is broken, Meridian Units in numbers, then the Blackout, then the Seed.
- The Ledger Board (existing Hunt board): shows the player and the NPC seekers with their shard count and score.
- Multiplayer is parked, so the "three players at once" rule becomes: the three shards must be socketed together in the Citadel's vault door (the existing vault mechanic).

## 10. The company, the hardware, the world outside

- The creator: reclusive, brilliant, shy, obsessed with the decade he grew up in, never got over one unrequited love, died rich and alone. His co-founder was the warm one who left when the company stopped feeling like a game.
- Players wear a visor and haptic gloves; the rich have full rigs (a suit, an omnidirectional platform, a chair, even a smell tower). The universe closes down two days a week at the end of the film so people go outside.
- Outside the game the world is broke, hot and crowded; stacked trailer parks; the company's debtors work in loyalty centres.

**Hub version.** Flavour only. Lyle Ashcombe's story is told through the Archive rooms and the broadcast. The intro card gets one line of world-setting. Nothing about real hardware is needed.

## 11. How it feels (the tester checks these too)

- Scale: standing on Hub Spaceport you can see that there is far more out there than you can reach yet (the star map shows 27 sectors, most uncharted).
- Solidity: every world is ground you can trust, with real geometry and fixed textures.
- Identity: your avatar is yours; the name tag shows your name and level; other avatars look nothing like you.
- Stakes: a danger realm feels different from a safe one, and dying costs you.
- Wonder: each realm is a genre of its own, with its own sky, light, sound and residents.
- Neon and nostalgia: Hub's own invented old games and songs are everywhere in the Spaceport and Neon Grid, not real ones.

## 11a. Picture quality: the owner's first goal

The owner's words: make it look more realistic than GTA 6. Not "realistic" as in what the world is made of (the realms stay stylised genres), but realistic as in pixels: sharp, clean, high-quality rendering with nothing cheap-looking on screen. This comes before every other feature. Never trade sharpness or frame rate for a feature; if a feature costs quality, it waits.

Honest ceiling: a one-file three.js r128 game in a browser cannot match a console engine's asset budget, but it can be as clean and sharp as the best browser games, and that is the bar. Everything below is standard three.js r128 and runs from the single index.html. The three.js example scripts (postprocessing, shaders, CSM) may be loaded as plain non-module scripts from cdn.jsdelivr.net/npm/three@0.128.0/examples/js/... (the published link allows jsdelivr; cdnjs does not carry the examples).

What "quality" means here, in order of visible impact:
1. **Resolution and edges.** Render at the full device pixel ratio (cap 2 on desktop, 1.5 on phones), MSAA on, plus an SMAA pass so no edge shimmers. Text and UI stay crisp.
2. **Shadows.** Cascaded shadow maps (THREE.CSM from the examples) with three cascades, 2048 each on desktop, soft PCF, tuned bias so there is no acne and no peter-panning. Everything casts and receives, including grass tufts near the player.
3. **Ambient occlusion.** SSAO or SAO pass from the examples, subtle radius, so rocks, pillars, feet and doorways sit into the ground instead of floating.
4. **Light.** Physically based: sun + sky environment map (PMREM from the sky shader, already there) + hemisphere fill. ACES tone mapping with a per-realm exposure. Bloom pass, subtle, only on emissive glows (portals, neon, shards), never on the whole image. Optional light shafts in Glass Dunes and Night Grove using a cheap radial-blur pass.
5. **Surfaces.** Every material gets roughness and normal detail; large surfaces get a second detail normal map tiled small so nothing looks flat close up. Procedural textures go to 1024–2048 px. Poly Haven textures (local file) go to 2k with normal, roughness and AO maps. Anisotropy 16. Wet-look variation on the Neon Grid floor, dust on the sandstone, moss on grove rocks.
6. **Geometry.** Terrain tessellation dense near the player and coarser far away (the current ring layout already does this; raise the near density). Rocks and pillars with more subdivisions and layered displacement, no visible facets at arm's length. Trees with layered canopies; grass as alpha-tested blade cards with a wind shader, thicker near the player. Distant objects get a lower-detail version (THREE.LOD).
7. **Atmosphere.** Height fog that tints with distance (aerial perspective), a proper sky gradient with a bright sun disc and glare, clouds that catch the light, stars at night that twinkle. Each realm keeps its own look; only the quality goes up.
8. **Motion.** A steady 60 fps on a normal laptop, 30 on a phone, with frame time measured and a quality ladder that steps down in this order when it drops: light shafts, SSAO, bloom, shadow cascade count, pixel ratio. It never steps below "sharp edges and shadows".

The AI reality mode (R) must keep working on top of the new pipeline: the AI sees the composed world image, avatars still draw on top.

**Done means (checked by the tester with 1920x1080 screenshots in every realm, from the local file):** no jagged edges anywhere, soft shadows with no acne, visible occlusion under rocks and at the base of pillars, subtle bloom on glows only, no flat-looking surfaces within ten metres, no popping when walking, no console errors, and a logged frame time under 16.7 ms on the tester's machine at pixel ratio 1 (or the ladder's first step applied automatically). Before/after screenshots are committed under `shots/` so the owner can see the difference.

## 11b. Real School: Hub's mission (the owner's goal)

The owner's words: host real classrooms in Hub and give Orox glasses to children in need so they can go to school. In the book, the school world is what gave poor children a real education; Hub wants that for real, not only as fiction. Campus (goal 8) is the building; this section is everything a real school needs on top of a game.

It is a different product from the game, with real children in it, so five things come first and in this order. None of it starts until the owner unparks multiplayer (CLAUDE.md), and none of it ships to real children until item 2 is reviewed by someone qualified in child safety and privacy law.

1. **Live classes (needs multiplayer).** A teacher and up to 30 students in the same Campus classroom at the same time: avatars in seats, teacher voice to the room, hand-raising, a shared lesson board the teacher controls (slides, drawing, text), and the teacher able to mute, move and bring everyone to one spot. Break-out rooms for group work. Attendance recorded per lesson.
2. **Child safety, designed in from the start.** Accounts are created by a school or a guardian, never self-sign-up for under-16s. Children can only meet their own class and teachers; no contact from strangers, no open chat, no friend requests from outside the school. Teachers and moderators can see logs; there is a report button in every room. Collect the least data possible, no ads, no selling data, no tracking. Follow the child-privacy law of every country served (for example COPPA in the US, GDPR and the UK Age Appropriate Design Code in Europe). The money and danger systems (credits, zero-out, Meridian) are switched off inside school accounts' lessons.
3. **Runs on cheap devices and weak internet.** A "School" quality profile for a low-cost Android phone on a slow, patchy connection: small download, cached after first load, works offline for already-downloaded lessons, lower resolution but still clean (sharp edges and readable text come before effects, as in section 11a). Audio-first so a lesson survives when video would not.
4. **Teachers and lessons.** Hub gives the room; real educators give the school. Work with teachers, schools and curriculum partners; lessons are content they create and own. Tools for them: a lesson builder, a way to bring in their own slides and worksheets, simple homework and marks. Hub's invented-culture rule still applies inside the game world, but lesson content is whatever the teacher teaches.
5. **Orox glasses.** Start with the cheapest thing that works: a phone headset (a plain lens-and-strap holder) running Hub's existing WebXR mode (section 5d) in the phone's browser, so the only hardware to give out is the headset, plus a phone where the child has none. Every lesson must also work without the glasses, on the phone screen alone, so no child is shut out if the headset breaks. Distribution through charities and schools, who decide which children qualify; Hub does not collect income data about families.

**How it feels.** A child in a poor, crowded place puts on the glasses and is in a bright marble hall with their class. It must feel safe, calm and dependable first, and wondrous second.

## 12. Roadmap (work in order; every goal is a builder task list checked by the tester)

**Phase 0 (in progress): Glass Dunes looks like a real desert.** Finish the current task list first; it is the first realm to hit the section 11a bar, so do it to that standard.

**Phase 1: the spine.**
1. **Picture quality**, exactly as section 11a, applied to every realm. Done means: section 11a's done line.
2. **Describe-your-avatar**, exactly as section 5a. Done means: section 5a's done line.
3. Rules line per realm (`magic`, `tech`, `danger`) and the star map (27-sector cube, Sector 1 charted, others uncharted). Done means: the Warp screen shows the cube, each realm shows its sector and rules, and jet boost is disabled in a `tech:false` realm.
4. Distance-priced warps. Done means: fares match section 4 and the Spaceport is always free.
5. HP, damage and the zero-out rule with respawn and the loot bundle. Done means: taking 100 damage in a danger realm drops a bundle, resets level, respawns on the Spaceport, and picking the bundle up restores the items and credits.
6. Inventory panel (I key) with items, rarity and sale price. Done means: an item can be picked up, seen, and sold at Outfitters.
7. Outfitters shop on Hub Spaceport and a vending terminal in every realm. Done means: buying a cape changes the avatar and persists; buying a health kit and using it restores HP.
8. Campus realm in Sector 1: perpetual daytime, a school building, a zero-g gym, a forest, free warps while enrolled. Done means: the portal from the Spaceport works, the gym has no gravity, the realm is `danger:false`.

**Phase 2: the Hunt.**
9. The Archive on the Spaceport with six memory rooms, the Registrar, and the Ledger book. Done means: every room opens, the Ledger is readable, and one hidden detail per room can be inspected.
10. The Architect's Last Broadcast as the intro to the Hunt (plays once, replayable from the Archive).
11. Amber Shard: The Hollow dungeon under Glass Dunes' chamber and the Comet Rally cabinet. Done means: the shard is only won by the backwards last lap.
12. Rose Shard: The Drift and the hotel corridor.
13. Cyan Shard: the wind chimes and "Low Tide".
14. Ashfall and the Citadel with three gates and the vault; the Seed; the winning card.

**Phase 3: a living universe.**
15. Quest portals in every realm with credit and XP rewards.
16. Monsters per realm with loot.
17. Artifacts: The Second Breath, The Bell Jar, plus three more with named powers, one copy each.
18. Meridian Units, the Bell Jar field and the Blackout event.
19. Vehicles: the hoverbike with fuel.
20. New realms, one at a time: Warfront, a noir city, a holiday isle, a casino, a memory copy of the Architect's home town. (The Worldsmith, section 5b, can rough any of these out from a sentence; a hand-built realm then replaces it.)
21. The Den (private room) with decor.

**Phase 4: polish.** Performance on phones, sound per realm, save slots, accessibility. Multiplayer stays parked until the owner says otherwise.

**Phase 5: Real School (section 11b; starts only when the owner unparks multiplayer, and ships to real children only after a child-safety and privacy review).**
22. Multiplayer foundation for Campus only: two or more players see each other move in the same classroom. Done means: two browsers join one classroom and see each other's avatars move within half a second.
23. Live class: teacher role, seats, voice to the room, hand-raising, a shared lesson board the teacher controls, attendance. Done means: a teacher runs a ten-minute lesson for five test students end to end.
24. School accounts and safety: school- or guardian-created accounts, class-only contact, report button, moderator log, no money or danger systems in lessons. Done means: a student account cannot see, hear or message anyone outside its class, and every report reaches the log.
25. School quality profile: small first download, offline cache for lessons, runs at 30 fps on a low-cost Android phone with readable text and sharp edges. Done means: the tester's low-end profile loads a lesson under a set size limit and holds 30 fps.
26. Lesson tools for teachers: lesson builder, import slides and worksheets, homework and marks. Done means: a teacher builds a lesson from their own slides without help.
27. Orox glasses: phone-headset mode checked on real headsets, with every lesson also working on the phone screen alone. Done means: one lesson completed on a headset and the same lesson completed without one.

## 13. Sources this file was written from

Summaries of the book and film on Wikipedia (the novel and the film pages), the Ready Player One fan wiki pages for the OASIS worlds, Ludus and Incipio, the EN World thread on the OASIS as a role-playing setting, the TV Tropes page for the novel, and Den of Geek's book-versus-film comparison. All descriptions above are paraphrased; none of the original text is reproduced.

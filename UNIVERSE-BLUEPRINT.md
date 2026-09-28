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

**Hub version.** Keep the existing suit and glow customiser (the avatar only changes when the player changes it). Add: HP (100 at level 1, +5 per level), a level cap of 99, an inventory panel (I key), items with rarity, artifacts as unique named items. Zero-out rule exactly as above: on death in a danger realm the player drops a loot bundle containing every item and all credits at the death spot, level and XP reset to 1, respawn on Hub Spaceport, and the bundle stays for that session so the player can run back for it. The Second Breath artifact cancels one death and is consumed.

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

## 12. Roadmap (work in order; every goal is a builder task list checked by the tester)

**Phase 0 (in progress): Glass Dunes looks like a real desert.** Finish the current task list first.

**Phase 1: the spine.**
1. Rules line per realm (`magic`, `tech`, `danger`) and the star map (27-sector cube, Sector 1 charted, others uncharted). Done means: the Warp screen shows the cube, each realm shows its sector and rules, and jet boost is disabled in a `tech:false` realm.
2. Distance-priced warps. Done means: fares match section 4 and the Spaceport is always free.
3. HP, damage and the zero-out rule with respawn and the loot bundle. Done means: taking 100 damage in a danger realm drops a bundle, resets level, respawns on the Spaceport, and picking the bundle up restores the items and credits.
4. Inventory panel (I key) with items, rarity and sale price. Done means: an item can be picked up, seen, and sold at Outfitters.
5. Outfitters shop on Hub Spaceport and a vending terminal in every realm. Done means: buying a cape changes the avatar and persists; buying a health kit and using it restores HP.
6. Campus realm in Sector 1: perpetual daytime, a school building, a zero-g gym, a forest, free warps while enrolled. Done means: the portal from the Spaceport works, the gym has no gravity, the realm is `danger:false`.

**Phase 2: the Hunt.**
7. The Archive on the Spaceport with six memory rooms, the Registrar, and the Ledger book. Done means: every room opens, the Ledger is readable, and one hidden detail per room can be inspected.
8. The Architect's Last Broadcast as the intro to the Hunt (plays once, replayable from the Archive).
9. Amber Shard: The Hollow dungeon under Glass Dunes' chamber and the Comet Rally cabinet. Done means: the shard is only won by the backwards last lap.
10. Rose Shard: The Drift and the hotel corridor.
11. Cyan Shard: the wind chimes and "Low Tide".
12. Ashfall and the Citadel with three gates and the vault; the Seed; the winning card.

**Phase 3: a living universe.**
13. Quest portals in every realm with credit and XP rewards.
14. Monsters per realm with loot.
15. Artifacts: The Second Breath, The Bell Jar, plus three more with named powers, one copy each.
16. Meridian Units, the Bell Jar field and the Blackout event.
17. Vehicles: the hoverbike with fuel.
18. New realms, one at a time: Warfront, a noir city, a holiday isle, a casino, a memory copy of the Architect's home town.
19. The Den (private room) with decor.

**Phase 4: polish.** Performance on phones, sound per realm, save slots, accessibility. Multiplayer stays parked until the owner says otherwise.

## 13. Sources this file was written from

Summaries of the book and film on Wikipedia (the novel and the film pages), the Ready Player One fan wiki pages for the OASIS worlds, Ludus and Incipio, the EN World thread on the OASIS as a role-playing setting, the TV Tropes page for the novel, and Den of Geek's book-versus-film comparison. All descriptions above are paraphrased; none of the original text is reproduced.

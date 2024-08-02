# Editor

It may become apparent that there is no need for an update function on an entity because it doesn’t change its data on a frame-by-frame basis in response to real time input but rather everything falls under this turn based construct. To make this even more clear, the scripting is only used in the context of the combat loop. Which means it is part of the full tech stack Website <-> Server -> Table <-> Scripts. This stack does not exist in the pre-game functionality of the table aka edit/prep mode. In edit mode the table is the only thing running, the Lua scripting is only used to collect a list of monster prefabs (we may find it easier to just use a json table of all the monsters available and a path to their token images.) 

The way edit mode is going to work is as if it has no clue what the game mode is going to do, when the game will be played, or how the game will be paused and left for later. This means the editor needs to make as few assumptions as possible and store very robust data. This is where the campaign filesystem comes in. Below you can see a tree of how files will be sorted.

```
campaigns/
├─ game1/
│  ├─ characters/
│  │  ├─ boblin.json
│  │  ├─ clifford.json
│  ├─ maps/
│  │  ├─ town.map
│  │  ├─ dungeon.map
```

The map file format will store a couple different data fields. It may be discovered that a custom file format is redundant, and we move to just using json, but for now the idea is as follows. The first chunk is the texture data for the map which has been serialized into RGBA, if there are multiple floors to a map then there will be more than one texture. Presently it would be required for all multilevel maps to have each texture the same size. If a user wanted to make multilevel maps without this constraint, they can just be separate maps and then have the spawns line up.

The next chunk of the map file is the collision tables for each floor. Collision tables are not just for walkable vs not walkable but also store data on if a tile is difficult terrain, a spawn point, an exit point, or even a customizable trigger zone to pre-register events like perception checks into areas of the map.

The last chunk of the map file is the entity table which lists out all the entities in each floor and their spawn points. There should be no need to define starting component values for an entity since all monsters are predefined and character init data is in json files. (custom enemies/bosses will similarly have a json format it just hasn’t been concepted yet)


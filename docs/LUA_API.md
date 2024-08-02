# Lua API Design

## Conceptual Rework of Entities

From here on out if entities need to malloc RAM or load assets into VRAM those methods will be called during the instantiate method for an entity. Then there will be a destroy method (previously free) on each entity prefab that will deallocate any assets it initialized. This method will be called by world by default, if an entity doesn’t need a destroy method world will notice that and just go on with removing the entity from the entity table. Since Lua is garbage collected since no more references to the entity object itself will exist the GC will eventually come along and take care of the rest.

## Image Drawing

Load image method: give path to C and it loads it onto memory but since a raylib texture struct is just an OpenGL texture we need to have the API method return the Texture2D struct as Lua user data. (I know there’s a guide in the Lua manual on this)
Draw image method: give the C API a Texture2D and it will draw it.
Unload image method: give the C API a Texture 2D and it will unload it 

## Getting Server Data

The Lua world has no concept of the Python server that is getting messages from the website, so it is the responsibility of the table to inform the Lua world. Any time the table wants to share new data from the server with Lua it must use the publicly facing functions in world.lua 

For example, a monster making an attack is informed by input from the website instead of by the monster entity in Lua. So, the table will tell the AI to make a choice and then when the choice is made the attack can just target a player entity internally. When a player makes an attack all the data on the attack is already known by the table so it instead can just tell Lua to update the health of the impacted entities. Being aware of these dynamics is important when thinking about how to handle server messages but also handling persistent (conditions, concentration spells, etc.) and other Lua internal communication. 

To handle this there should be a way for the C program to directly signal a single entity or set of entities by ID. In order to streamline this process, it will probably be best for world.lua to provide contextual getter methods to return IDs of entities that meet a classification (location, is player/is monster, etc.)

In short, this new model changes from a real time event/handler model to more of a peer to peer model where C and Lua directly ask for data through the world.lua as a sort of protocol to concisely dictate how communication can happen. 

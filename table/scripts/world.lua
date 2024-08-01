-- include all prefabs needed
local Token = require("token")

-- is a global since C may need to read
-- the entity table
World = { count = 0, entities = {}}

-- add and remove will also be used by the
-- C code to add/remove from the World
function add_entity(entity)
    World.count = World.count + 1
    table.insert(World.entities, entity)
end

function remove_entity(entity)
    for i, e in ipairs(World.entities) do
        if e.id == entity.id then
            table.remove(World.entities, i)
            return
        end
    end
end

function init()
    -- add any entities that exist at start
    add_entity(Token:instantiate(World.count, "test.png", "test"))
end

function update()
    for _, e in ipairs(World.entities) do
        e:update()
    end
end

function draw()
    for _, e in ipairs(World.entities) do
        e:draw()
    end
end
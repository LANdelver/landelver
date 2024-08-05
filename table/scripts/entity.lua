local Entity = {}
Entity.__index = Entity

function Entity:new(id)
    return setmetatable({id = id, components = {}}, self)
end

return Entity
local System = {}
System.__index = System

function System:new(requiredComponents)
    local instance = setmetatable({requiredComponents = requiredComponents or {}, entities = {}}, self)
    instance:init()
    return instance
end

function System:addEntity(entity)
    for _, componentName in ipairs(self.requiredComponents) do
        if not entity:getComponent(componentName) then
            return
        end
    end
    table.insert(self.entities, entity)
end

function System:removeEntity(entity)
    for i, e in ipairs(self.entities) do
        if e.id == entity.id then
            table.remove(self.entities, i)
            return
        end
    end
end

-- override in instance
function System:init()
end

function System:update()
end

function System:draw()
end

return System
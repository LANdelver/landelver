local Entity = {}
Entity.__index = Entity

function Entity:new(id)
    return setmetatable({id = id, components = {}}, self)
end

function Entity:addComponent(componentName, component)
    self.components[componentName] = component
end

function Entity:getComponent(componentName)
    return self.components[componentName]
end

function Entity:removeComponent(componentName)
    self.components[componentName] = nil
end

return Entity
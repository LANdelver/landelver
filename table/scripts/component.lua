local Component = {}
Component.__index = Component

function Component:new(componentData)
    local instance = setmetatable({componentData}, self)
    -- automatically call init on new
    instance:init()
    return instance
end

-- to be overriden by instance
function Component:init()
end

function Component:remove()
end

return Component
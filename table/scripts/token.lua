local Entity = require("entity")
local common = require("common")
local landelver = require("landelver_api")

-- token entity prefab
local Token = setmetatable({}, { __index = Entity})
Token.__index = Token

function Token:instantiate(id, icon, label)
    local instance = Entity:new(id)
    local pos = common.pos(0, 0)
    instance:addComponent("pos", pos)
    instance:addComponent("icon", icon)
    instance:addComponent("label", label)
    setmetatable(instance, Token)
    return instance
end

function Token:update()
    print("token is updating")
end

function Token:draw()
    local x = self:getComponent("pos").x
    local y = self:getComponent("pos").y
    landelver.draw_text(self:getComponent("label"), x, y)
end

function Token:free()
    print("Token is freeing assets")
end

return Token
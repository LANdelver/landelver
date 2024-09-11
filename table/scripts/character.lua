local Entity = require("entity")
local common = require("common")
local landelver = require("landelver_api")

-- token entity prefab
local Token = setmetatable({}, { __index = Entity })
Token.__index = Token

local pos = common.pos(0, 0)
local image = {}
local charSheet = {}

function Token:instantiate(id)
    local instance = Entity:new(id)
    charSheet = landelver.get_character("./resources/players/boblin.json")
    local imgPath = string.format("./resources/players/%s.png", charSheet.name);
    image = landelver.load_image(imgPath)
    setmetatable(instance, Token)
    return instance
end

function Token:draw()
    local x = pos.x
    local y = pos.y
    landelver.draw_text(charSheet.name, x, y - 10)
    image:draw(x, y)
end

function Token:destroy()
    print("Token is freeing assets")
    image:unload()
end

return Token

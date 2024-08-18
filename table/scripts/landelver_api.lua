local api = {}

function api.draw_text(text, x, y)
    draw_text(text, x, y)
end

function api.load_image(filename)
    local tex = load_image(filename)
    return tex
end

function api.get_character(filename)
    local character = get_character(filename)
    return character
end

return api

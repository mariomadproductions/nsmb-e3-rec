-- Ported from the NSMB E3 Recreation NSMBe plugin's MushroomPlatform. It
-- replaces the vanilla 189, whose settings E3MushroomPlatform.cpp reinterprets.

local images = {}

local function init(ctx)
    for _, color in ipairs({ "r", "g" }) do
        for _, cap in ipairs({ "b", "s" }) do
            images["edge_" .. color .. cap] = ctx.loadImage("images/mplat_" .. color .. "_1_" .. cap .. ".png")
            images["section_" .. color .. cap] = ctx.loadImage("images/mplat_" .. color .. "_2_" .. cap .. ".png")
        end
    end
    images.stalk_b = ctx.loadImage("images/mplat_s_b.png")
    images.stalk_s = ctx.loadImage("images/mplat_s_s.png")
end

local function grabBounds(actor)
    local length = actor.fields.length
    return {
        x = actor.pixelX - 16 * (length + 1),
        y = actor.pixelY,
        width = 32 * (length + 2),
        height = 65 + 16 * actor.fields.stalk_height,
    }
end

local function render(actor, renderer)
    local color = actor.fields.color == 1 and "g" or "r"
    local cap = actor.fields.slim_platform and "s" or "b"
    local edge = images["edge_" .. color .. cap]
    local section = images["section_" .. color .. cap]
    local stalk = actor.fields.fat_stalk and images.stalk_b or images.stalk_s

    local box = grabBounds(actor)
    local drawn = renderer:draw(stalk, {
        x = actor.pixelX,
        y = actor.pixelY + 24,
        width = 32,
        height = 41 + 16 * actor.fields.stalk_height,
    })
    for column = 1, actor.fields.length do
        drawn = renderer:draw(section, { x = box.x + 32 * column, y = box.y, width = 32, height = 24 }) or drawn
    end
    drawn = renderer:draw(edge, { x = box.x, y = box.y, width = 32, height = 24 }) or drawn
    return renderer:draw(edge, {
        x = box.x + box.width - 32,
        y = box.y,
        width = 32,
        height = 24,
        flipX = true,
    }) or drawn
end

return {
    objectId = 189,
    name = "E3 2005 Mushroom Platform",
    category = "Platforms and ropes",
    notes = "The mushroom platform as the E3 2005 demo had it, with a slim cap, a fat stalk and a green color to choose from.",
    fields = {
        {
            key = "fat_stalk",
            label = "Fat stalk",
            bitOffset = 28,
            bitWidth = 1,
            checkboxValue = 1,
        },
        {
            key = "color",
            label = "Color",
            bitOffset = 24,
            bitWidth = 1,
            choices = {
                { value = 0, label = "Red" },
                { value = 1, label = "Green" },
            },
        },
        {
            key = "bobbing",
            label = "Bobbing",
            bitOffset = 21,
            bitWidth = 1,
            checkboxValue = 1,
        },
        {
            key = "slim_platform",
            label = "Slim platform",
            bitOffset = 23,
            bitWidth = 1,
            checkboxValue = 1,
        },
        {
            key = "stalk_height",
            label = "Stalk height",
            bitOffset = 16,
            bitWidth = 3,
            notes = "Max 7. Add tiles under it.",
        },
        {
            key = "length",
            label = "Length",
            bitOffset = 12,
            bitWidth = 3,
        },
        {
            key = "tilt_angle",
            label = "Tilt angle",
            bitOffset = 8,
            bitWidth = 4,
        },
        {
            key = "speed",
            label = "Speed",
            bitOffset = 0,
            bitWidth = 8,
        },
    },
    init = init,
    render = render,
    grabBounds = grabBounds,
    renderBounds = grabBounds,
}

-- Ported from the NSMB E3 Recreation NSMBe plugin's BackgroundSwapper.

local icon

local function init(ctx)
    icon = ctx.loadImage("images/bg_swapper.png")
end

local function grabBounds(actor)
    return { x = actor.pixelX - 16, y = actor.pixelY - 16, width = 32, height = 32 }
end

-- The swapper acts while the player is within half a screen of it, so the box
-- it draws is the screen it covers.
local function renderBounds(actor)
    return { x = actor.pixelX - 128, y = actor.pixelY - 96, width = 256, height = 192 }
end

local function render(actor, renderer)
    local area = renderBounds(actor)
    renderer:drawText("BG: " .. actor.fields.background_id, { x = area.x + 4, y = area.y + 4 })
    renderer:drawText("FG: " .. actor.fields.foreground_id, { x = area.x + 4, y = area.y + 20 })
    renderer:drawText("TS: " .. actor.fields.tileset_id, { x = area.x + 4, y = area.y + 36 })
    area.color = "#dc143c"
    area.strokeWidth = 2
    renderer:strokeRect(area)
    return renderer:draw(icon, grabBounds(actor))
end

return {
    stageObject = "e3bgswapper.BackgroundSwapper.Default",
    name = "Background Swapper",
    category = "E3 2005 demo",
    notes = "Loads another background, foreground and tileset when the player comes within half a screen of it, so one area can change scenery partway through.",
    fields = {
        {
            key = "background_id",
            label = "Background ID",
            bitOffset = 0,
            bitWidth = 8,
            notes = "255 = No background",
        },
        {
            key = "foreground_id",
            label = "Foreground ID",
            bitOffset = 8,
            bitWidth = 8,
            notes = "255 = No foreground",
        },
        {
            key = "tileset_id",
            label = "Tileset ID",
            bitOffset = 16,
            bitWidth = 8,
            notes = "255 = No tileset",
        },
    },
    init = init,
    render = render,
    grabBounds = grabBounds,
    renderBounds = renderBounds,
}

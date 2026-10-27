-- Ported from the NSMB E3 Recreation NSMBe plugin's ItemBlock.

local images = {}

local function init(ctx)
    images[0] = ctx.loadImage("images/item_block_b.png")
    images[1] = ctx.loadImage("images/item_block_g.png")
    images[2] = ctx.loadImage("images/item_block_y.png")
end

-- The block's top-left. The game centres it on the placement, then moves it
-- down and right by the shifts, which are in pixels.
local function origin(actor)
    local size = actor.fields.size
    return actor.pixelX + actor.fields.right_shift - size // 2,
        actor.pixelY + actor.fields.down_shift - size // 2
end

local function grabBounds(actor)
    local x, y = origin(actor)
    local size = math.max(actor.fields.size, 8)
    return { x = x, y = y, width = size, height = size }
end

local function render(actor, renderer)
    local x, y = origin(actor)
    local size = actor.fields.size
    if size < 8 then
        renderer:strokeRect({ x = x, y = y, width = 8, height = 8, color = "#000" })
    end
    local image = images[actor.fields.color]
    if size == 0 or image == nil then
        return size < 8
    end
    return renderer:draw(image, { x = x, y = y, width = size, height = size })
end

return {
    stageObject = "e3itemblock.ItemBlock.Default",
    name = "SM64 Item Block",
    category = "E3 2005 demo",
    notes = "The rotating block from the E3 2005 demo, hit from below, ground-pounded from above, or struck from the side by anything that hits ? blocks, like a shell.\n\nTrigger event: the event it activates when its behavior is \"Activates event\".",
    fields = {
        {
            key = "size",
            label = "Size",
            bitOffset = 16,
            bitWidth = 8,
            notes = "In pixels. 32 draws the model at its own size.",
        },
        {
            key = "down_shift",
            label = "Down shift",
            bitOffset = 0,
            bitWidth = 4,
            notes = "In pixels.",
        },
        {
            key = "right_shift",
            label = "Right shift",
            bitOffset = 4,
            bitWidth = 4,
            notes = "In pixels.",
        },
        {
            key = "item",
            label = "Item",
            bitOffset = 24,
            bitWidth = 5,
            choices = {
                { value = 0, label = "Mushroom/Fire Flower" },
                { value = 1, label = "Starman" },
                { value = 2, label = "Coin" },
                { value = 3, label = "Mushroom" },
                { value = 5, label = "Mega Mushroom" },
                { value = 7, label = "1-Up" },
                { value = 9, label = "Fire Flower" },
                { value = 10, label = "Vine" },
                { value = 11, label = "Blue Shell" },
                { value = 18, label = "Entrance Vine (grows 7 tiles and then stops)" },
                { value = 25, label = "Mini Mushroom" },
            },
        },
        {
            key = "rotation_direction",
            label = "Rotation direction",
            bitOffset = 14,
            bitWidth = 1,
            choices = {
                { value = 0, label = "Left to right" },
                { value = 1, label = "Right to left" },
            },
        },
        {
            key = "color",
            label = "Color",
            bitOffset = 12,
            bitWidth = 2,
            notes = "A block that was used up once is green when it comes back, whatever its color.",
            choices = {
                { value = 0, label = "Blue" },
                { value = 1, label = "Green" },
                { value = 2, label = "Yellow" },
            },
        },
        {
            key = "behavior",
            label = "Behavior",
            bitOffset = 8,
            bitWidth = 4,
            choices = {
                { value = 0, label = "Activates event" },
                { value = 1, label = "Spawns item" },
                { value = 2, label = "Nothing" },
            },
        },
        {
            key = "destroy_mode",
            label = "Destroy mode",
            bitOffset = 29,
            bitWidth = 2,
            choices = {
                { value = 0, label = "Default" },
                { value = 1, label = "Single use (turns green)" },
                { value = 3, label = "Explodes during animation" },
            },
        },
    },
    init = init,
    render = render,
    grabBounds = grabBounds,
    renderBounds = grabBounds,
}

-- The vanilla Red Coin Ring with the fields RedRing.cpp adds, from the
-- recreation's NSMBe stageobjsettings patch.

local images = {}

local function init(ctx)
    images.RedCoinRing = ctx.loadImage("images/RedCoinRing.png")
end

local function grabBounds(actor)
    local x = actor.pixelX - 7
    if actor.fields.shift_8_pixels_right then
        x = x + 8
    end
    return { x = x, y = actor.pixelY - 26, width = 30, height = 42 }
end

local function render(actor, renderer)
    return renderer:draw(images.RedCoinRing, grabBounds(actor))
end

return {
    objectId = 151,
    name = "Red Coin Ring",
    category = "Event controllers",
    notes = "In the E3 2005 demo a ring is a checkpoint: it remembers which player passed through it, takes their color, and makes its entrance where that player respawns.\n\nTarget event: it can trigger anything, but it's usually used to trigger Red Coins.",
    fields = {
        {
            key = "ring_id",
            label = "Ring ID",
            bitOffset = 0,
            bitWidth = 4,
            notes = "Which of the level's rings this is. Each player can pass through each ID once.",
        },
        {
            key = "entrance_id",
            label = "Entrance ID",
            bitOffset = 8,
            bitWidth = 4,
            notes = "The entrance a player respawns at after passing through the ring. The game reads it as a whole byte, so ID Activation mode must be 0 for this to be the entrance it uses.",
        },
        {
            key = "disable_timer",
            label = "Disable timer",
            bitOffset = 20,
            bitWidth = 4,
            checkboxValue = 1,
        },
        {
            key = "shift_8_pixels_right",
            label = "Shift 8 pixels right",
            bitOffset = 4,
            bitWidth = 4,
            notes = "If set, the Red Ring will respawn if you change areas and come back.",
            checkboxValue = 1,
        },
        {
            key = "switch_tile_states",
            label = "Switch Tile States",
            bitOffset = 16,
            bitWidth = 4,
            notes = "Switches the state of all two-state tiles; invisible blue coins appear, red coin outlines become collectable, red switch blocks become solid.",
            choices = {
                { value = 0, label = "No" },
                { value = 1, label = "Like a P Switch" },
                { value = 2, label = "Like a ! Switch" },
                { value = 4, label = "Red Blocks only" },
                { value = 5, label = "Like a P Switch + Red Blocks" },
                { value = 7, label = "All switchable tiles" },
            },
        },
        {
            key = "id_activation_mode",
            label = "ID Activation mode",
            bitOffset = 12,
            bitWidth = 4,
            notes = "Works only if Target event is not 0 and Disable timer is not set.",
            choices = {
                { value = 0, label = "During timer" },
                { value = 2, label = "After timer" },
            },
        },
    },
    init = init,
    render = render,
    grabBounds = grabBounds,
    renderBounds = grabBounds,
}

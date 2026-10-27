-- Ported from the NSMB E3 Recreation NSMBe plugin's BetaSwitch.

local image

local function init(ctx)
    image = ctx.loadImage("images/beta_switch.png")
end

local function grabBounds(actor)
    if actor.fields.small then
        return { x = actor.pixelX, y = actor.pixelY, width = 16, height = 16 }
    end
    return { x = actor.pixelX, y = actor.pixelY - 16, width = 32, height = 32 }
end

local function render(actor, renderer)
    return renderer:draw(image, grabBounds(actor))
end

return {
    stageObject = "e3betaswitch.BetaSwitch.Default",
    name = "SM64 Boss Switch",
    category = "E3 2005 demo",
    notes = "The switch from the E3 2005 demo. A player stomping it presses it, and it disappears in a puff of smoke.\n\nTrigger event: the event it activates when pressed.",
    fields = {
        {
            key = "small",
            label = "Is small",
            bitOffset = 0,
            bitWidth = 1,
            checkboxValue = 1,
        },
    },
    init = init,
    render = render,
    grabBounds = grabBounds,
    renderBounds = grabBounds,
}

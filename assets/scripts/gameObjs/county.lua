--[[
    county
--]]
doat = 0
function init()
    math.randomseed(os.time())
    math.random()
    math.random()
    math.random()
    doat = math.random(0, 4) -- they should all check at different times
end

count = 0
closeat = 2
function update(county, transform)
    -- Dont do it every frame because jesus thats ineffeciant
    if(count % doat == 0) then
        mouseX = Graphics.mouseX - Graphics:getWindowSize().x / 2
        mouseY = Graphics.mouseY - Graphics:getWindowSize().y / 2
        mouseX = (mouseX + Graphics:getViewPos().x) * Graphics.zoom
        mouseY = (mouseY + Graphics:getViewPos().y) * Graphics.zoom
        thisX = transform.position.x --math.abs(transform.position.x - Graphics:getViewPos().x)
        thisY = transform.position.y --math.abs(transform.position.y - Graphics:getViewPos().y)
        if(math.abs(mouseX - thisX) < closeat and math.abs(mouseY - thisY) < closeat) then
            county.highlightColor(county)
        else
            county.defaultColor(county)
        end
    end
    count = count + 1
end

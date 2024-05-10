function init()
end

function update(gameObj)
    gameObj.transform.position.x = Graphics:getWindowSize().x / 2
    gameObj.transform.position.y = Graphics:getWindowSize().y / 2
end
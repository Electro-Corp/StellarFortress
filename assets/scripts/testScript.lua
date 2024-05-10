-- Test script
function init()
    math.randomseed(os.time())
    math.random()
    math.random()
    math.random()
    math.random()
    print("inited!")
end

count = 0
targetXPos = 0
targetYPos = 0

moving = false

function update(gameObj)
    gameObj.transform.scale.x = 0.03
    gameObj.transform.scale.y = 0.03
    
    if math.abs(targetXPos - gameObj.transform.position.x) < 10 and math.abs(targetYPos -gameObj.transform.position.y) < 10 then
        count = 0
        moving = false
        targetXPos = math.random(-700, 700)
        targetYPos = math.random(-700, 700)
    else
        gameObj.transform.position.x = gameObj.transform.position.x + ((targetXPos - gameObj.transform.position.x) / 1000)
        gameObj.transform.position.y = gameObj.transform.position.y + ((targetYPos - gameObj.transform.position.y) / 1000)
	    gameObj.transform.angle = 90 + (math.atan2(targetYPos - gameObj.transform.position.y, targetXPos - gameObj.transform.position.x) * (180 / 3.14))
    end


    count = count + 0.01

end

function init(object)
  object.transform.scale.x = 350
  object.transform.scale.y = 45
  object.transform.position.x = (Graphics:getWindowSize().x / 2) - (object.transform.scale.x / 2)
  object.transform.position.y = 500
end

function lerp(a, b, t)
  return a + (b - a) * t
end


count = 0
function update(object)
  
end

function onKeyPressed(object, key)
  print(key)
  if key == 's' then
    Game:setTickNum(1)
  end
end
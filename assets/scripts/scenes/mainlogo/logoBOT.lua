targetY = Graphics:getWindowSize().y / 11

function init()

end

function lerp(a, b, t)
  return a + (b - a) * t
end

count = 0
function update(object)
  object.transform.scale.x = 510
  object.transform.scale.y = 170
  if(math.abs((targetY + (object.transform.scale.y / 1.5)) - object.transform.position.y) > 5) then
    object.transform.position.x =  (Graphics:getWindowSize().x / 2) - (object.transform.scale.x / 2) --lerp(object.transform.position.x, (Graphics:getWindowSize().x / 2) - (object.transform.scale.x / 2), count)
    object.transform.position.y =  lerp(object.transform.position.y, targetY + (object.transform.scale.y / 1.5), count) --Graphics:getWindowSize().y / 3
    count = count + 0.001
  else
    object.transform.position.x = (((Graphics:getWindowSize().x / 2) - (object.transform.scale.x / 2)) + (math.sin(count) * 10))-- + (Graphics.mouseX / 100)
    --object.transform.position.y = (targetY + (object.transform.scale.y / 1.5)) + (Graphics.mouseY / 100)
    count = count + 0.01
    --object.transform.position.y = targetY + (object.transform.scale.y / 1.5 + math.cos(count)
  end
  if count > 100000 then
    count = 0
  end
end

function init()

end

function lerp(a, b, t)
  return a + (b - a) * t
end


count = 0
function update(object)
  object.transform.scale.x = 350
  object.transform.scale.y = 45
  object.transform.position.x = (Graphics:getWindowSize().x / 2) - (object.transform.scale.x / 2)
  object.transform.position.y = 500
  count = count + 0.001
  if count > 1000 then
    count = 0
  end
end

function onKeyPressed(object, key)
  object.transform.angle = 360 * math.sin(count)
end
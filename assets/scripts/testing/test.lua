function init()

end
count = 0
function update(object)
  object.transform.scale.x = math.abs(800 * math.sin(count)) --Graphics.mouseX
  object.transform.scale.y = math.abs(600 * math.cos(count)) --Graphics.mouseY
  object.transform.angle = 360 * math.sin(count)
  count = count + 0.01
end
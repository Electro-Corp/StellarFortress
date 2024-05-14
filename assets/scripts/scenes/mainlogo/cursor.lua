
function init()

end


function update(object)
  object.transform.scale.x = 68
  object.transform.scale.y = 75
  object.transform.position.x =  Graphics.mouseX - (object.transform.scale.x / 2)
  object.transform.position.y =  Graphics.mouseY - (object.transform.scale.y / 2)
end
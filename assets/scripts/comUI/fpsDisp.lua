function init(objet)
end

function update(textObj)
  local deltaTime = Game:getDelta() / 1000
  local fps = 1 / deltaTime 
  textObj.text = "FPS: " .. string.format("%.1f", fps) .. " [target 30]"
end

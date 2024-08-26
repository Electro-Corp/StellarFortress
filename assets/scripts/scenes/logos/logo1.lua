var = 0

fade = false

function init(object)
  object.getSprite(object).setAlpha(object.getSprite(object), var)
end


function update(object)
  if fade == false then
    if var < 255 then
      object.getSprite(object).setAlpha(object.getSprite(object), var)
      var = var + 5
    else
      var = var + 5
      if var > 509 then
        var = 255
        fade = true
      end
      -- Game:setTickNum(1)
    end
  end
  if fade == true and var > 1 then
    var = var - 5
    object.getSprite(object).setAlpha(object.getSprite(object), var)
  end
  
end
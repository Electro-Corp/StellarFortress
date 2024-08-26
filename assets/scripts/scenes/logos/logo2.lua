var = 0

time = false

fade = false

function init(object)
  object.getSprite(object).setAlpha(object.getSprite(object), var)
end


function update(object)
  if fade == false then
    if var < 255 and time == true then
      object.getSprite(object).setAlpha(object.getSprite(object), var)
      var = var + 5
    elseif var < 255 and time == false then
      var = var + 5
    elseif var > 254 and time == false then
      var = 0
      time = true
    end
    if var > 254 and time == true then
        fade = true
    end
  end

  if fade == true and var > 1 then
    var = var - 5
    object.getSprite(object).setAlpha(object.getSprite(object), var)
  elseif fade == true and var < 2 then
     Game:setTickNum(1)
  end
end

function onKeyPressed(obj, key)
  -- Skip intro
  Game:setTickNum(1)
end
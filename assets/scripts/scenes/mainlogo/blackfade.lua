var = 255

function init(object)

end

function update(object)
  if var > 1 then
    var = var - 5
    object.getSprite(object).setAlpha(object.getSprite(object), var)
  end
end
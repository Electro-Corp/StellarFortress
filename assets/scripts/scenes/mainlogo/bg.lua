-- This file exists because weezer

weezer = {'w', 'e', 'e', 'z', 'e', 'r'}
buffer = {}
count = 1

sad = true

function init()
  
end

function update(obj)
  if not sad then
    obj.setTex(obj, "../assets/textures/menu/weezerblue.jpg")
    sad = true
  end
end

function onKeyPressed(object, key)
  buffer[count] = key
  if count == 6 then
    sad = false
    for i = 1, 6 do  
      if weezer[i] ~= buffer[i] then
        sad = true
        break
      end
    end
    count = 1
    buffer = {}  
  else
    count = count + 1
  end
end

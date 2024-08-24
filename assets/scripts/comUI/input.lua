-- File for UI input box

text = ""

function init(obj)
  obj.transform.position.y = Graphics:getWindowSize().y / 11
  obj.transform.position.x = Graphics:getWindowSize().x / 3
  obj.transform.scale.x = 500
  obj.transform.scale.y = 100
  
  obj.question.transform.position.x = obj.transform.position.x + 10
  obj.question.transform.position.y = obj.transform.position.y + 20

  obj.question.transform.scale.x = 50
  obj.question.transform.scale.y = 20

  obj.input.transform.position.x = obj.transform.position.x + 20
  obj.input.transform.position.y = obj.transform.position.y + 30
  obj.input.transform.scale.y = 50
  obj.input.transform.scale.x = 20
end

function update(obj)
  obj.input.text = text
  obj.input.transform.scale.x = string.len(text) * 20
end

function onKeyPressed(obj, key)
  text = text .. key
end
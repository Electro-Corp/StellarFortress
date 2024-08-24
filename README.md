# Stellar Fortress
Rewrite of Stellar Fortress in the Mosiac Engine (from https://github.com/Electro-Corp/Disunited-States-of-America).
The Mosiac Engine has been modified to support SDL2 Rendering for Replit. 
## Pre-Reqs
* a modern-ish c++ compiler that supports "#pramga"
* SDL and SFML
* Lua 5.1
* LuaBridge
* jsoncpp
* cmake

## Build
To build, create a empty build directory:
```
mkdir build
```
Then, go into it and run cmake:
```
cd build
camke ../
```
Then, compile and run!
```
make
./STELLAR
```

## Lua API
Stellar Fortress features a Lua API for easy scripting.
### Basics
Each script needs two functions:

```lua
function init()
  -- init code goes here
end

function update(object)
  -- update is called once per frame
end
```
The argument in update is a refrence to the GameObject it is attached to. <br>
What you can do with it depends on what GameObject it is. For example:
```lua
-- We a Engine::GameObject
function update(object)
  -- When calling a function for an object, the first argument must 
  -- always be the object itself.
  object.setTex(object, "../assets/images/swagmessiah.jpg")
end

-- We an UI::Text
function update(textObj)
  textObj.text = "hiii!"
end
```

### On Event functions
Stellar Fortress currently has the follwing functions that can optionally be added to be called on a specfic event: <br>
* onKeyPressed

### `onKeyPressed`
When onKeyPressed is added to a Lua file, Stellar Fortress will automatically call the function when a key is pressed. <br>

Ex:
```lua
-- onKeyPressed requires two arguments, the object itself, and the key that was pressed
function onKeyPressed(object, key)
  if key == "w" then
    object.transform.x = 50
  end
end

## ToDO:
* music/audio manager

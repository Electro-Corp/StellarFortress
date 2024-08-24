#include <gameObjects/ui/inputpanel.h>

UI::Panel::Panel(std::string caption, int rgb){
  question = new UI::Text(caption, 255);
  input = new UI::Text("", 255);
  this->rgb = RGB(rgb);
}

void UI::Panel::initScript(){
    if(this->script){
        this->script->initfunc(this);
    };
}

void UI::Panel::update(){
    if(this->script){
      this->script->update(this);
    }
    updateTransform();
    #if USE_SDL
    texture_rect.x = this->transform.position.x; 
    texture_rect.y = this->transform.position.y;
    texture_rect.w = this->transform.scale.x;
    texture_rect.h = this->transform.scale.y;
    #endif
}


#if USE_SDL
void UI::Panel::draw(SDL_Renderer* window){
    SDL_SetRenderDrawColor(window, rgb.r, rgb.g, rgb.b, 255);
    SDL_RenderFillRect(window, &texture_rect);
    SDL_SetRenderDrawColor(window, 255, 0, 0, 255);
    SDL_RenderDrawRect(window, &texture_rect);

    question->update();
    question->draw(window);
    input->update();
    input->draw(window);
}
#endif

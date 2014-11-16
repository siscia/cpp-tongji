#include <iostream>
#include <allegro5/allegro.h>

class Bullet {  
public:
  float x, y;
  float velocity[2];
  float acceleration[2];
  Bullet(float x_in, float y_in){
    x = x_in; y = y_in;
  }
  Bullet(float x_in, float y_in, float vel[2]){
    x = x_in; y = y_in;
    velocity[0] = vel[0]; velocity[1] = vel[1];
  }
  Bullet(float x_in, float y_in, float vel[2], float acc[2]){
    x = x_in; y = y_in;
    velocity[0] = vel[0]; velocity[1] = vel[1];
    acceleration[0] = acc[0]; acceleration[1] = acc[1];
  }
  void accelerate () {
    velocity[0] += acceleration[0];
    velocity[1] += acceleration[1];
  }
  void move(){
    x += velocity[0];
    y += velocity[1];
  }
  void tick(){
    this->accelerate();
    this->move();
  }
  void display(){
    std::cout << "Position:     [ " << this->x << ", " << this->y << " ]\n";
    std::cout << "Velocity:     [ " << this->velocity[0] << ", " << this->velocity[1] << " ]\n";
    std::cout << "Acceleration: [ " << this->acceleration[0] << ", " << this->acceleration[1] << " ]\n";
  }
};

class VisualBullet : public Bullet {
public:
  ALLEGRO_BITMAP *bmp_p = NULL;
  VisualBullet(float x_in, float y_in) : Bullet(x_in, y_in) {
    ALLEGRO_DISPLAY *old = al_get_current_display();
    bmp_p = al_create_bitmap(10, 10);
    al_set_target_bitmap(bmp_p);
    al_clear_to_color(al_map_rgb(255, 0, 255)); //viola
    al_set_target_backbuffer(old);
  }
  VisualBullet(float x_in, float y_in, float dir[2]) : Bullet(x_in, y_in, dir) {
    ALLEGRO_DISPLAY *old = al_get_current_display();
    bmp_p = al_create_bitmap(10, 10);
    al_set_target_bitmap(bmp_p);
    al_clear_to_color(al_map_rgb(255, 0, 255)); //viola
    al_set_target_backbuffer(old);
  }
  VisualBullet(float x_in, float y_in, float dir[2], float acc[2]) : Bullet(x_in, y_in, dir, acc) {
    ALLEGRO_DISPLAY *old = al_get_current_display();
    bmp_p = al_create_bitmap(10, 10);
    al_set_target_bitmap(bmp_p);
    al_clear_to_color(al_map_rgb(255, 0, 255)); //viola
    al_set_target_backbuffer(old);
  }
  void draw(){
    al_draw_bitmap(this->bmp_p, this->x, this->y, 0);
  }
};

ALLEGRO_DISPLAY *display = NULL;

int main(){
  al_init();

  float velocity[2] = {2.0, 3.0};
  float acceleration[2] = {5.0, 10.8};

  VisualBullet b1 (10, 20, velocity, acceleration);
 

  display = al_create_display(640, 480);
  
  al_set_target_bitmap(al_get_backbuffer(display));

  for (int i=0; i<20; i++){
    b1.draw();
    b1.tick();
    al_flip_display();
    al_rest(0.1);
  }
  al_rest(1.0);
  al_destroy_display(display);
  return 1;
}

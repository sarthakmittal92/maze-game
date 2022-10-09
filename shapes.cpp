#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <iostream>
using namespace std;

int a[] = {5,6,7,8,9,11,17,19,20,21,22,23,25,29,33,-1};
int goright[] = {0,1,2,3,15,14,13,12,30,31,26,27,34,-1};
int goleft[] = {1,2,3,4,16,15,14,13,31,32,27,28,35,-1};
int goup[] = {10,16,18,24,30,32,34,-1};
int godown[] = {4,10,12,18,24,26,28,-1};
bool block[36];

bool check (int i, int a[]) {
  for (int j = 0; a[j] != -1; j++) {
    if (i == a[j]) {
      return true;
    }
  }
  return false;
}

class MyRectangle : public Fl_Widget {
  int x, y, w, h, color;
  public:
    MyRectangle (int x, int y, int w, int h, int color) : Fl_Widget (x,y,w,h) {
      this -> x = x;
      this -> y = y;
      this -> w = w;
      this -> h = h;
      this -> color = color;
    }
    void draw () {
      fl_draw_box (FL_FLAT_BOX,x,y,w,h,color);
    }
};

class Shape : public Fl_Widget {
  protected:
    int x, y, w, h;
  public:
    Shape (int x, int y, int w, int h) : Fl_Widget (x,y,w,h) {
      this -> x = x;
      this -> y = y;
      this -> w = w;
      this -> h = h;
    }    
    virtual void wipe () = 0;
    virtual void refresh () = 0;
    virtual void remake (int dx, int dy) {
      x += dx;
      y += dy;
      resize(x,y,w,h);
    }
    virtual int handle (int e) {
      int i = (y - 100)*6/100 + (x - 100)/100;
      if (Fl::event_key() == 'd' && e == FL_KEYDOWN && check(i,goright)) {
        wipe ();
        remake (100,0);
        refresh ();
      }
      else if (Fl::event_key() == 'a' && e == FL_KEYDOWN && check(i,goleft)) {
        wipe ();
        remake (-100,0);
        refresh ();
      }
      else if (Fl::event_key() == 'w' && e == FL_KEYDOWN && check(i,goup)) {
        wipe ();
        remake (0,-100);
        refresh ();
      }
      else if (Fl::event_key() == 's' && e == FL_KEYDOWN && check(i,godown)) {
        wipe ();
        remake (0,100);
        refresh ();
      }
      return 1;
    }
};

class MyCircle : public Shape {
  public:
    MyCircle (int x, int y, int w) : Shape (x,y,w,w) {}
    void draw () {
      fl_color (fl_rgb_color(130));
      fl_pie (x,y,w,h,0,360);
    }
    virtual void wipe () {
      fl_color (FL_WHITE);
      fl_pie (x,y,w,h,0,360);
    }
    virtual void refresh () {
      fl_color (fl_rgb_color(130));
      fl_pie (x,y,w,h,0,360);
    }
};

int main () {
  Fl_Window* window = new Fl_Window(800,800,"200050129");
    
    for (int i = 0; i < 36; i++) {
      if (check(i,a)) {
        block[i] = true;
      }
      else {
        block[i] = false;
      }
    }
    
    for (int i = 0; i < 36; i++) {
      if (block[i]) {
        new MyRectangle (100 + 100*(i % 6),100 + 100*(i/6),100,100,FL_BLACK);
      }
      else {
        new MyRectangle (100 + 100*(i % 6),100 + 100*(i/6),100,100,FL_WHITE);
      }
    }
    window -> color(FL_BLUE);
    new MyCircle (116,116,70);

  window -> end();

  window -> show();
  return (Fl::run());
}
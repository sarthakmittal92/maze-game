#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <iostream>
using namespace std;

const int l = 47;
const int n = 15;

// int a[] = {5,6,7,8,9,11,17,19,20,21,22,23,25,29,33,-1};

int a[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,19,25,29,30,31,32,34,36,38,39,40,42,44,45,49,51,57,59,60,62,63,64,66,67,68,69,70,71,72,74,75,77,81,85,90,92,94,95,96,98,100,102,103,104,105,109,113,115,119,120,122,123,124,125,126,128,130,131,132,134,135,141,143,145,149,150,151,152,153,154,156,158,159,160,162,163,164,165,171,175,179,180,182,183,184,185,186,187,188,190,191,192,193,194,195,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,-1};

int goright[n*n], goleft[n*n], goup[n*n], godown[n*n];
bool block[n*n];

bool check (int i, int a[]) {
  for (int j = 0; a[j] != -1 ; j++) {
    if (i == a[j]) {
      return true;
    }
  }
  return false;
}

void moveright () {
  int j = 0;
  for (int i = 0; i < n*n; i++) {
    if ((i + 1) % n && !block[i] && !block[i + 1]) {
      goright[j] = i;
      j++;
    }
  }
  goright[j] = -1;
} 

void moveleft () {
  int j = 0;
  for (int i = 0; i < n*n; i++) {
    if (i % n && !block[i] && !block[i - 1]) {
      goleft[j] = i;
      j++;
    }
  }
  goleft[j] = -1;
} 

void moveup () {
  int j = 0;
  for (int i = 0; i < n*n; i++) {
    if (i >= n && !block[i] && !block[i - n]) {
      goup[j] = i;
      j++;
    }
  }
  goup[j] = -1;
} 

void movedown () {
  int j = 0;
  for (int i = 0; i < n*n; i++) {
    if (i < n*n - n && !block[i] && !block[i + n]) {
      godown[j] = i;
      j++;
    }
  }
  godown[j] = -1;
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
      int i = (y - l)*n/l + (x - l)/l;
      if (Fl::event_key() == 'd' && e == FL_KEYDOWN && check(i,goright)) {
        wipe ();
        remake (l,0);
        refresh ();
      }
      else if (Fl::event_key() == 'a' && e == FL_KEYDOWN && check(i,goleft)) {
        wipe ();
        remake (-l,0);
        refresh ();
      }
      else if (Fl::event_key() == 'w' && e == FL_KEYDOWN && check(i,goup)) {
        wipe ();
        remake (0,-l);
        refresh ();
      }
      else if (Fl::event_key() == 's' && e == FL_KEYDOWN && check(i,godown)) {
        wipe ();
        remake (0,l);
        refresh ();
      }
      return 1;
    }
};

class MyCircle : public Shape {
  public:
    MyCircle (int x, int y, int w) : Shape (x,y,w,w) {}
    void draw () {
      fl_color (fl_rgb_color(FL_RED));
      fl_pie (x,y,w,h,0,360);
    }
    virtual void wipe () {
      fl_color (FL_WHITE);
      fl_pie (x,y,w,h,0,360);
    }
    virtual void refresh () {
      fl_color (fl_rgb_color(FL_RED));
      fl_pie (x,y,w,h,0,360);
    }
};

int main () {
  Fl_Window* window = new Fl_Window(800,800,"200050129");

    for (int i = 0; i < n*n; i++) {
      if (check(i,a)) {
        block[i] = true;
      }
      else {
        block[i] = false;
      }
    }

    moveright();
    moveleft();
    moveup();
    movedown();

    for (int i = 0; i < n*n; i++) {
      if (block[i]) {
        new MyRectangle (l + l*(i % n),l + l*(i/n),l,l,FL_BLACK);
      }
      else {
        new MyRectangle (l + l*(i % n),l + l*(i/n),l,l,FL_WHITE);
      }
    }

    window -> color(FL_BLUE);
    new MyCircle (l,2*l,l);
    new Fl_Button(0,2*l,l,l,"Start");
    new Fl_Button(16*l,6*l,l,l,"End");

  window -> end();

  window -> show();
  return (Fl::run());
}
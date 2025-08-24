PImage Im;
color c;
int x, y;


void setup()
{
  size(500,500);
  Im = loadImage("lena.jpg");
  Im.resize(200,200);
  
  x = width/2 - Im.width / 2;
  y = height/2 - Im.height / 2;
  
  c = color(0);
}


void draw()
{
  background(c);
  c = Im.get(mouseX - x, mouseY - y);
   image(Im,x,y);
  
 
}

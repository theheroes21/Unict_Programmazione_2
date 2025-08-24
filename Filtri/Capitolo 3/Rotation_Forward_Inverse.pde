PImage Im, Ir, Iri;
int ang = 0;

void setup()
{
  size(1025,512);
  Im=loadImage("lena.png");
  
  Ir=rotateF(Im,radians(ang));
  Iri=rotateI(Im,radians(ang));

  image(Ir,0,0);
  image(Iri,512,0);
}

void draw(){}


PImage rotateF(PImage I, float theta)
{
  PImage R = I.copy();
  R.loadPixels();
  
  for(int i=0; i<R.pixels.length; i++)
  {
    R.pixels[i] = color(0);
  }
  
  float u, v;
  float x1, y1;
  
  for(int x=0; x<I.width; x++)
  {
    for(int y=0; y<I.height; y++)
    {
      x1 = x - I.width/2;
      y1 = y - I.height/2;
      
      u = x1 * cos(theta) - y1 * sin(theta);
      v = x1 * sin(theta) + y1 * cos(theta);
      
      u = u+I.width/2;
      v = v+I.height/2;
      
      R.set(round(u),round(v),I.get(x,y));
      
    }
  }
  
  R.updatePixels();
  return R;
}



PImage rotateI(PImage I, float theta)
{
  PImage R = I.copy();
  R.loadPixels();
  
  for(int i=0; i<R.pixels.length; i++)
  {
    R.pixels[i] = color(0);
  }
  
  float u, v;
  float x1, y1;
  
  for(int x=0; x<I.width; x++)
  {
    for(int y=0; y<I.height; y++)
    {
      x1 = x - I.width/2;
      y1 = y - I.height/2;
      
      u = x1 * cos(theta) + y1 * sin(theta);
      v = -x1 * sin(theta) + y1 * cos(theta);
      
      u = u + I.width/2;
      v = v + I.height/2;
      
      R.set(x,y,I.get(round(u), round(v)));
    }
  }
  
   R.updatePixels();
   
   return R;
}

void keyPressed()
{
  if(key=='+')
  {
    ang+=5;
  }
  
  if(key=='-')
  {
    ang-=5;
  }
  
  ang=ang%360;
  println(ang);
  Ir=rotateF(Im,radians(ang));
  image(Ir,0,0);
  Iri=rotateI(Im,radians(ang));
  image(Iri,512,0);
}

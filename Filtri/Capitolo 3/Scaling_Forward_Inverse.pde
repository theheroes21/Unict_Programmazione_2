PImage Im, Ir, Iri;
float scale = 1;

void setup()
{
  size(1024,512);
  Im=loadImage("lena.png");
  
  Ir=scaleF(Im,scale,scale);
  Iri=scaleI(Im,scale,scale);
  image(Ir,0,0);
  image(Iri,512,0);
}


void draw(){}


PImage scaleF(PImage I, float cx, float cy)
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
      x1 = x-I.width/2;
      y1 = y-I.height/2;
      
      u = x1 * cx;
      v = y1 * cy;
      
      u = u + I.width/2;
      v = v + I.height/2;
      
      R.set(round(u),round(v), I.get(x,y));
    }
  }
  
  R.updatePixels();
  return R;
}

PImage scaleI(PImage I, float cx, float cy)
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
      
      u = x1 * 1/cx;
      v = y1 * 1/cy;
      
      u = u + I.width/2;
      v = v + I.height/2;
      
      R.set(x, y, I.get(round(u),round(v)));
    }
  }
  
  R.updatePixels();
  
  return R;
}

void keyPressed()
{
  if(key == '+')
    scale = scale + .1;
    
  if(key == '-')
    scale = scale - .1;
    
  println(scale);
  
  Ir = scaleF(Im,scale,scale);
  Iri = scaleI(Im,scale,scale);
  
  image(Ir,0,0);
  image(Iri,512,0);
  
}

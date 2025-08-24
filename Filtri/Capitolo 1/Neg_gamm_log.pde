PImage Im, In, Ig, Ilog;

void setup()
{
  size(512,512);
  Im = loadImage("lena.png");
  Im.resize(256,256);
  image(Im,0,0);
  
  In = negativo(Im);
  image(In,256,0);
  
  Ig = gamma(Im,5.2);
  image(Ig,0,256);
  
  Ilog = logaritmo(Im);
  image(Ilog,256,256);
  
  
  
  
}

void draw(){}


PImage negativo(PImage I)
{
  PImage R = I.copy();
  
  float r,g,b;
  
  R.loadPixels(); // è ridondante per PImage
  
  for(int i=0; i<R.pixels.length; i++)
  {
    r = 255 - red(R.pixels[i]);
    g = 255 - green(R.pixels[i]);
    b = 255 - blue(R.pixels[i]);
    
    R.pixels[i] = color(r,g,b);
  }
  
  R.updatePixels(); //  è ridondante per PImage
  
  return R;
}


PImage gamma(PImage I, float gm)
{
  PImage R = I.copy();
  float r,g,b;
  float C = 1/pow(255,gm-1);
  
  for(int i=0; i<R.pixels.length; i++)
  {
    r = C * pow(red(R.pixels[i]),gm);
    g = C * pow(green(R.pixels[i]),gm);
    b = C * pow(blue(R.pixels[i]),gm);
    
    R.pixels[i] = color(r,g,b);
  }
  
  return R;
}


PImage logaritmo(PImage I)
{
  PImage R = I.copy();
  
  float r,g,b;
  float C = 256/log(256);
  
  for(int i=0; i<R.pixels.length; i++)
  {
    r = C * log(1+red(R.pixels[i]));
    g = C * log(1+green(R.pixels[i]));
    b = C * log(1+blue(R.pixels[i]));
    
    R.pixels[i] = color(r,g,b);
  }
  
  return R;
}
























/*
.loadPixels() e .updatePixels() sono ridondanti per PImage
 
Quando invece sono necessari?
Sono obbligatori solo in questi casi:

- Modifica dei pixel della finestra principale
- Forzare un aggiornamento immediato
*/

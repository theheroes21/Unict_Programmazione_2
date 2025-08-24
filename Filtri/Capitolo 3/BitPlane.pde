PImage Im, Ib;
int K;

void setup()
{
  size(1024,512);
  Im = loadImage("lena.png");
  Im.filter(GRAY);
  image(Im,0,0);
  K = 0;
  
  Ib = bitplane(Im,K);
  image(Ib,512,0);
  
}


void draw(){}

PImage bitplane(PImage I, int nb)
{
  PImage R = I.copy();
  R.loadPixels();
  
  int x , r;
  
  for(int i=0; i<R.pixels.length; i++)
  {
    x = int(brightness(R.pixels[i]));
    r = (x>>nb)&1;
    R.pixels[i] = color(r*255);
  }
  
  R.updatePixels();
  
  return R;
}

void keyPressed()
{
  if((key == '+') && (K < 7))
  {
    K++;
    Ib = bitplane(Im,K);
    image(Ib,512,0);
    println(K);
  }
  
  if((key == '-') && (K > 0))
  {
    K--;
    Ib = bitplane(Im,K);
    image(Ib,512,0);
    println(K);
  }
}

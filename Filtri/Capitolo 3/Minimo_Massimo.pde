PImage Im, Imin, Imax;
int N;

void setup()
{
  size(1536,512);
  Im = loadImage("lena.png");
  Im.filter(GRAY);
  image(Im,0,0);
  
  Imin = minimo(Im,11);
  image(Imin,512,0);
  
  Imax = massimo(Im,11);
  image(Imax,1024,0);
  
  
}

void draw(){}

PImage minimo(PImage I, int N)
{
    PImage R = I.copy();
    
    PImage tmp;
    int off = N/2;
    
    
    float [] tmpF = new float [N*N];
    
    for(int x=0; x<I.width; x++)
    {
      for(int y=0; y<I.height; y++)
      {
        int xs = x - off;
        int ys = y - off;
        
        
        xs = constrain(xs, 0, I.width - N);
        ys = constrain(ys, 0, I.height - N);
        
        tmp = I.get(xs, ys, N, N);
        tmp.loadPixels();
        
        for(int i=0; i<tmp.pixels.length; i++)
        {
          tmpF[i] = brightness(tmp.pixels[i]);
        }
        
        R.set(x,y,color(min(tmpF)));
      }
    }
    
    return R;
}

PImage massimo(PImage I, int N)
{
    PImage R = I.copy();
    
    PImage tmp;
    int off = N/2;
    
    float [] tmpF = new float [N*N];
    
    for(int x=0; x<I.width; x++)
    {
      for(int y=0; y<I.height; y++)
      {
        
        int xs = x - off;
        int ys = y - off;
        
        xs = constrain(xs, 0, I.width - N);
        ys = constrain(ys, 0, I.height - N);
        
        tmp = I.get(xs, ys, N, N);
        tmp.loadPixels();
        
        for(int i=0; i<tmp.pixels.length; i++)
        {
          tmpF[i] = brightness(tmp.pixels[i]);
        }
        
        R.set(x,y,color(max(tmpF)));
      }
    }
    
    return R;
}

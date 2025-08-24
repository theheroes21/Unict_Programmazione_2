PImage Im, Is, Ie;


void setup()
{
  size(1500,812);
  background(0);
  
  Im = loadImage("lena.png");
  Im.filter(GRAY);
  
  Is = stretching(Im);
  
  Ie = equalizza(Im);
  
  
  image(Im,0,0);
  image(Is,500,0);
  image(Ie,1000,0);
  
  float [] H1,H2,H3;
  H1 = istogramma(Im);
  H2 = istogramma(Is);
  H3 = istogramma(Ie);
  
  rectMode(CORNERS);
  noStroke();
  fill(255,255,0);
  
  for(int i=0; i<256; i++)
  {
    rect(i*2, height-(H1[i] * 256 * 100), i*2+2, height);
    rect(Im.width +i*2, height-(H2[i] * 256 * 100), Im.width +i*2+2, height);
    rect(Im.width*2 +i*2, height-(H3[i] * 256 * 100), Im.width*2 +i*2+2,height);
  }
}

void draw(){}

float[] istogramma(PImage I)
{
  float[] H = new float[256];
  
  for(int i=0; i<256; i++)
  {
    H[i] = 0;    // Imposta ogni elemento a 0
  }
  
  I.loadPixels();
  
  for(int i=0; i<I.pixels.length; i++)
  {
    H[int(brightness(I.pixels[i]))]++;  //Incrementa il conteggio
  }
  
  for(int i=0; i<256; i++)
  {
    H[i] = H[i]/I.pixels.length;
  }
  
  return H;
}

PImage stretching(PImage I)
{
  PImage R = I.copy();
  
  float min, max;
  R.loadPixels();
  
  max = brightness(R.pixels[0]);
  min = brightness(R.pixels[0]);
  
  for(int i=0; i<R.pixels.length; i++)
  {
    if(brightness(R.pixels[i]) < min)
      min = brightness(R.pixels[i]);
      
      if(brightness(R.pixels[i]) > max)
      max = brightness(R.pixels[i]);
  }
   for(int i=0; i<R.pixels.length; i++)
   {
     R.pixels[i] = color (255*(brightness(R.pixels[i])- min)/(max-min));
   }
   
   R.updatePixels();
   
   return R;
}


PImage equalizza(PImage I)
{
  PImage R = I.copy();
  
  float[] H = istogramma(I);
  
  for(int i=1; i<256; i++)  // i = 1 e non 0 altrimenti H[-1] ERROR 
  {
    H[i] = H[i-1] + H[i];  // Calcola il CDF
  }
  
  R.loadPixels();
  
  for(int i=0; i<R.pixels.length; i++)
  {
    R.pixels[i] = color(255 * H[int(brightness(R.pixels[i]))]);
  }
  
  R.updatePixels();
  
  return R;
}

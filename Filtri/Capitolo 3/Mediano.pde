PImage Im, Imed;
int N = 5;

void setup()
{
  size(1024,512);
  Im = loadImage("lena.png");
  Im.filter(GRAY);
  
  Imed = mediano(Im,N);
  
  image(Im,0,0);
  image(Imed,512,0);
}

void draw(){}

PImage mediano(PImage I, int N)
{
  PImage R = I.copy();
  PImage tmp;
  int off = N/2;
  float med;
  
  
  float [] tmpF = new float [N*N];
  
   for(int x=0; x<I.width; x++){
     for(int y=0; y<I.height; y++){
       
       int xs = x - off;
       int ys = y - off;
       
       xs = constrain(xs,0,I.width-N);
       ys = constrain(ys,0,I.height-N);
       
       tmp=I.get(xs,ys,N,N);
       
       tmp.loadPixels();
       
       for(int i=0; i<tmp.pixels.length; i++)
       {
         tmpF[i] = brightness(tmp.pixels[i]);
       }
       
       tmpF = sort(tmpF);
       
       if((N*N)%2 == 1)
         med = tmpF[(N*N)/2];
       else
         med = ( tmpF[(N*N)/ 2] + tmpF[(N*N)/2-1] ) / 2;
         
       R.set(x,y,color(med));
     } 
   }
   
   return R;
}

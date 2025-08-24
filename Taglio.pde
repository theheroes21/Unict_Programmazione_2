PImage Im, Ivert, Ioriz;

void setup(){
  size(768,256);
    
  Im = loadImage("Black_Goku.jpg");
  Im.resize(256,256);
  
  image(Im,0,0);
  
  Ivert  = taglio_vert(Im);
  image(Ivert,256,0);
 
  Ioriz = taglio_orizz(Im);
  image(Ioriz,512,0);
}

void draw(){}

PImage taglio_vert(PImage I)
{
  
  PImage sup, inf;
  PImage y = createImage(3,5,RGB);
  
  PImage R = I.copy();
  sup = I.get(0, 0, I.width, I.height/2);
  inf = I.get(0, I.height/2 ,I.width ,I.height/2);
  R.set(0,0,inf);
  R.set(0,I.height/2,sup);
  for(int i =0; i<y.pixels.length; i++)
    y.pixels[i]=color(255,255,0);
  
  for(int i= R.height/2; i<R.height; i++)
    R.set(i,i,y);
  
  return R;
}

PImage taglio_orizz(PImage I)
{
  PImage sx,dx;
  
  PImage R = I.copy();
  sx = I.get(0,0,I.width/2,I.height);
  dx = I.get(I.width/2,0,I.width/2,I.height);
  R.set(0,0,dx);
  R.set(I.width/2,0,sx);
  
  return R;

}

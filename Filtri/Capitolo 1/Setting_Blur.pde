PImage Im;
String url = "https://staticctf.ubisoft.com/J3yJr34U2pZ2Ieem48Dwy9uqj5PNUQTn/449BBgnc3Q1ha2IN9rh3bR/eb9a6d17615e1480d12e9aab24804c67/ac-ezio-hero-mobile.jpg";
int g = 0;

void settings()
{
  Im = loadImage(url);
  Im.resize(int(Im.width/4.5), int(Im.height/4.5));
  size(Im.width,Im.height);
}

void draw()
{
  image(Im,0,0);
}

void keyPressed()
{
  if(key == '+')
  {
    g++;
    Im.filter(BLUR,g);
  }
    
  if(key == 'r')
  {
    Im = loadImage(url);
    Im.resize(int(Im.width/4.5), int(Im.height/4.5));
    g = 0;
  }
  

  
    
}

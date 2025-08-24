PImage Im, subIm;
String url = "https://static1.xdaimages.com/wordpress/wp-content/uploads/2025/04/wallpaper-dragon-ball.jpg?q=70&fit=contain&w=1200&h=628&dpr=1";


void setup()
{
  size(432,250);
  Im = loadImage(url);
  Im.resize(int(Im.width/2.5),int(Im.height/2.5));
  subIm = Im.get(170,110,120,160);
  Im.filter(GRAY);
  
}

void draw()
{
  image(Im,0,0);
  image(subIm,165,110);
  
  subIm.save("Goku Ultra Istinto.jpg");
  
  saveFrame("Composizione Sparking Zero.jpg");
}

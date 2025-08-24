PImage Im, In3, In5, Il, Is, IsX;

float n3=1/9.0;
float [][] nbox3 = {{n3,n3,n3},
                    {n3,n3,n3},
                    {n3,n3,n3}};

float n5=1.0/25;
float[][] nbox5={{n5,n5,n5,n5,n5},
                {n5,n5,n5,n5,n5},
                {n5,n5,n5,n5,n5},
                {n5,n5,n5,n5,n5},
                {n5,n5,n5,n5,n5}};
                
                
float[][] lapl = {{-1,0,-1},
                    {0,4,0},
                  {-1,0,-1}};

float[][] sobX={ {-1,-2,-1},
                  {0,0,0},
                  {1,2,1}};
                  
float[][] sharp={{-1,0,-1},
                  {0,5,0},
                  {-1,0,-1}};
                  
float[][] random={{2,-2,-3},
                  {2,-1,0.5},
                  {-1,4,2}};


void setup()
{
  size(1200,720);
  Im = loadImage("lena.png");
  Im.resize(400,360);
  Im.filter(GRAY);
  
  In3 = converti(convoluzione(Im,nbox3));
  In5 = converti(convoluzione(Im,nbox5));
  Il = converti(convoluzione(Im,lapl));
  Is=converti(convoluzione(Im,sharp));
  IsX=converti(convoluzione(Im,sobX));
  
  
  image(Im,0,0);
  image(In3,400,0);
  image(In5,800,0);
  image(Il,0,360);
  image(Is,400,360);
  image(IsX,800,360);
  
  
}

void draw(){}

float [][] convoluzione(PImage I, float [][] K)
{
  float [][] R = new float [I.width][I.height];
  
  //kernel
  int M = K.length;  //righe
  int N = K[0].length;  //colonne;
  
  PImage tmp;
  float res;
  
  for(int x=0; x<I.width; x++)
  {
    for(int y=0; y<I.height; y++)
    {
      tmp = I.get(x-M/2, y-N/2, M, N);     //Estrazione regione di interesse
      res = 0;
      
      for(int p=0; p<M; p++)
      {
        for(int q=0; q<N; q++)
        {
          res = res + brightness(tmp.get(p,q)) * K[p][q];        //Calcolo convoluzione
        }
      }
      
      R[x][y] = res;        //risultato convoluzione
    }
  }
  
  return R;
}


PImage converti(float [][] F)
{
  PImage R = createImage(F.length,F[0].length, RGB);
  float val=0;
  
  
  for(int x=0; x<R.width; x++)
  {
    for(int y=0; y<R.height; y++)
    {
      val = constrain(F[x][y], 0, 255);    //Normalizzazione del valore, constrain() forza il valore a rimanere nel range [0, 255]
      R.set(x,y,color(val));      //color(val) scala di grigi
    }
  }
  
  return R;
}

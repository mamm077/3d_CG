
#define nMesh 100
#define NUM_WAVE  20
int numWave;
float period = 0.5;
float lambda = 0.5;
float amp0 = 0.01;
float sizeX = 8.0;
float sizeY = 8.0;
float meshX = sizeX / (float)nMesh;
float meshY = sizeY / (float)nMesh;
float sX[NUM_WAVE], sY[NUM_WAVE];
float timeOccur[NUM_WAVE];
float data[(nMesh+1)*(nMesh+1)];
int interval = 100;


float getSingleWave(float r, float elapseTime, int k)
{
  float phase;
  float a;

  if(r < 0.2) r = 0.2;
  phase = 2.0 * PI * ( (elapseTime - timeOccur[k]) /period - r / lambda);

  if(phase >= 0.0 && phase < 2.0 * PI) 
		a = (float)( amp0 * sin(phase) )  / (sqrt(r)) ;
  else
    a = 0.0f;

  return( a );
}

void makeWave(float elapseTime)
{
  int i, j, k;
  float x, y, r;

  //Clear Wave
  for(j = 0; j <= nMesh; j++)
      for(i = 0; i <= nMesh; i++) data[j * (nMesh + 1) + i] = 0.0;

  for(k = 0; k < NUM_WAVE; k++)
  {
    for(j = 0; j <= nMesh; j++)
    {
      y = (float)( - nMesh / 2 + j) * meshY - sY[k];
      for(i = 0; i <= nMesh; i++)
      {
        x = (float)( - nMesh / 2 + i) * meshX - sX[k];
        r = sqrt( x * x + y * y);
        data[j * (nMesh + 1) + i] += getSingleWave(r, elapseTime, k);
      }
    }
  }
}



void calcNormal(float* p1,float* p2,float* p3,float* nn)
{
    CVector A = CVector(p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]);
    CVector B = CVector(p3[0] - p2[0], p3[1] - p2[1], p3[2] - p2[2]);
    CVector n = A ^ B;//ŠOÏ
    n.normalize();
    nn[0] = n.x; nn[1] = n.y; nn[2] = n.z;
}


void drawElevation1(int Nx, int Ny, float sizeX, float sizeY, int sideFlag, float* data)
{



    const int NMAX = 130;
    int i, j;
    float p[NMAX][NMAX][3];
    float a[NMAX][NMAX], b[NMAX][NMAX], c[NMAX][NMAX];
    float pitchX, pitchY;
    float n1[3], n2[3], n3[3], n4[3];

    
    if(Nx > NMAX) printf("Nx > NMAX \n");
    if(Ny > NMAX) printf("Ny > NMAX \n");
    

    pitchX = sizeX / (float)Nx;
    pitchY = sizeY / (float)Ny;
    

    for(j = 0; j <= Ny; j++){
        for(i = 0; i <= Nx; i++){
            p[i][j][0] = (float)(i - Nx / 2) * pitchX;
            p[i][j][1] = (float)(j - Ny / 2) * pitchY;
            p[i][j][2] = data[j * (Nx+1) + i];
        }
    }
    
    

    for(i = 0;i <= Nx;i++)
        for(j = 0;j <= Ny;j++)
        {
            if(j == 0 )
            {
                if(i == 0)
                {
                    calcNormal(p[0][0],p[1][0],p[0][1],n1);
                    a[i][j] = n1[0]; b[i][j] = n1[1]; c[i][j] = n1[2]; }
                else if(i == Nx)
                {
                    calcNormal(p[Nx-1][0],p[Nx][0],p[Nx][1],n1);
                    a[i][j] = n1[0]; b[i][j] = n1[1]; c[i][j] = n1[2]; }
                else
                {
                    calcNormal(p[i][0],p[i][1],p[i-1][0],n1);
                    calcNormal(p[i][0],p[i+1][0],p[i][1],n2);
                    a[i][j] = (n1[0]+n2[0])/2.0f;
                    b[i][j] = (n1[1]+n2[1])/2.0f;
                    c[i][j] = (n1[2]+n2[2])/2.0f; }
            }
            else if(j == Ny)
            {
                if(i == 0)
                {
                    calcNormal(p[0][Ny],p[0][Ny-1],p[1][Ny],n1);
                    a[i][j] = n1[0]; b[i][j] = n1[1]; c[i][j] = n1[2]; }
                else if(i == Nx)
                {
                    calcNormal(p[Nx][Ny],p[Nx-1][Ny],p[Nx][Ny-1],n1);
                    a[i][j] = n1[0]; b[i][j] = n1[1]; c[i][j] = n1[2]; }
                else
                {
                    calcNormal(p[i][Ny],p[i-1][Ny],p[i][Ny-1],n1);
                    calcNormal(p[i][Ny],p[i][Ny-1],p[i+1][Ny],n2);
                    a[i][j] = (n1[0]+n2[0])/2.0f;
                    b[i][j] = (n1[1]+n2[1])/2.0f;
                    c[i][j] = (n1[2]+n2[2])/2.0f; }
            }
            else
            {
                if(i == 0)
                {
                    calcNormal(p[0][j],p[1][j],p[0][j+1],n1);
                    calcNormal(p[0][j],p[0][j-1],p[0][1],n2);
                    a[i][j] = (n1[0]+n2[0])/2.0f;
                    b[i][j] = (n1[1]+n2[1])/2.0f;
                    c[i][j] = (n1[2]+n2[2])/2.0f; }
                else if(i == Nx)
                {
                    calcNormal(p[Nx][j],p[Nx][j+1],p[Nx-1][j],n1);
                    calcNormal(p[Nx][j],p[Nx-1][j],p[Nx][j-1],n2);
                    a[i][j] = (n1[0]+n2[0])/2.0f;
                    b[i][j] = (n1[1]+n2[1])/2.0f;
                    c[i][j] = (n1[2]+n2[2])/2.0f; }
                else
                {
                    calcNormal(p[i][j],p[i][j+1],p[i-1][j],n1);
                    calcNormal(p[i][j],p[i+1][j],p[i][j+1],n2);
                    calcNormal(p[i][j],p[i-1][j],p[i][j-1],n3);
                    calcNormal(p[i][j],p[i][j-1],p[i+1][j],n4);
                    a[i][j] = (n1[0]+n2[0]+n3[0]+n4[0])/4.0f;
                    b[i][j] = (n1[1]+n2[1]+n3[1]+n4[1])/4.0f;
                    c[i][j] = (n1[2]+n2[2]+n3[2]+n4[2])/4.0f; }
            }
        }

    for(j = 0;j < Ny;j++)
        for(i = 0;i < Nx;i++)
        {
            glBegin(GL_TRIANGLES);
            glNormal3d(a[i][j],b[i][j],c[i][j]);
            glVertex3fv(p[i][j]);
            glNormal3d(a[i+1][j],b[i+1][j],c[i+1][j]);
            glVertex3fv(p[i+1][j]);
            glNormal3d(a[i][j+1],b[i][j+1],c[i][j+1]);
            glVertex3fv(p[i][j+1]);
            glNormal3d(a[i+1][j],b[i+1][j],c[i+1][j]);
            glVertex3fv(p[i+1][j]);
            glNormal3d(a[i+1][j+1],b[i+1][j+1],c[i+1][j+1]);
            glVertex3fv(p[i+1][j+1]);
            glNormal3d(a[i][j+1],b[i][j+1],c[i][j+1]);
            glVertex3fv(p[i][j+1]);
            glEnd();
        }
    
    if(sideFlag == 1)
    {
        glBegin(GL_QUADS);

        glNormal3d(1.0, 0.0, 0.0);
        for(j = 0; j < Ny; j++)
        {
            glVertex3f(p[Nx][j][0], p[Nx][j][1], 0.0f);
            glVertex3f(p[Nx][j+1][0], p[Nx][j+1][1], 0.0f);
            glVertex3f(p[Nx][j+1][0], p[Nx][j+1][1], p[Nx][j+1][2]);
            glVertex3f(p[Nx][j][0], p[Nx][j][1], p[Nx][j][2]);
        }

        glNormal3d(-1.0, 0.0, 0.0); 
        for(j = 0; j < Ny; j++)
	  {
            glVertex3f(p[0][j][0], p[0][j][1], 0.0f);
            glVertex3f(p[0][j][0], p[0][j][1], p[0][j][2]);
            glVertex3f(p[0][j+1][0], p[0][j+1][1], p[0][j+1][2]);
            glVertex3f(p[0][j+1][0], p[0][j+1][1], 0.0f);
        }

        glNormal3d(0.0, 1.0, 0.0);
        for(i = 0; i < Nx; i++)
        {
            glVertex3f(p[i][Ny][0], p[i][Ny][1], 0.0f);
            glVertex3f(p[i][Ny][0], p[i][Ny][1], p[i][Ny][2]);
            glVertex3f(p[i+1][Ny][0], p[i+1][Ny][1], p[i+1][Ny][2]);
            glVertex3f(p[i+1][Ny][0], p[i+1][Ny][1], 0.0f);
        }

        glNormal3d(0.0, -1.0, 0.0);
        for(i = 0; i < Nx; i++)
        {
            glVertex3f(p[i][0][0], p[i][0][1], 0.0f);
            glVertex3f(p[i+1][0][0], p[i+1][0][1], 0.0f);
            glVertex3f(p[i+1][0][0], p[i+1][0][1], p[i+1][0][2]);
            glVertex3f(p[i][0][0], p[i][0][1], p[i][0][2]);
        }
        glEnd();
        
        
    }
}



void drawWave()
{
    static float diffuse[] = { 0.4f, 0.6f, 0.9f, 1.0f} ;
    static float ambient[] = { 0.1f, 0.2f, 0.3f, 1.0f};
    static float specular[]= { 1.0f, 1.0f, 1.0f, 1.0f};
    
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT,GL_SHININESS,10);
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    drawElevation1(nMesh, nMesh, sizeX, sizeY, 0, data);
    glPopMatrix();
    
}


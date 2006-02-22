#include <windows.h>
#include <gl\glut.h>//As linhas 58 e 59 do 'glut.h' incluem 'gl.h' e 'glu.h'
#include <stdio.h>
#include <math.h>

#define utMeuTipo int
#define TEXTO     "\nTexto de exemplo.\n"

//Tipo de projeção
const int PROJ_ORTO = 1;
const int PROJ_PERS = 2;
int tipo_proj = PROJ_PERS;

//Outras constantes
const GLfloat DEG     = M_PI/180;
const GLfloat VEL_MOV = 1.0;

//Parametros para alterar a projeção
GLdouble pr_c_x        =   1.0;//    Este centro é
GLdouble pr_c_y        =   0.0;//usado   nos  dois
GLdouble pr_c_z        =   0.0;//tipos de projeção
GLdouble pr_orto_z1    =  90.0;
GLdouble pr_orto_y1    =  45.0;
GLdouble pr_orto_z2    = 135.0;
GLdouble pr_pers_ang   =  50.0;
GLdouble pr_pers_prox  =   0.1;
GLdouble pr_pers_dist  = 100.0;
GLdouble pr_pers_aspec =   1.0;
GLdouble pr_cam_dist   =   5.0;//coordenadas esféricas//
GLdouble pr_cam_phi    =  30.0;//angulo em relação a 'z'
GLdouble pr_cam_theta  =  45.0;//angulo em relação a 'x'
GLdouble pr_direc_z    =   1.0;//valor 'z' indicando o teto da cena

int botao_mouse=-1; //indica qual o botão pressionado
int xm, xb, ym, yb;

const int C_PRETO    = 0;
const int C_VERMELHO =1;
const int C_VERDE    =2;
const int C_AMARELO  = C_VERMELHO+C_VERDE;
const int C_AZUL     =4;
const int C_VIOLETA  = C_VERMELHO+C_AZUL;
const int C_CIANO    = C_VERDE+C_AZUL;
const int C_BRANCO   = C_VERMELHO+C_VERDE+C_AZUL;
GLfloat Brilho=1.0;
GLfloat Cor[8][3]={
{  0.0*Brilho,  0.0*Brilho,  0.0*Brilho}, //[0]-Preto
{  1.0*Brilho,  0.0*Brilho,  0.0*Brilho}, //(1)-Vermelho
{  0.0*Brilho,  1.0*Brilho,  0.0*Brilho}, //(2)-Verde
{  1.0*Brilho,  1.0*Brilho,  0.0*Brilho}, //[3]-Amarelo
{  0.0*Brilho,  0.0*Brilho,  1.0*Brilho}, //(4)-Azul
{  1.0*Brilho,  0.0*Brilho,  1.0*Brilho}, //[5]-Violeta
{  0.0*Brilho,  1.0*Brilho,  1.0*Brilho}, //[6]-Ciano
{  1.0*Brilho,  1.0*Brilho,  1.0*Brilho}  //[7]-Branco
};

//Deste ponto em diante, modifique de acordo com o projeto atual
const int INC=0;
const int DIST=1;
const int TAM=2;
const int N_ETAPAS=3;

const int MAX_PARAM=4;//número de constantes logo acima
const GLfloat reset[MAX_PARAM]={1,pr_cam_dist,0.01,7};
GLfloat p[MAX_PARAM]={reset[0],reset[1],reset[2],reset[3]};

#define NUM_TETR_FACES     4

static GLdouble tet_r[4][3] =
{ {             1.0,             0.0,             0.0 },
  { -0.333333333333,  0.942809041582,             0.0 },
  { -0.333333333333, -0.471404520791,  0.816496580928 },
  { -0.333333333333, -0.471404520791, -0.816496580928 } } ;

static GLint tet_i[4][3] =  /* Vertex indices */
{
  { 1, 3, 2 }, { 0, 2, 3 }, { 0, 3, 1 }, { 0, 1, 2 }
} ;

void glutWireSierpinskiSponge ( int num_levels, GLdouble offset[3], GLdouble scale )
{
  int i, j ;

  //FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutWireSierpinskiSponge" );

  if ( num_levels <= 0 )
  {
    if (num_levels<0){num_levels=0;p[N_ETAPAS]=0;}
    for ( i = 0 ; i < NUM_TETR_FACES ; i++ )
    {
      glBegin ( GL_LINE_LOOP ) ;
      glNormal3d ( -tet_r[i][0], -tet_r[i][1], -tet_r[i][2] ) ;
      for ( j = 0; j < 3; j++ )
      {
        double x = offset[0] + scale * tet_r[tet_i[i][j]][0] ;
        double y = offset[1] + scale * tet_r[tet_i[i][j]][1] ;
        double z = offset[2] + scale * tet_r[tet_i[i][j]][2] ;
        glVertex3d ( x, y, z ) ;
      }

      glEnd () ;
    }
  }
  else
  {
    GLdouble local_offset[3] ;  /* Use a local variable to avoid buildup of roundoff errors */
    num_levels -- ;
    scale /= 2.0 ;
    for ( i = 0 ; i < NUM_TETR_FACES ; i++ )
    {
      local_offset[0] = offset[0] + scale * tet_r[i][0] ;
      local_offset[1] = offset[1] + scale * tet_r[i][1] ;
      local_offset[2] = offset[2] + scale * tet_r[i][2] ;
      glutWireSierpinskiSponge ( num_levels, local_offset, scale ) ;
    }
  }
}
void Des_Objeto(int Tipo){
 glPushMatrix();
 switch (Tipo){
 case 1:
  //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
  //glTranslatef(0.5, 0.5, 0.0);
  glBegin(GL_LINES);
   glColor3f(1.0,0.0,0.0);//x
     glVertex3f(0.0,0.0,0.0); glVertex3f(2,0.0,0.0);
   glColor3f(0.0,1.0,0.0);//y
     glVertex3f(0.0,0.0,0.0); glVertex3f(0.0,2,0.0);
   glColor3f(0.0,0.0,1.0);//z
     glVertex3f(0.0,0.0,0.0); glVertex3f(0.0,0.0,2);
  glEnd();
  break;
 case 2: 
  //F[0][0][0]=F[1][0][0]=F[0][1][0]=F[0][0][1]=F[0][2][0]=1;
  glColor3f(Cor[C_CIANO][0],Cor[C_CIANO][1],Cor[C_CIANO][2]);
  GLdouble offset[3]={0.0,0.0,0.0};
  glutWireSierpinskiSponge((int) p[N_ETAPAS],offset,1.0);
  break;

 }
 glPopMatrix();
}


void Exibe(){
 const GLdouble PHI=pr_cam_phi*DEG;
 const GLdouble THETA=pr_cam_theta*DEG;
 const GLdouble CAM_X = pr_c_x + p[DIST] * sin(PHI) * cos(THETA);
 const GLdouble CAM_Y = pr_c_y + p[DIST] * sin(PHI) * sin(THETA);
 const GLdouble CAM_Z = pr_c_z + p[DIST] * cos(PHI);
 GLdouble prof=(pr_pers_prox+pr_pers_dist)/2;
 
 /*GLfloat espec[]={0.5, 0.5, 0.5, 1.0};
 GLfloat emi[]={0.3, 0.6, 0.0, 0.0};
 GLfloat emi2[]={0.5, 0.0, 0.3, 0.0};
 GLfloat emi3[]={0.0, 0.0, 0.2, 0.0};*/
 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
  
  switch (tipo_proj){
  case PROJ_PERS:   
   gluPerspective (pr_pers_ang, pr_pers_aspec, pr_pers_prox, pr_pers_dist);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(CAM_X,   CAM_Y,  CAM_Z,  //Camera
             pr_c_x, pr_c_y, pr_c_z,  //Alvo (Centro do tabuleiro)
             0.0,       0.0, pr_direc_z); //Para cima
   break;
  case PROJ_ORTO:   
   glOrtho(-5.0,5.0,-5.0,5.0,prof,-prof);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glRotatef(pr_orto_z1,0.0,0.0,1.0);
   glRotatef(pr_orto_y1,0.0,1.0,0.0);
   glRotatef(pr_orto_z2,0.0,0.0,1.0);
   glTranslatef(pr_c_x,pr_c_y,pr_c_z);
   break;
  }   
  Des_Objeto(1);
  
  Des_Objeto(2);
  
  //glFlush(); 
  glutSwapBuffers();//caso doublebuffered...
 
}
/*void Redimensiona(int alt, int larg){
 glViewport (0, 0, (GLsizei) larg, (GLsizei) alt); 
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 pr_pers_aspec=(GLsizei) larg/(GLsizei) alt;
 gluPerspective (pr_pers_ang, pr_pers_aspec, pr_pers_prox, pr_pers_dist);
}*/

void Ini()
{/*Defina aqui os valores iniciais dos parâmetros mais importantes.
Exemplos:
 Tipo de projeção;
 Ponto de vista;
 Cor do fundo de tela;
 Modelos de Iluminação.
 */ 
 /*GLfloat ambiente[]={0.2, 0.2, 0.2, 1.0};
 GLfloat difusa[]={0.7, 0.7, 0.7, 1.0};
 GLfloat especular[]={1.0, 1.0, 1.0, 1.0};
 GLfloat posicao[]={0.0, 0.0, 2.0, 0.0};
 GLfloat lmodelo_ambiente[]={0.2, 0.2, 0.2, 1.0};*/

 const GLdouble PHI=pr_cam_phi*DEG;
 const GLdouble THETA=pr_cam_theta*DEG;
 const GLdouble CAM_X = pr_c_x + p[DIST] * sin(PHI) * cos(THETA);
 const GLdouble CAM_Y = pr_c_y + p[DIST] * sin(PHI) * sin(THETA);
 const GLdouble CAM_Z = pr_c_z + p[DIST] * cos(PHI);
 GLdouble prof=(pr_pers_prox+pr_pers_dist)/2;
  
  glClearColor(0.1*Cor[C_CIANO][0],
               0.1*Cor[C_CIANO][1],
               0.1*Cor[C_CIANO][2],0);
    glEnable (GL_DEPTH_TEST);//Testa os objetos, decidindo qual está na frente.
    
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  switch (tipo_proj){
  case PROJ_PERS:
   gluPerspective (pr_pers_ang, pr_pers_aspec, pr_pers_prox, pr_pers_dist);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(CAM_X+pr_c_x,  CAM_Y+pr_c_y,  CAM_Z+pr_c_z,  //Camera
                   pr_c_x,        pr_c_y,        pr_c_z,  //Alvo (Centro do tabuleiro)
                      0.0,           0.0,    pr_direc_z); //Para cima
   break;
  case PROJ_ORTO:
   glOrtho(-5.0,5.0,-5.0,5.0,-prof,prof);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glRotatef(pr_orto_z1,0.0,0.0,1.0);
   glRotatef(pr_orto_y1,0.0,1.0,0.0);
   glRotatef(pr_orto_z2,0.0,0.0,1.0);
   glTranslatef(pr_c_x,pr_c_y,pr_c_z);
   break;
  }  
  //quad=gluNewQuadric(); 
}
void Teclado(unsigned char key, int x, int y)
{
 static int p_atual=DIST; 
 
 if (48<=key && key<=57){
  p_atual=(key-48)<MAX_PARAM?key-48:DIST;
  return;
 }
 else{
  switch(key){
   case 27:
       exit(0);
       break;
   case '+':
   case GLUT_KEY_PAGE_DOWN:
    if(p_atual==INC) p[p_atual]*=10;
    else if (p_atual==DIST) p[p_atual]-=p[INC];
    else p[p_atual]+=p[INC];
    
    break;
   case '-':
   case GLUT_KEY_PAGE_UP:
    if(p_atual==INC) p[p_atual]/=10;
    else if (p_atual==DIST) p[p_atual]+=p[INC];
    else p[p_atual]-=p[INC];
    
    break;
   case 'r':
   case 'R':
    for (int i=0;i<MAX_PARAM;i++) p[i]=reset[i];
    pr_cam_dist=5.0; pr_cam_phi=30.0; pr_cam_theta =45.0;
    pr_direc_z=1.0;
    break;
   default:
    return;break;
  }
  glutPostRedisplay();
 }
}

void Mouse_click(int b,int state,int x, int y)
{
 botao_mouse=b;
 switch(b) {
 case GLUT_LEFT_BUTTON:
  switch(state) {
    case GLUT_DOWN:     
     xb = x;
     yb = y;
     break;
    case GLUT_UP:
     botao_mouse=-1;
     switch (tipo_proj){
     case PROJ_PERS:
      pr_cam_theta -= VEL_MOV*(xm - xb);
       if  (pr_cam_theta>180) pr_cam_theta-=360;
       if (-pr_cam_theta>180) pr_cam_theta+=360;
      pr_cam_phi   -= VEL_MOV*(ym - yb);  
       if  (pr_cam_phi>180){pr_cam_phi-=360; pr_direc_z = -1.0;}
       if (-pr_cam_phi>180){pr_cam_phi+=360; pr_direc_z = 1.0;}
       
       if (pr_cam_phi*pr_direc_z<0) pr_direc_z = -pr_direc_z;
       if (pr_cam_phi==0) pr_cam_phi=0.0001*pr_direc_z;
      break;
     case PROJ_ORTO:
      pr_orto_z2 += VEL_MOV*(xm - xb);//theta
      pr_orto_y1 -= VEL_MOV*(ym - yb);//phi
      break;
     }
    break;
  }//switch (state)
  break;
 case GLUT_RIGHT_BUTTON:
  break;
 }//switch (b)
}
void Mouse_mov(int x, int y)
{
 if (botao_mouse!=GLUT_LEFT_BUTTON) return;
 xm = x;
 ym = y;
 switch (tipo_proj){
 case PROJ_PERS:

  pr_cam_theta -= VEL_MOV*(xm - xb);
  pr_cam_phi   -= VEL_MOV*(ym - yb);
  if  (pr_cam_phi>180){pr_cam_phi-=360; pr_direc_z = -1.0;}
  if (-pr_cam_phi>180){pr_cam_phi+=360; pr_direc_z = 1.0;}
  if (pr_cam_phi*pr_direc_z<0) pr_direc_z = -pr_direc_z;
  if (pr_cam_phi==0) pr_cam_phi=0.0001*pr_direc_z;  

  Exibe();//glutPostRedisplay();
  
  pr_cam_theta += VEL_MOV*(xm - xb);
  pr_cam_phi   += VEL_MOV*(ym - yb);
  
  break;
 case PROJ_ORTO:
  pr_orto_z2 += VEL_MOV*(xm - xb);//theta
  pr_orto_y1 -= VEL_MOV*(ym - yb);//phi
  
  Exibe();
  
  pr_orto_z2 -= VEL_MOV*(xm - xb);//theta
  pr_orto_y1 += VEL_MOV*(ym - yb);//phi
  break;
 }
}
int main(int argc, char **argv)
{
   glutInit(&argc,argv);
   //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(700,700);
   glutInitWindowPosition(0,0);
   glutCreateWindow("Sierpinsk");
   //glutFullScreen();
   
   Ini();
   
   glutDisplayFunc(Exibe);  
   glutKeyboardFunc(Teclado);
   //glutReshapeFunc(Redimensiona);
   glutMouseFunc(Mouse_click);
   glutMotionFunc(Mouse_mov);
   glutMainLoop();
 return 0;
}

#include <windows.h>
#include <gl\glut.h>//As linhas 58 e 59 do 'glut.h' incluem 'gl.h' e 'glu.h'
#include <stdio.h>
#include <math.h>

#define utMeuTipo int
#define TEXTO     "\nTexto de exemplo.\n"

//Tipo de projeção
const int PROJ_ORTO = 1;
const int PROJ_PERS = 2;
int tipo_proj = 2;

//Outras constantes
const GLfloat VEL_MOV = 1.0;
const GLdouble TAM=3.0; 
//Parametros para alterar a projeção
GLdouble pr_c_x        =   0.0;
GLdouble pr_c_y        =   0.0;
GLdouble pr_c_z        =   TAM;
GLdouble pr_orto_z1    =  90.0;
GLdouble pr_orto_y1    =  45.0;
GLdouble pr_orto_z2    = 135.0;
GLdouble pr_pers_ang   =  50.0;
GLdouble pr_pers_prox  =   1.0;
GLdouble pr_pers_dist  = 100.0;
GLdouble pr_pers_aspec =   1.0;
GLdouble pr_cam_dist   =  15.0;//coordenadas esféricas//
GLdouble pr_cam_phi    =  40.0;//angulo em relação a 'z'
GLdouble pr_cam_theta      =  20.0;//angulo em relação a 'x'
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
{  0.42*Brilho,  0.21*Brilho,  0.18*Brilho}, //[0]-Preto
{  0.37*Brilho,  0.25*Brilho,  0.15*Brilho}, //(1)-Vermelho
{  0.32*Brilho,  0.29*Brilho,  0.13*Brilho}, //(2)-Verde
{  0.27*Brilho,  0.33*Brilho,  0.10*Brilho}, //[3]-Amarelo
{  0.21*Brilho,  0.38*Brilho,  0.08*Brilho}, //(4)-Azul
{  0.16*Brilho,  0.42*Brilho,  0.05*Brilho}, //[5]-Violeta
{  0.11*Brilho,  0.46*Brilho,  0.03*Brilho}, //[6]-Ciano
{  0.06*Brilho,  0.50*Brilho,  0.00*Brilho}  //[7]-Branco
};
const GLfloat PI = M_PI;
const GLfloat PI2 = 2*M_PI;
const GLfloat DEG = PI/180;//1.74532925199433E-02
const GLfloat div_theta = 3;
const GLfloat phi   = 29;
const GLfloat FATOR_RED = 0.53;
const int MAX_N=8;


void Desenha_galhos(int n){
 int i;
 GLfloat r=TAM;
 
 for(i=n;i<MAX_N;i++) r*=FATOR_RED;

 if (n>0){
  for (i=0;i<div_theta;i++){
   glPushMatrix();        
    glTranslatef(0.0, 0.0, r);
    glRotatef(i*360/div_theta,0.0,0.0,1.0);
    glRotatef(phi,0.0,1.0,0.0);

    glColor3f(Cor[(MAX_N-n)%8][0],Cor[(MAX_N-n)%8][1],Cor[(MAX_N-n)%8][2]);
    glBegin(GL_LINES);
     glVertex3f(0.0,0.0,0.0);
     glVertex3f(0.0,0.0,r*FATOR_RED);
    glEnd();
    
    Desenha_galhos(n-1);
    
   glPopMatrix();     
  }         
 }             
}
void Des_Objeto(int Tipo){
 glPushMatrix();
 switch (Tipo){
 case 1:
  //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
  //glTranslatef(0.5, 0.5, 0.0);
   //glColor3f(0.5,0.4,0.2);
   glLineWidth(2.0);
   Desenha_galhos(MAX_N); 
  break;
 case 2:
  glBegin(GL_LINES);
//  glColor3f(1.0,0.0,0.0);//x
//    glVertex3f(0.0,0.0,0.0); glVertex3f(TAM,0.0,0.0);
//  glColor3f(0.0,1.0,0.0);//y
//    glVertex3f(0.0,0.0,0.0); glVertex3f(0.0,TAM,0.0);
  glColor3f(0.30, 0.15, 0.13);//z
    glVertex3f(0.0,0.0,0.0); glVertex3f(0.0,0.0,TAM);
  glEnd();
  glColor3f(0.20, 0.30, 0.20);
   glBegin(GL_QUAD_STRIP); 
    glVertex3f(-TAM/2,-TAM/2,0.0); glVertex3f(-TAM/2,TAM/2,0.0); 
    glVertex3f(+TAM/2,-TAM/2,0.0); glVertex3f(+TAM/2,TAM/2,0.0); 
   glEnd();
  break;
 default:
 
  break;
 }
 glPopMatrix();
}

void Exibe(){
 const GLdouble cam_x = pr_c_x + pr_cam_dist * sin(pr_cam_phi*DEG) * cos(pr_cam_theta*DEG);
 const GLdouble cam_y = pr_c_y + pr_cam_dist * sin(pr_cam_phi*DEG) * sin(pr_cam_theta*DEG);
 const GLdouble cam_z = pr_c_z + pr_cam_dist * cos(pr_cam_phi*DEG);
 GLdouble prof=(pr_pers_prox+pr_pers_dist)/2;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
  
  switch (tipo_proj){
  case PROJ_PERS:   
   gluPerspective (pr_pers_ang, pr_pers_aspec, pr_pers_prox, pr_pers_dist);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(cam_x,   cam_y,  cam_z,  //Camera
             pr_c_x, pr_c_y, pr_c_z,  //Alvo (Centro do tabuleiro)
             0.0,       0.0,    1.0); //Para cima
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

 const GLdouble cam_x = pr_c_x + pr_cam_dist * sin(pr_cam_phi*DEG) * cos(pr_cam_theta*DEG);
 const GLdouble cam_y = pr_c_y + pr_cam_dist * sin(pr_cam_phi*DEG) * sin(pr_cam_theta*DEG);
 const GLdouble cam_z = pr_c_z + pr_cam_dist * cos(pr_cam_phi*DEG);
 GLdouble prof=(pr_pers_prox+pr_pers_dist)/2;
  
  glClearColor(0.0,0.4,0.6,0.0);
    glEnable (GL_DEPTH_TEST);//Testa os objetos, decidindo qual está na frente.

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  switch (tipo_proj){
  case PROJ_PERS:
   gluPerspective (pr_pers_ang, pr_pers_aspec, pr_pers_prox, pr_pers_dist);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(cam_x+pr_c_x,  cam_y+pr_c_y,  cam_z+pr_c_z,  //Camera
                   pr_c_x,        pr_c_y,        pr_c_z,  //Alvo (Centro do tabuleiro)
                   0.0,        0.0,        1.0); //Para cima
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

}
void Teclado(unsigned char key, int x, int y)
{
  char a[1]={key};
    switch(key){
    case 27:
        exit(0);
        break;
    case '+':
    case GLUT_KEY_PAGE_DOWN:
        pr_cam_dist--;
        glutPostRedisplay();
        break;
    case '-':
    case GLUT_KEY_PAGE_UP:
        pr_cam_dist++;
        glutPostRedisplay();
        break;
    default:
     break;
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
      pr_cam_phi   -= VEL_MOV*(ym - yb);  
      //if (pr_cam_phi==0) pr_cam_phi:0.001;
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
 //static int sx=xm>x?1:-1;
 //static int sy=ym>y?1:-1;
 
 if (botao_mouse!=GLUT_LEFT_BUTTON) return;
 xm = x;
 ym = y;
 switch (tipo_proj){
 case PROJ_PERS:
  //if ((xm-x)*sx<0) {sx=-sx;xb = x;}     
  //if ((ym-y)*sy<0) {sy=-sy;yb = y;}
 
  pr_cam_theta -= VEL_MOV*(xm - xb);
  pr_cam_phi   -= VEL_MOV*(ym - yb);
  
  //if (pr_cam_phi==0) pr_cam_phi:0.001;
  
  /*pr_cam_phi= pr_cam_phi<=180?pr_cam_phi:180;
  pr_cam_phi= 180>=-pr_cam_phi?pr_cam_phi:-180;*/
  
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
   glutInitWindowSize(500,500);
   glutInitWindowPosition(0,0);
   glutCreateWindow("Objetos 3d");
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


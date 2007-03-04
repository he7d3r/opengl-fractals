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
const GLfloat PI = M_PI;   //3.1415926535897932384626433832795
const GLfloat DEG = PI/180;//0.017453292519943295769236907684886
const GLfloat PI2 = 2*PI;  //6.283185307179586476925286766559

const GLfloat VEL_MOV = 1.0;
//const GLdouble TAM=3.0;


//Parametros para alterar a projeção
GLdouble pr_c_x        =   0.0;//    Este centro é
GLdouble pr_c_y        =   0.0;//usado   nos  dois
GLdouble pr_c_z        =   0.0;//tipos de projeção
GLdouble pr_orto_z1    =  90.0;
GLdouble pr_orto_y1    =  45.0;
GLdouble pr_orto_z2    = 135.0;
GLdouble pr_pers_ang   =  50.0;
GLdouble pr_pers_prox  =   0.1;
GLdouble pr_pers_dist  = 100.0;
GLdouble pr_pers_aspec =   1.0;
GLdouble pr_cam_dist   =   15.0;//coordenadas esféricas//
GLdouble pr_cam_phi    =  50.0;//angulo em relação a 'z'
GLdouble pr_cam_theta  =  55.0;//angulo em relação a 'x'
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

const int INC  = 0;
const int DIST = 1;
const int TAM  = 2;
const int N_IT = 3;
const int DIV  = 4;
const int PHI  = 5;
const int RED  = 6;

const int MAX_PARAM=7;//número de constantes logo acima

const GLfloat reset[MAX_PARAM]={1,pr_cam_dist,3.0,4,3,29,0.53};
GLfloat p[MAX_PARAM]={reset[0],reset[1],reset[2],reset[3],reset[4],reset[5],reset[6]};

GLfloat Cor1[3]={0.52*Brilho,  0.21*Brilho,  0.18*Brilho};
GLfloat Cor2[3]={0.16*Brilho,  0.90*Brilho,  0.10*Brilho};

GLfloat inc_cor[3]={(Cor2[0]-Cor1[0])/p[N_IT],
                    (Cor2[1]-Cor1[1])/p[N_IT],
                    (Cor2[2]-Cor1[2])/p[N_IT]};

void Desenha_galhos(GLfloat n){
 GLfloat i;
 GLfloat r=p[TAM];
 
 for(i=n;i<p[N_IT];i++) r*=p[RED];

 if (n>0){
  for (i=0;i<p[DIV];i++){
   glPushMatrix();    
   
       
    glTranslatef(0.0, 0.0, r);
    glRotatef(i*360/p[DIV],0.0,0.0,1.0);
    glRotatef(p[PHI],0.0,1.0,0.0);

    glColor3f(Cor1[0]+(p[N_IT]-n)*inc_cor[0],
              Cor1[1]+(p[N_IT]-n)*inc_cor[1],
              Cor1[2]+(p[N_IT]-n)*inc_cor[2]);
    
    glLineWidth(n/2);          
    glBegin(GL_LINES);
     glVertex3f(0.0,0.0,0.0);
     glVertex3f(0.0,0.0,r*p[RED]);
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
  glColor3f(0.10, 0.35, 0.10);
   glBegin(GL_QUAD_STRIP); 
    glVertex3f(-2,-2,0.0); glVertex3f(-2,2,0.0); 
    glVertex3f(+2,-2,0.0); glVertex3f(+2,2,0.0); 
   glEnd();
  break;
 case 2:
  //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
  //glTranslatef(0.5, 0.5, 0.0);
   //glColor3f(0.5,0.4,0.2);
  glLineWidth(p[N_IT]/2);
  glBegin(GL_LINES);
   glColor3f(Cor1[0]/2,Cor1[1]/2,Cor1[2]/2);//z
   glVertex3f(0.0,0.0,0.0); glVertex3f(0.0,0.0,p[TAM]);
  glEnd();         
  Desenha_galhos(p[N_IT]); 
  break;
 default:
 
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

void Ini()
{
 const GLdouble PHI=pr_cam_phi*DEG;
 const GLdouble THETA=pr_cam_theta*DEG;
 const GLdouble CAM_X = pr_c_x + p[DIST] * sin(PHI) * cos(THETA);
 const GLdouble CAM_Y = pr_c_y + p[DIST] * sin(PHI) * sin(THETA);
 const GLdouble CAM_Z = pr_c_z + p[DIST] * cos(PHI);
 GLdouble prof=(pr_pers_prox+pr_pers_dist)/2;
  
  glClearColor(0.4*Cor[C_CIANO][0],
               0.4*Cor[C_CIANO][1],
               0.4*Cor[C_CIANO][2],0);
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
        switch(p_atual){
        case INC:
         p[p_atual]*=10;
         break;
        case DIST:
         p[p_atual]-=p[INC];
         break;
        case N_IT:
          p[p_atual]++;
          inc_cor[0]=(Cor2[0]-Cor1[0])/p[N_IT];
          inc_cor[1]=(Cor2[1]-Cor1[1])/p[N_IT];
          inc_cor[2]=(Cor2[2]-Cor1[2])/p[N_IT];
          break;
        case RED:
          p[p_atual]+=p[INC]/100;
          break;
        default:     
         p[p_atual]+=p[INC];            
         break;
         }
    break;
   case '-':
   case GLUT_KEY_PAGE_UP:
        switch(p_atual){
        case INC:
         p[p_atual]/=10;
         break;
        case DIST:
         p[p_atual]+=p[INC];
         break;     
        case N_IT:
          p[p_atual]--;
          inc_cor[0]=(Cor2[0]-Cor1[0])/p[N_IT];
          inc_cor[1]=(Cor2[1]-Cor1[1])/p[N_IT];
          inc_cor[2]=(Cor2[2]-Cor1[2])/p[N_IT];
          break;
        case RED:
          p[p_atual]-=p[INC]/100;
          break;
        default:     
         p[p_atual]-=p[INC];            
         break;
        break;
        }
    break;
   case 'r':
   case 'R':
    for (int i=0;i<MAX_PARAM;i++) p[i]=reset[i];
    pr_cam_dist=15.0; pr_cam_phi=50.0; pr_cam_theta =55.0;
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

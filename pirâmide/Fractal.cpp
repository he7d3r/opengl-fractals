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
const GLfloat DEG     = M_PI/180;
const GLfloat VEL_MOV = 1.0;

//Parametros para alterar a projeção
GLdouble pr_c_x        =   0.0;//    Este centro é
GLdouble pr_c_y        =   0.0;//usado   nos  dois
GLdouble pr_c_z        =   0.0;//tipos de projeção
GLdouble pr_orto_z1    =  90.0;
GLdouble pr_orto_y1    =  45.0;
GLdouble pr_orto_z2    = 135.0;
GLdouble pr_pers_ang   =  50.0;
GLdouble pr_pers_prox  =   1.0;
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

//Aqui começam as declarações específicas deste projeto
const int MAX_PARAM=4;

const int INC=0;
const int RAZAO=1;
const int POS=2;
const int DIST=3;

GLfloat p[MAX_PARAM]={0.1,//INC
                      0.5,//RAZAO
                      1.0,//POS
                      pr_cam_dist};//DIST. da camera

const int MAX_SORT=10000; 
const int MAX_VERT=4;
int v_sort[MAX_SORT];

const GLdouble TAM=3.0; //glutSolidCube(TAM);

void Sorteia_pontos (){ 
 for (int c=0;c<MAX_SORT;c++)
  v_sort[c]=(int)rand()%MAX_VERT;
}

void Des_PontosAleatorios(){ 
 int c;
 GLfloat ult[3]={0.5,0.5,0.5};
 GLfloat v[4][3]={{0,0,0},{1,0,0},{0,1,0},{1-p[POS],1-p[POS],p[POS]}};

 glBegin(GL_POINTS);
 for (c=0;c<MAX_SORT;c++){ 
  if (v_sort[c]!=v_sort[c-1]){ 
   glColor3f(Cor[1+v_sort[c]][0], Cor[1+v_sort[c]][1], Cor[1+v_sort[c]][2]);
   /*switch (v_sort[c]){
   case 0:
    glColor3f(Cor[C_BRANCO][0], Cor[C_BRANCO][1], Cor[C_BRANCO][2]);break;   
   case 1:
    glColor3f(Cor[C_VERMELHO][0], Cor[C_VERMELHO][1], Cor[C_VERMELHO][2]);break;
   case 2:
    glColor3f(Cor[C_VERDE][0], Cor[C_VERDE][1], Cor[C_VERDE][2]);break;
   case 3:
    glColor3f(Cor[C_CIANO][0], Cor[C_CIANO][1], Cor[C_CIANO][2]);break;
   }*/
  }
  ult[0]+=p[RAZAO]*(v[v_sort[c]][0] - ult[0]);
  ult[1]+=p[RAZAO]*(v[v_sort[c]][1] - ult[1]);
  ult[2]+=p[RAZAO]*(v[v_sort[c]][2] - ult[2]);
  glVertex3f(ult[0], ult[1], ult[2]);  
 }
 glEnd();
}
void Des_Objeto(int Tipo){
 glPushMatrix();
 switch (Tipo){
 case 1:
  glBegin(GL_LINES);
   glColor3f(Cor[C_VERMELHO][0],Cor[C_VERMELHO][1],Cor[C_VERMELHO][2]);//x
     glVertex3f(0.0,0.0,0.0); glVertex3f(2,0.0,0.0);
   glColor3f(Cor[C_VERDE][0],Cor[C_VERDE][1],Cor[C_VERDE][2]);//y
     glVertex3f(0.0,0.0,0.0); glVertex3f(0.0,2,0.0);
   glColor3f(Cor[C_AZUL][0],Cor[C_AZUL][1],Cor[C_AZUL][2]);//z
     glVertex3f(0.0,0.0,0.0); glVertex3f(0.0,0.0,2);
  glEnd(); 
  break;
 case 2: 
  Des_PontosAleatorios();
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
  //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
  
  Des_Objeto(1);
  Des_Objeto(2);
  //glFlush(); 
  glutSwapBuffers();//caso doublebuffered...
 
}

void Ini()
{/*Defina aqui os valores iniciais dos parâmetros mais importantes.
Exemplos:
 Tipo de projeção;
 Ponto de vista;
 Cor do fundo de tela;
 Modelos de Iluminação.
 */ 
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
  Sorteia_pontos();
}
void Teclado(unsigned char key, int x, int y)
{
 static int p_atual=DIST;
 const GLfloat reset[MAX_PARAM]={0.1,0.5,1.0,pr_cam_dist};
 
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


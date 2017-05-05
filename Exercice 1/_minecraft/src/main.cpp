//Includes application
#include <conio.h>
#include <vector>
#include <windows.h>

#include "external/gl/glew.h"
#include "external/gl/freeglut.h"

//Moteur
#include "engine/utils/types_3d.h"
#include "engine/timer.h"
#include "engine/log/log_console.h"
#include "engine/render/renderer.h"
#include "engine/gui/screen.h"
#include "engine/gui/screen_manager.h"

//Pour avoir le monde
#include "Exercice 4/world.h"
//Pour avoir l'avatar
#include "Exercice 7/avatar.h"

//Variable globale

//World
NYWorld * g_world;

NYRenderer * g_renderer = NULL;
NYTimer * g_timer = NULL;
int g_nb_frames = 0;
float g_elapsed_fps = 0;
int g_main_window_id;
int g_mouse_btn_gui_state = 0;
bool g_fullscreen = false;

//Character
NYAvatar * g_avatar;

GLuint g_program;

//GUI 
GUIScreenManager * g_screen_manager = NULL;
GUIBouton * BtnParams = NULL;
GUIBouton * BtnClose = NULL;
GUILabel * LabelFps = NULL;
GUILabel * LabelCam = NULL;
GUIScreen * g_screen_params = NULL;
GUIScreen * g_screen_jeu = NULL;
GUISlider * g_slider;

//SUN
/*NYVert3Df g_sun_dir;
NYColor g_sun_color;
float g_mn_lever = 6.0f * 60.0f;
float g_mn_coucher = 19.0f * 60.0f;		
float g_tweak_time = 0;
bool g_fast_time = false;*/

//////////////////////////////////////////////////////////////////////////
// GESTION APPLICATION
//////////////////////////////////////////////////////////////////////////
void update(void)
{

	float elapsed = g_timer->getElapsedSeconds(true);

	static float g_eval_elapsed = 0;

	//Calcul des fps
	g_elapsed_fps += elapsed;
	g_nb_frames++;
	if(g_elapsed_fps > 1.0)
	{
		LabelFps->Text = std::string("FPS : ") + toString(g_nb_frames);
		g_elapsed_fps -= 1.0f;
		g_nb_frames = 0;
	}

	//Tweak time
	/*if (g_fast_time)
		g_tweak_time += elapsed * 120.0f;*/

	//g_renderer->_Camera->moveTo(g_avatar->Position);//g_avatar->Position.X - 5, g_avatar->Position.Y - 5, g_avatar->Position.Z - - 5));
	g_avatar->update(elapsed);
	g_renderer->_Camera->setPosition(g_avatar->Position);
	//Rendu
	g_renderer->render(elapsed);
}


void render2d(void)
{
	g_screen_manager->render();
}

/*GLfloat* test(double r, double g, double b, double a)
{
	GLfloat _materialDiffuse[] = { r, g, b, a };
	return _materialDiffuse;
}*/

void renderObjects(void)
{
	//Rendu des axes
	
	glEnable(GL_LIGHTING);

	//Dessin des axes : on dessine des lignes
	glBegin(GL_LINES);

	//Premiere primitive : axe des x
	glColor3d(1,0,0);
	glVertex3d(0,0,0);
	glVertex3d(10000,0,0);

	//Deuxieme primitive : axe des y
	glColor3d(0,1,0);
	glVertex3d(0,0,0);
	glVertex3d(0,10000,0);

	//Troisieme primitive : axe des z
	glColor3d(0,0,1);
	glVertex3d(0,0,0);
	glVertex3d(0,0,10000);

	/*glColor3d(1, 0, 0);
	glVertex3d(g_renderer->_Camera->_Position.X, g_renderer->_Camera->_Position.Y, g_renderer->_Camera->_Position.Z);
	glVertex3d(g_renderer->_Camera->_LookAt.X, g_renderer->_Camera->_LookAt.Y, g_renderer->_Camera->_LookAt.Z);*/
	glEnd();


	//NYVert3Df posSun(10, 0, 0);
	//rotateAround(NYRenderer::_DeltaTimeCumul * 100);

	//A rajouter pour debug : rotation dans le temps
	/*glRotatef(NYRenderer::_DeltaTimeCumul * 100,
		g_slider->Value*10.0f, 1, cos(NYRenderer::_DeltaTimeCumul));*/

	//Exercice 2
	//Placement du cube en (2, 2, 0)

	//Solution 1 : translation puis rotation
	/*glTranslatef(2, 2, 0);
	glRotatef(45, 0, 0, 1);*/

	
	//Solution 2 : rotation puis translation
	/*glRotatef(45, 0, 0, 1);
	glTranslatef(sqrtf(8.f), 0, 0);*/

	/*
	glRotatef(NYRenderer::_DeltaTimeCumul * 100, 1, 1, 0);

	//Exercice 1
	//Rendu du cube

	//Material speculaire for all the cube
	//Speculaire
	GLfloat whiteSpecularMaterial[] = { 0, 0, 0, 1.0 };
	GLfloat mShininess = 100;
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecularMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, mShininess);

	//Pour dessiner des quads
	glBegin(GL_QUADS);

	//Materials
	double _diffuse = 0.7;
	double _ambient = 0.2;

	GLfloat materialDiffuse[] = { _diffuse, 0, 0, 1.0 };
	GLfloat materialAmbient[] = { _ambient, 0, 0, 1.0 };

	//Materials	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse); ///Diffuse
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient); ///Ambient

	//FACE 1 RED
	//On set la normale
	glNormal3f(1, 0, 0);
	//Sommets
	//glColor3d(1 , 0 , 0 );
	glVertex3d(1 , 1 , 1 );
	glVertex3d(1 , -1 , 1 );
	glVertex3d(1 , -1 , -1 );
	glVertex3d(1 , 1 , -1 );

	//FACE 4 YELLOW
	//On set la normale
	glNormal3f(-1, 0, 0);
	//Sommets
	//glColor3d(1, 1, 0);
	glVertex3d(-1, -1, 1);
	glVertex3d(-1, 1, 1);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, -1, -1);

	//Materials
	materialDiffuse[0] = 0.0f;
	materialDiffuse[1] = _diffuse;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse); ///Diffuse
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = _ambient;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient); ///Ambient

	//FACE 2 GREEN
	//On set la normale
	glNormal3f(0, 1, 0);
	//Sommets
	//glColor3d(0, 1, 0);
	glVertex3d(1, 1, 1);
	glVertex3d(1, 1, -1);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, 1, 1);

	//FACE 5 TURQUOISE
	//On set la normale
	glNormal3f(0, -1, 0);
	//Sommets
	//glColor3d(0, 1, 1);
	glVertex3d(1, -1, 1);
	glVertex3d(-1, -1, 1);
	glVertex3d(-1, -1, -1);
	glVertex3d(1, -1, -1);

	//Materials
	materialDiffuse[1] = 0.0f;
	materialDiffuse[2] = _diffuse;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse); ///Diffuse
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = _ambient;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient); ///Ambient

	//FACE 3 BLUE
	//On set la normale
	glNormal3f(0, 0, 1);
	//glColor3d(0, 0, 1);
	glVertex3d(1, 1, 1);
	glVertex3d(-1, 1, 1);
	glVertex3d(-1, -1, 1);
	glVertex3d(1, -1, 1);

	//FACE 6 PURPLE
	//On set la normale
	glNormal3f(0, 0, -1);
	//Sommets
	//glColor3d(1, 0, 1);
	glVertex3d(1, 1, -1);
	glVertex3d(1, -1, -1);
	glVertex3d(-1, -1, -1);
	glVertex3d(-1, 1, -1);
	
	glEnd();

	//On recharge la matrice précédente
	glPopMatrix();

	//Sphère blanche transparente pour bien voir le shading et le reflet du soleil
	GLfloat whiteSpecularMaterialSphere[] = { 0.3, 0.3, 0.3,0.8 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecularMaterialSphere);
	glMaterialf(GL_FRONT, GL_SHININESS, mShininess);

	GLfloat materialDiffuseSphere[] = { 0.7, 0.7, 0.7, 0.8 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuseSphere);
	GLfloat materialAmbientSphere[] = { 0.2, 0.2, 0.2, 0.8 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbientSphere);	

	glutSolidSphere(2, 30, 30);*/

	//Au lieu de rendre notre cube dans sa sphère (mais on laisse le soleil)

	glUseProgram(g_program);

	GLuint elap = glGetUniformLocation(g_program, "elapsed");
	glUniform1f(elap, NYRenderer::_DeltaTimeCumul);

	GLuint amb = glGetUniformLocation(g_program, "ambientLevel");
	glUniform1f(amb, 0.4);

	GLuint invView = glGetUniformLocation(g_program, "invertView");
	glUniformMatrix4fv(invView, 1, true, g_renderer->_Camera->_InvertViewMatrix.Mat.t);

	NYFloatMatrix viewTemp = g_renderer->_Camera->_InvertViewMatrix.Mat.t;
	viewTemp.invert();
	GLuint view = glGetUniformLocation(g_program, "view");
	glUniformMatrix4fv(view, 1, true, viewTemp.Mat.t);

	GLuint camPos = glGetUniformLocation(g_program, "camPos");
	glUniform3f(camPos, g_renderer->_Camera->_Position.X, g_renderer->_Camera->_Position.Y, g_renderer->_Camera->_Position.Z);

	g_avatar->render();

	glPushMatrix();
	g_world->render_world_vbo();//render_world_old_school();/
	glPopMatrix();
}

void setLights(void)
{
	//On active l'illumination 
	glEnable(GL_LIGHTING);

	//On active la light 0
	glEnable(GL_LIGHT0);

	//SUN
	glPushMatrix();
	NYVert3Df posSun(100, 0, 0);
	NYColor sunColor(1, 1, 0, 1);
	posSun.rotate(NYVert3Df(0, 1, 0), NYRenderer::_DeltaTimeCumul);
	//glRotatef(NYRenderer::_DeltaTimeCumul * 100, 0, 1, 0);
	glTranslatef(posSun.X, posSun.Y, posSun.Z);

	GLuint lightPos = glGetUniformLocation(g_program, "lightPos");
	glUniform3f(lightPos, posSun.X, posSun.Y, posSun.Z);

	//Emissive
	GLfloat emissive[] = { 1.0, 1.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emissive);

	glutSolidCube(2);

	//On reset le material emissive pour la suite
	emissive[0] = 0.0f;
	emissive[1] = 0.0f;
	emissive[2] = 0.0f;
	glMaterialfv(GL_FRONT, GL_EMISSION, emissive);

	glPopMatrix();

	//On définit une lumière directionelle (un soleil)
	// w = 1 donc c'est une point light (w=0 -> directionelle, point à l'infini)
	//w = 0 donc elle est a l'infini
	float position[4] = {0, 0, 7, 0}; 
	glLightfv(GL_LIGHT0, GL_POSITION, position );

	float diffuse[4] = { 0.5f,0.5f,0.5f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse );

	float specular[4] = {0.5f,0.5f,0.5f};
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular );

	float ambient[4] = {0.3f,0.3f,0.3f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient );
}

/*bool getSunDirection(NYVert3Df & sun, float mnLever, float mnCoucher)
{
	bool nuit = false;

	SYSTEMTIME t;
	GetLocalTime(&t);

	//On borne le tweak time à une journée (cyclique)
	while (g_tweak_time > 24 * 60)
		g_tweak_time -= 24 * 60;

	//Temps écoulé depuis le début de la journée
	float fTime = (float)(t.wHour * 60 + t.wMinute);
	fTime += g_tweak_time;
	while (fTime > 24 * 60)
		fTime -= 24 * 60;

	//Si c'est la nuit
	if (fTime < mnLever || fTime > mnCoucher)
	{
		nuit = true;
		if (fTime < mnLever)
			fTime += 24 * 60;
		fTime -= mnCoucher;
		fTime /= (mnLever + 24 * 60 - mnCoucher);
		fTime *= M_PI;
	}
	else
	{
		//c'est le jour
		nuit = false;
		fTime -= mnLever;
		fTime /= (mnCoucher - mnLever);
		fTime *= M_PI;
	}

	//Position en fonction de la progression dans la journée
	sun.X = cos(fTime);
	sun.Y = 0.2f;
	sun.Z = sin(fTime);
	sun.normalize();

	return nuit;
}*/

/*void setLightsBasedOnDayTime(void)
{
	//On active la light 0
	glEnable(GL_LIGHT0);

	//On recup la direciton du soleil
	bool nuit = getSunDirection(g_sun_dir, g_mn_lever, g_mn_coucher);

	//On définit une lumière directionelle (un soleil)
	float position[4] = { g_sun_dir.X,g_sun_dir.Y,g_sun_dir.Z,0 }; ///w = 0 donc c'est une position a l'infini
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	//Pendant la journée
	if (!nuit)
	{
		//On definit la couleur
		NYColor sunColor(1, 1, 0.8, 1);
		NYColor skyColor(0, 181.f / 255.f, 221.f / 255.f, 1);
		NYColor downColor(0.9, 0.5, 0.1, 1);
		sunColor = sunColor.interpolate(downColor, (abs(g_sun_dir.X)));
		skyColor = skyColor.interpolate(downColor, (abs(g_sun_dir.X)));

		g_renderer->setBackgroundColor(skyColor);

		float color[4] = { sunColor.R,sunColor.V,sunColor.B,1 };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
		float color2[4] = { sunColor.R,sunColor.V,sunColor.B,1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, color2);
		g_sun_color = sunColor;
	}
	else
	{
		//La nuit : lune blanche et ciel noir
		NYColor sunColor(1, 1, 1, 1);
		NYColor skyColor(0, 0, 0, 1);
		g_renderer->setBackgroundColor(skyColor);

		float color[4] = { sunColor.R / 3.f,sunColor.V / 3.f,sunColor.B / 3.f,1 };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
		float color2[4] = { sunColor.R / 7.f,sunColor.V / 7.f,sunColor.B / 7.f,1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, color2);
		g_sun_color = sunColor;
	}
}*/

void resizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	g_renderer->resize(width,height);
}

//////////////////////////////////////////////////////////////////////////
// GESTION CLAVIER SOURIS
//////////////////////////////////////////////////////////////////////////

void specialDownFunction(int key, int p1, int p2)
{
	//On change de mode de camera
	if(key == GLUT_KEY_LEFT)
	{
	}

}

void specialUpFunction(int key, int p1, int p2)
{

}

void keyboardDownFunction(unsigned char key, int p1, int p2)
{
	if(key == VK_ESCAPE)
	{
		glutDestroyWindow(g_main_window_id);		
		exit(0);
	}

	if(key == 'f')
	{
		if(!g_fullscreen){
			glutFullScreen();
			g_fullscreen = true;
		} else if(g_fullscreen){
			glutLeaveGameMode();
			glutLeaveFullScreen();
			glutReshapeWindow(g_renderer->_ScreenWidth, g_renderer->_ScreenWidth);
			glutPositionWindow(0,0);
			g_fullscreen = false;
		}
	}	

	switch (key)
	{
		case 'z':
			g_avatar->avance = true;
			//g_renderer->_Camera->move(NYVert3Df(-1, -1, 0));
			break;
		case 'q':
			g_avatar->gauche = true;
			//g_renderer->_Camera->move(NYVert3Df(1, -1, 0));
			break;
		case 's':
			g_avatar->recule = true;
			//g_renderer->_Camera->move(NYVert3Df(1, 1, 0));
			break;
		case 'd':
			g_avatar->droite = true;
			//g_renderer->_Camera->move(NYVert3Df(-1, 1, 0));
			break;
		case VK_SPACE:
			g_avatar->Jump = true;
			break;
		/*case 'g':
			g_fast_time = !g_fast_time;
			break;*/
	}
}

void keyboardUpFunction(unsigned char key, int p1, int p2)
{
	switch (key)
	{
		case 'z':
			g_avatar->avance = false;
			//g_renderer->_Camera->move(NYVert3Df(-1, -1, 0));
			break;
		case 'q':
			g_avatar->gauche = false;
			//g_renderer->_Camera->move(NYVert3Df(1, -1, 0));
			break;
		case 's':
			g_avatar->recule = false;
			//g_renderer->_Camera->move(NYVert3Df(1, 1, 0));
			break;
		case 'd':
			g_avatar->droite = false;
			//g_renderer->_Camera->move(NYVert3Df(-1, 1, 0));
			break;
		case VK_SPACE:
			g_avatar->Jump = false;
			break;
	}
}

void mouseWheelFunction(int wheel, int dir, int x, int y)
{
	//g_renderer->_Camera->move(NYVert3Df(-1 * dir, -1 * dir, 0)); //Soufian

	g_renderer->_Camera->move(NYVert3Df(0, 0, dir*50)); //SOLUTION
}

void mouseFunction(int button, int state, int x, int y)
{
	//Gestion de la roulette de la souris
	if((button & 0x07) == 3 && state)
		mouseWheelFunction(button,1,x,y);
	if((button & 0x07) == 4 && state)
		mouseWheelFunction(button,-1,x,y);

	//GUI
	g_mouse_btn_gui_state = 0;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		g_mouse_btn_gui_state |= GUI_MLBUTTON;
	
	bool mouseTraite = false;
	mouseTraite = g_screen_manager->mouseCallback(x,y,g_mouse_btn_gui_state,0,0);
}

void mouseMoveFunction(int x, int y, bool pressed)
{
	bool mouseTraite = false;

	mouseTraite = g_screen_manager->mouseCallback(x,y,g_mouse_btn_gui_state,0,0);
	if(pressed && mouseTraite)
	{
		//Mise a jour des variables liées aux sliders
		//g_renderer->_Camera->rotate(10f); //SOUFIAN
	}

	//SOUFIAN
	/*int _lastX = x;
	int _lastY = y;

	int _x = _lastX - x;
	int _y = _lastY - y;
	//int deltaX = _lastX - x;

	g_renderer->_Camera->rotate(x);

	int _lastX = x;
	g_renderer->_Camera->setLookAt(NYVert3Df(-x, -y, 0));*/

	//SOLUTION
	static int lastx = -1;
	static int lasty = -1;

	if (!pressed)
	{
		lastx = x;
		lasty = y;
	}
	else
	{
		if (lastx == -1 && lasty == -1)
		{
			lastx = x;
			lasty = y;
		}

		int dx = x - lastx;
		int dy = y - lasty;

		lastx = x;
		lasty = y;

		if (GetKeyState(VK_LCONTROL) & 0x80)
		{
			NYVert3Df strafe = g_renderer->_Camera->_NormVec;
			strafe.Z = 0;
			strafe.normalize();
			strafe *= (float)-dx / 5.0f;

			NYVert3Df avance = g_renderer->_Camera->_Direction;
			avance.Z = 0;
			avance.normalize();
			avance *= (float)dy / 50.0f;

			g_renderer->_Camera->move(avance + strafe);
		}
		else
		{
			g_renderer->_Camera->rotate((float)-dx / 300.0f);
			g_renderer->_Camera->rotateUp((float)-dy / 300.0f);
		}
	}
}

void mouseMoveActiveFunction(int x, int y)
{
	mouseMoveFunction(x,y,true);
}
void mouseMovePassiveFunction(int x, int y)
{
	mouseMoveFunction(x,y,false);
}


void clickBtnParams (GUIBouton * bouton)
{
	g_screen_manager->setActiveScreen(g_screen_params);
}

void clickBtnCloseParam (GUIBouton * bouton)
{
	g_screen_manager->setActiveScreen(g_screen_jeu);
}

/**
  * POINT D'ENTREE PRINCIPAL
  **/
int main(int argc, char* argv[])
{ 
	LogConsole::createInstance();

	int screen_width = 800;
	int screen_height = 600;

	glutInit(&argc, argv); 
	glutInitContextVersion(3,0);
	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
		);

	glutInitWindowSize(screen_width,screen_height);
	glutInitWindowPosition (0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE );

	glEnable(GL_MULTISAMPLE);

	Log::log(Log::ENGINE_INFO, (toString(argc) + " arguments en ligne de commande.").c_str());	
	bool gameMode = true;
	for(int i=0;i<argc;i++)
	{
		if(argv[i][0] == 'w')
		{
			Log::log(Log::ENGINE_INFO,"Arg w mode fenetre.\n");
			gameMode = false;
		}
	}

	if(gameMode)
	{
		int width = glutGet(GLUT_SCREEN_WIDTH);
		int height = glutGet(GLUT_SCREEN_HEIGHT);
		
		char gameModeStr[200];
		sprintf(gameModeStr,"%dx%d:32@60",width,height);
		glutGameModeString(gameModeStr);
		g_main_window_id = glutEnterGameMode();
	}
	else
	{
		g_main_window_id = glutCreateWindow("MyNecraft");
		glutReshapeWindow(screen_width,screen_height);
	}

	if(g_main_window_id < 1) 
	{
		Log::log(Log::ENGINE_ERROR,"Erreur creation de la fenetre.");
		exit(EXIT_FAILURE);
	}
	
	GLenum glewInitResult = glewInit();

	if (glewInitResult != GLEW_OK)
	{
		Log::log(Log::ENGINE_ERROR,("Erreur init glew " + std::string((char*)glewGetErrorString(glewInitResult))).c_str());
		_cprintf("ERROR : %s",glewGetErrorString(glewInitResult));
		exit(EXIT_FAILURE);
	}

	//Affichage des capacités du système
	Log::log(Log::ENGINE_INFO,("OpenGL Version : " + std::string((char*)glGetString(GL_VERSION))).c_str());

	glutDisplayFunc(update);
	glutReshapeFunc(resizeFunction);
	glutKeyboardFunc(keyboardDownFunction);
	glutKeyboardUpFunc(keyboardUpFunction);
	glutSpecialFunc(specialDownFunction);
	glutSpecialUpFunc(specialUpFunction);
	glutMouseFunc(mouseFunction);
	glutMotionFunc(mouseMoveActiveFunction);
	glutPassiveMotionFunc(mouseMovePassiveFunction);
	glutIgnoreKeyRepeat(1);

	//Initialisation du renderer
	g_renderer = NYRenderer::getInstance();
	g_renderer->setRenderObjectFun(renderObjects);
	g_renderer->setRender2DFun(render2d);
	g_renderer->setLightsFun(setLights);

	/*NYColor dayColor(255.f, 1.f, 204.f / 255.f, 1);
	NYColor nightColor(0.f, 0.f, 51.f / 255.f, 1);
	dayColor.interpolate(nightColor, NYRenderer::_DeltaTimeCumul);*/

	g_renderer->setBackgroundColor(NYColor(0.8f, 0.8f, 0.8f, 1.f));

	g_renderer->initialise();

	//On applique la config du renderer
	glViewport(0, 0, g_renderer->_ScreenWidth, g_renderer->_ScreenHeight);
	g_renderer->resize(g_renderer->_ScreenWidth,g_renderer->_ScreenHeight);
	
	//Ecran de jeu
	uint16 x = 10;
	uint16 y = 10;
	g_screen_jeu = new GUIScreen(); 

	g_screen_manager = new GUIScreenManager();
		
	//Bouton pour afficher les params
	BtnParams = new GUIBouton();
	BtnParams->Titre = std::string("Params");
	BtnParams->X = x;
	BtnParams->setOnClick(clickBtnParams);
	g_screen_jeu->addElement(BtnParams);

	y += BtnParams->Height + 1;

	LabelFps = new GUILabel();
	LabelFps->Text = "FPS";
	LabelFps->X = x;
	LabelFps->Y = y;
	LabelFps->Visible = true;
	g_screen_jeu->addElement(LabelFps);

	//Ecran de parametrage
	x = 10;
	y = 10;
	g_screen_params = new GUIScreen();

	GUIBouton * btnClose = new GUIBouton();
	btnClose->Titre = std::string("Close");
	btnClose->X = x;
	btnClose->setOnClick(clickBtnCloseParam);
	g_screen_params->addElement(btnClose);

	y += btnClose->Height + 1;
	y+=10;
	x+=10;

	GUILabel * label = new GUILabel();
	label->X = x;
	label->Y = y;
	label->Text = "Param :";
	g_screen_params->addElement(label);

	y += label->Height + 1;

	g_slider = new GUISlider();
	g_slider->setPos(x,y);
	g_slider->setMaxMin(1,0);
	g_slider->Visible = true;
	g_screen_params->addElement(g_slider);

	y += g_slider->Height + 1;
	y+=10;

	//Ecran a rendre
	g_screen_manager->setActiveScreen(g_screen_jeu);
	
	//Init Camera
	g_renderer->_Camera->setPosition(NYVert3Df(10,10,10));
	g_renderer->_Camera->setLookAt(NYVert3Df(0,0,0));
	
	//A la fin du main, on genere un monde
	g_world = new NYWorld();	
	g_world->_FacteurGeneration = 5;
	g_world->init_world();
	g_world->add_world_to_vbo();
	g_avatar = new NYAvatar(g_renderer->_Camera, g_world);

	//g_renderer->_Camera->setPosition(g_avatar->Position);
	//Dans le main, à l'initialisation du moteur de rendu

	//Active le post process (chargera le shader de post process "postprocess/pshader.glsl")
	g_renderer->initialise(true);

	//Creation d'un programme de shader, avec vertex et fragment shaders
	g_program = g_renderer->createProgram("shaders/psbase.glsl", "shaders/vsbase.glsl");

	//Fin init moteur

	//Init application



	//Init Timer
	g_timer = new NYTimer();
	
	//On start
	g_timer->start();

	glutMainLoop(); 

	return 0;
}


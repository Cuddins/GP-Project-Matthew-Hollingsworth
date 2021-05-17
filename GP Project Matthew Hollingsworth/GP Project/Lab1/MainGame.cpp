#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;
Transform transform2;
Transform transform3;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Shader celShader();
	Shader geoShader();
	Shader eMapping();
	//Audio* audioDevice();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay();
	
	meshMonkey.loadModel("..\\res\\monkey3.obj");
	meshSphere.loadModel("..\\res\\sphereSmooth.obj");
	meshTorus.loadModel("..\\res\\torus.obj");
	celShader.init("..\\res\\shaderCellExtension.vert", "..\\res\\shaderCellExtension.frag"); //new shader
	eMapping.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");

	geoShader.initGeo();

	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;

	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};

	skybox.init(faces);
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


void MainGame::linkCel()
{
	celShader.setVec3("light", glm::vec3(0.0f, 1.0f, -2.0f));
	celShader.setVec3("lightColour", glm::vec3(1.0f, 1.0f, 1.0f));
}

void MainGame::linkGeo()
{
	geoShader.setFloat("time", counter);
}


void MainGame::linkEmapping()
{
	eMapping.setMat4("projection", myCamera.getProjection());
	eMapping.setMat4("view", myCamera.getView());
	eMapping.setMat4("model", transform2.GetModel());
	eMapping.setVec3("cameraPos", myCamera.getPos());
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.8f, 0.8f, 0.8f, 1.0f); //sets our background colour

	//load textures
	Texture texture("..\\res\\bricks.jpg"); //load texture
	Texture texture1("..\\res\\water.jpg"); //load texture
	

	//update transfroms 
	transform.SetPos(glm::vec3(-2.5, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	transform2.SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform2.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform2.SetScale(glm::vec3(0.6, 0.6, 0.6));

	transform3.SetPos(glm::vec3(2.5, 0.0, 0.0));
	transform3.SetRot(glm::vec3(-20.0, 0.0, 0.0));
	transform3.SetScale(glm::vec3(0.6, 0.6, 0.6));

	geoShader.Bind();
	linkGeo();
	geoShader.Update(transform, myCamera);
	texture1.Bind(0);
	meshMonkey.draw();

	eMapping.Bind();
	linkEmapping();
	eMapping.Update(transform2, myCamera);
	meshSphere.draw();

	celShader.Bind();
	linkCel();
	celShader.Update(transform3, myCamera);
	texture.Bind(0);
	meshTorus.draw();

	counter = counter + 0.02f;

	skybox.draw(&myCamera);	
	

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();


	_gameDisplay.swapBuffer();	
	

} 
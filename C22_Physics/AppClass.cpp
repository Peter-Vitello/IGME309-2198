#include "AppClass.h"
#include "MySolver.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		vector3(35.0f, 10.0f, 80.0f), //Position
		vector3(0.0f, 0.0f, 0.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	// steve that will move to the zombie 
	m_pEntityMngr->AddEntity("Minecraft\\Steve.obj", "Steve");
	
	m_pEntityMngr->UsePhysicsSolver();
	m_pEntityMngr->SetPosition(vector3(22.0f, 0.0f, 55.0f), 1);
	Steve = m_pEntityMngr->GetEntity(0)->GetRigidBody();
	
	
	// zombie what we are trying to find 
	m_pEntityMngr->AddEntity("Minecraft\\zombie.obj", "Zombie");
	Zombie = m_pEntityMngr->GetEntity(1)->GetRigidBody();

	
	for (int i = 0; i < 350; i++)
	{
		m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "Cube_" + std::to_string(i));
		vector3 v3Position = vector3(glm::sphericalRand(90.0f));
		v3Position.y = 0.0f;
		matrix4 m4Position = glm::translate(v3Position);
		m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(2.0f)));
		m_pEntityMngr->UsePhysicsSolver();
		m_pEntityMngr->SetMass(14);

		//m_pEntityMngr->SetMass(i+1);
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();
	
	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix

	//Get a timer
	static float fTimer = 0; //store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();
		
	//get the percentace
	float fTimeBetweenStops = 2.0;//in seconds
	//map the value to be between 0.0 and 1.0
	float fPercentage = MapValue(fTimer, 0.0f, fTimeBetweenStops, 0.0f, 1.0f);

	vector3 v3Start = Steve->GetCenterGlobal(); //start point
	vector3 v3End = Zombie->GetCenterGlobal(); //end point

	//calculate the current position
	vector3 v3CurrentPos = glm::lerp(v3Start, v3End, fPercentage);
	matrix4 m4Model = glm::translate(IDENTITY_M4, v3CurrentPos);;

	// should move steve to the zombie but it is not working 
	//Steve->SetModelMatrix(glm::translate(Steve->GetModelMatrix(), Zombie->GetCenterGlobal()));
	Steve->SetModelMatrix(m4Model);


	// got an error this methoid was gonna draw from steve to the zombie using the shortest distance 
	//ySolver::drawAstar(Steve->GetCenterLocal, Zombie->GetCenterLocal, C_BLUE_CORNFLOWER);
	
	if (Steve->IsColliding(Zombie))
	{
		return;
	}

	//m_pMeshMngr->Render(m4Projection, m4View, m4Model);
	m_pMeshMngr->Render();

	//Set the model matrix for the main object
	//m_pEntityMngr->SetModelMatrix(m_m4Steve, "Steve");

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
	//m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();


	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui,
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release MyEntityManager
	MyEntityManager::ReleaseInstance();

	//release GUI
	ShutdownGUI();
}
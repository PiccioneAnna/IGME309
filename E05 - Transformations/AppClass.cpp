#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Anna Piccione - ajp7549@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Allocate the memory for the Meshes
	m_uMeshCount = 46;
	for (uint i = 0; i < m_uMeshCount; ++i)
	{
		MyMesh* pMesh = new MyMesh();
		m_pMeshList.push_back(pMesh);
		m_pMeshList[i]->GenerateCube(1.0f, C_BLACK);
	}
		
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	// Set a timer for movement
	static float fTimer = 0;	// storing the new timer
	static uint uClock = m_pSystem->GenClock(); // setting a new clock for that timer
	fTimer += static_cast<float>(m_pSystem->GetDeltaTime(uClock)); // getting delta time

	// Draw meshes
	uint i = 0;
	static float fHorizontal = -10.0f;
	static vector3 v3Position(fHorizontal, 0.0f, 0.0f);

	v3Position.x = fHorizontal + fTimer;
	matrix4 m4Position = glm::translate(vector3(-5.0f, -3.0f, -15.0f)) * glm::translate(v3Position);

	// Mesh Board
	std::vector<std::vector<float>> grid{
	std::vector<float>{ 3.0f, 4.0f, 6.0f, 7.0f }, // First Row
	std::vector<float>{ 0.0f, 2.0f, 8.0f, 10.0f }, 
	std::vector<float>{ 0.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 10.0f },
	std::vector<float>{ 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f },
	std::vector<float>{ 1.0f, 2.0f, 4.0f, 5.0f, 6.0f, 8.0f, 9.0f},
	std::vector<float>{ 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f},
	std::vector<float>{ 3.0f, 7.0f},
	std::vector<float>{ 2.0f, 8.0f}}; // Eighth Row


	// Create each of the rows based on the grid
	for (float y = 0.0f; y < grid.size(); ++y)
	{
		for each (float x in grid[y])
		{
			m_pMeshList[i]->Render(m4Projection, m4View, glm::translate(m4Position, vector3(x, y, 0.0f))); ++i;
		}
	}

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release meshes
	std::vector<MyMesh*> m_pMeshList;
	uint uSize = m_pMeshList.size();
	for (uint i = 0; i < uSize; ++i)
	{
		if (m_pMeshList[i] != nullptr)
		{
			delete m_pMeshList[i];
			m_pMeshList[i] = nullptr;
		}
	}

	//release GUI
	ShutdownGUI();
}
#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	std::vector<vector3> base_vertices;

	// Cone tip
	vector3 coneTip(0.0f, 0.0f, a_fHeight);

	// Middle of base
	vector3 baseCenter(0.0f, 0.0f, 0.0f);

	// Generating the points for the base of the cone
	for (int i = 0; i < a_nSubdivisions; i++)
	{ 
		float angle = 2 * PI * ((float)i / (float)a_nSubdivisions);
		float s = sin(angle) * a_fRadius;
		float c = cos(angle) * a_fRadius;
		base_vertices.push_back(vector3(c, s, 0.0f));
	}

	// Generating the faces leading up to the cone tip
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i == a_nSubdivisions - 1) {
			AddTri(base_vertices[i], base_vertices[0], coneTip);
		}
		else {
			AddTri(base_vertices[i], base_vertices[i + 1], coneTip);
		}
	}

	// Reversing the base vertices for consistent direction of faces
	std:reverse(base_vertices.begin(), base_vertices.end());

	// Generating the faces based off of the points above for base
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i == a_nSubdivisions - 1) {
			AddTri(base_vertices[i], base_vertices[0], baseCenter);
		}
		else {
			AddTri(base_vertices[i], base_vertices[i + 1], baseCenter);
		}
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	std::vector<vector3> base_vertices;
	std::vector<vector3> top_vertices;

	// Middle of centers
	vector3 baseCenter(0, 0, 0);
	vector3 topCenter(0, 0, a_fHeight);

	// Generating the points for the base of the cylinder
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float angle = 2 * PI * ((float)i / (float)a_nSubdivisions);
		float s = sin(angle) * a_fRadius;
		float c = cos(angle) * a_fRadius;
		base_vertices.push_back(vector3(c, s, 0.0f));
	}

	// Generating the points for the top of the cylinder
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float angle = 2 * PI * ((float)i / (float)a_nSubdivisions);
		float s = sin(angle) * a_fRadius;
		float c = cos(angle) * a_fRadius;
		top_vertices.push_back(vector3(c, s, a_fHeight));
	}

	// Generating the faces based off of the points above for top
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i == a_nSubdivisions - 1) {
			AddTri(top_vertices[i], top_vertices[0], topCenter);
		}
		else {
			AddTri(top_vertices[i], top_vertices[i + 1], topCenter);
		}
	}

	// Generating the faces based off of the points above for top
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i == a_nSubdivisions - 1) {
			AddQuad(base_vertices[i], base_vertices[0], top_vertices[i], top_vertices[0]);
		}
		else {
			AddQuad(base_vertices[i], base_vertices[i+1], top_vertices[i], top_vertices[i+1]);
		}
	}

	// Reversing the base vertices for consistent direction of faces
	std::reverse(base_vertices.begin(), base_vertices.end());

	// Generating the faces based off of the points above for base
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i == a_nSubdivisions - 1) {
			AddTri(base_vertices[i], base_vertices[0], baseCenter);
		}
		else {
			AddTri(base_vertices[i], base_vertices[i + 1], baseCenter);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	std::vector<vector3> base_vertices_outer;
	std::vector<vector3> base_vertices_inner;
	std::vector<vector3> top_vertices_outer;
	std::vector<vector3> top_vertices_inner;

	// Generating the points for the outer base of the tube
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float angle = 2 * PI * ((float)i / (float)a_nSubdivisions);
		float s = sin(angle) * a_fOuterRadius;
		float c = cos(angle) * a_fOuterRadius;
		base_vertices_outer.push_back(vector3(c, s, 0.0f));
	}

	// Generating the points for the inner base of the tube
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float angle = 2 * PI * ((float)i / (float)a_nSubdivisions);
		float s = sin(angle) * a_fInnerRadius;
		float c = cos(angle) * a_fInnerRadius;
		base_vertices_inner.push_back(vector3(c, s, 0.0f));
	}

	// Generating the points for the outer top of the tube
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float angle = 2 * PI * ((float)i / (float)a_nSubdivisions);
		float s = sin(angle) * a_fOuterRadius;
		float c = cos(angle) * a_fOuterRadius;
		top_vertices_outer.push_back(vector3(c, s, a_fHeight));
	}

	// Generating the points for the inner top of the tube
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float angle = 2 * PI * ((float)i / (float)a_nSubdivisions);
		float s = sin(angle) * a_fInnerRadius;
		float c = cos(angle) * a_fInnerRadius;
		top_vertices_inner.push_back(vector3(c, s, a_fHeight));
	}

	// Generating the outer faces connecting top and bottom
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i == a_nSubdivisions - 1) {
			AddQuad(base_vertices_outer[i], base_vertices_outer[0], top_vertices_outer[i], top_vertices_outer[0]);
		}
		else {
			AddQuad(base_vertices_outer[i], base_vertices_outer[i + 1], top_vertices_outer[i], top_vertices_outer[i + 1]);
		}
	}

	// Reversing the base vertices for consistent direction of faces
	std::reverse(base_vertices_outer.begin(), base_vertices_outer.end());
	std::reverse(base_vertices_inner.begin(), base_vertices_inner.end());

	// Generating the faces based off of the points above for base
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i == a_nSubdivisions - 1) {
			AddQuad(base_vertices_outer[i], base_vertices_outer[0], base_vertices_inner[i], base_vertices_inner[0]);
		}
		else {
			AddQuad(base_vertices_outer[i], base_vertices_outer[i+1], base_vertices_inner[i], base_vertices_inner[i+1]);
		}
	}

	// Generating the faces based off of the points above for top
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i == a_nSubdivisions - 1) {
			AddQuad(top_vertices_outer[i], top_vertices_outer[0], top_vertices_inner[i], top_vertices_inner[0]);
		}
		else {
			AddQuad(top_vertices_outer[i], top_vertices_outer[i + 1], top_vertices_inner[i], top_vertices_inner[i + 1]);
		}
	}

	// Reversing the top vertices for consistent direction of faces
	std::reverse(top_vertices_outer.begin(), top_vertices_outer.end());
	std::reverse(top_vertices_inner.begin(), top_vertices_inner.end());

	// Generating the inner faces connecting top and bottom
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		if (i == a_nSubdivisions - 1) {
			AddQuad(base_vertices_inner[i], base_vertices_inner[0], top_vertices_inner[i], top_vertices_inner[0]);
		}
		else {
			AddQuad(base_vertices_inner[i], base_vertices_inner[i + 1], top_vertices_inner[i], top_vertices_inner[i + 1]);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	std::vector<vector3> vertices;
	float tubeRadius = ((a_fOuterRadius - a_fInnerRadius) / 2);

	// Generating vertices
	for (size_t i = 0; i < a_nSubdivisionsA; i++) {
		for (size_t j = 0; j < a_nSubdivisionsB; j++) {
			auto u = (float)j / a_nSubdivisionsA * PI * 2.0;
			auto v = (float)i / a_nSubdivisionsB * PI * 2.0;
			auto x = (a_fOuterRadius + tubeRadius * cos(v)) * cos(u);
			auto y = (a_fOuterRadius + tubeRadius * cos(v)) * sin(u);
			auto z = tubeRadius * sin(v);
			vertices.push_back(vector3(x, y, z));
		}
	}

	// Generating quad faces
	for (size_t i = 0; i < a_nSubdivisionsA; i++) {
		auto i_next = (i + 1) % a_nSubdivisionsA;
		for (size_t j = 0; j < a_nSubdivisionsB; j++) {
			auto j_next = (j + 1) % a_nSubdivisionsB;
			auto i0 = i * a_nSubdivisionsB + j;
			auto i1 = i * a_nSubdivisionsB + j_next;
			auto i2 = i_next * a_nSubdivisionsB + j;
			auto i3 = i_next * a_nSubdivisionsB + j_next;
			AddQuad(vertices[i0], vertices[i1], vertices[i2], vertices[i3]);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	// Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// North and south vectors - top and bottom of sphere
	vector3 vN(0, a_fRadius, 0);
	vector3 vS(0, -a_fRadius, 0);

	std::vector<vector3> vertices;

	// Starting off vertices list with the north point of sphere
	vertices.push_back(vN);

	// Generating vertices based on subdivisions
	for (size_t i = 0; i < a_nSubdivisions - 1; i++)
	{
		auto phi = PI * float(i + 1) / float(a_nSubdivisions);
		for (int j = 0; j < a_nSubdivisions; j++)
		{
			auto theta = 2.0 * PI * float(j) / float(a_nSubdivisions);
			auto x = sin(phi) * cos(theta) * a_fRadius;
			auto y = cos(phi) * a_fRadius;
			auto z = sin(phi) * sin(theta) * a_fRadius;
			vertices.push_back(vector3(x, y, z));
		}
	}

	// Finishing off vertices list with the south point of sphere
	vertices.push_back(vS);

	// Generating top & bottom triangles
	for (size_t i = 0; i < a_nSubdivisions; i++)
	{
		auto j = i + 1;
		auto k = (i + 1) % a_nSubdivisions + 1;
		AddTri(vN, vertices[k], vertices[j]);
		j = i + a_nSubdivisions * (a_nSubdivisions - 2) + 1;
		k = (i + 1) % a_nSubdivisions + a_nSubdivisions * (a_nSubdivisions - 2) + 1;
		AddTri(vS, vertices[j], vertices[k]);
	}

	// Generating quads to finish sphere off
	for (size_t i = 0; i < a_nSubdivisions - 2; i++)
	{
		auto j0 = i * a_nSubdivisions + 1;
		auto j1 = (i + 1) * a_nSubdivisions + 1;
		for (size_t k = 0; k < a_nSubdivisions; k++)
		{
			auto l0 = j0 + k;
			auto l1 = j0 + (k + 1) % a_nSubdivisions;
			auto l2 = j1 + k;
			auto l3 = j1 + (k + 1) % a_nSubdivisions;
			AddQuad(vertices[l0], vertices[l1],  vertices[l2], vertices[l3]);
		}
	}

	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
#include <vector>
#include <cstdlib>
#include <ctime>

#include "shader.h"
#define SCR_WIDTH 800
#define SCR_HEIGHT 600


GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLuint LoadShaders(const char *, const char *);
void Keyboard(unsigned char, int, int);
GLvoid TimerFunction(int);
bool loadOBJ(const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec3 > & out_uvs, std::vector < glm::vec3 > & out_normals);

bool timerCheck = false;
bool culling = true;
bool wire = true;
bool angle_B = true;
bool position = true;

float angle = 0;
int triangle_count = 36;


bool loadOBJ(
	const char * path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals
);

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec3 > temp_uvs;
std::vector< glm::vec3 > temp_normals;

struct vertex_data {
	float x;
	float y;
	float z;
};

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 700);
	glutCreateWindow("Floating Window");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;


	//좌표축
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(200, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}


GLvoid drawScene() {
	// draw	
	// 생성하고 컴파일하기

	Shader ourShader("vertexshader.glvs", "fragmentshader.glfs"); // you can name your shader files however you like

	ourShader.use();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 *(float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-400, (float)400);

	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 50);
	glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	GLuint VertexArrayID;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec3 > uvs;
	std::vector< glm::vec3 > normals; // 지금은 안쓸거에요. 
	bool res = loadOBJ("log.obj", vertices, uvs, normals);


	// 이것이 우리의 버텍스 버퍼를 가리킵니다.
	GLuint vertexbuffer;
	// 버퍼를 하나 생성합니다. vertexbuffer 에 결과 식별자를 넣습니다
	glGenBuffers(1, &vertexbuffer);
	// 아래의 명령어들은 우리의 "vertexbuffer" 버퍼에 대해서 다룰겁니다
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// 우리의 버텍스들을 OpenGL로 넘겨줍니다
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// 버퍼의 첫번째 속성값(attribute) : 버텍스들
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
		3,                  // 크기(size)
		GL_FLOAT,           // 타입(type)
		GL_FALSE,           // 정규화(normalized)
		0,                  // 다음 요소 까지 간격(stride)
		(void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
	);


	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec3), &uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);


	glm::mat4 rotMatrix = glm::mat4(1.0f); // 단위행렬로초기화 
	glm::mat4 transMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 myTransformeVector = glm::mat4(1.0f);

	rotMatrix = glm::rotate(rotMatrix, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(angle + -30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.05, 0.05, 0.05));

	myTransformeVector = transMatrix * rotMatrix * scaleMatrix;

	unsigned int transformLocation = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(myTransformeVector));

	unsigned int projectionLocation = glGetUniformLocation(ourShader.ID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	unsigned int viewLocation = glGetUniformLocation(ourShader.ID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vertexIndices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	glutSwapBuffers();
}


GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}


void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'h':
	case 'H':
		if (culling == true)
			culling = false;
		else
			culling = true;
		break;
	case 'w':
	case 'W':
		if (wire == true)
			wire = false;
		else
			wire = true;
		break;
	case 'y':
	case 'Y':
		timerCheck = true;
		glutTimerFunc(200, TimerFunction, 1);
		break;
	case 'p':
	case 'P':
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (timerCheck == true) {
		angle += 10;
		glutTimerFunc(200, TimerFunction, 1);
	}

	glutPostRedisplay();
}


bool loadOBJ(const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec3 > & out_uvs, 
	std::vector < glm::vec3 > & out_normals)
{
	FILE * file;

	fopen_s(&file, path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec3 uv;
			fscanf_s(file, "%f %f %f\n", &uv.x, &uv.y, &uv.z);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	// For each vertex of each triangle  (각 삼각형의 각 꼭지점을 순회합니다. ) 
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec3 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}
}
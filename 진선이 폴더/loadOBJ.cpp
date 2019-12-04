#include "shader.h"
#include "loadObj.h"


void loadOBJ::load(glm::mat4 projection, glm::mat4 view)
{
	GLuint VertexArrayID;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	//madeOBJ(objPath, vertices, uvs, normals);

	// �̰��� �츮�� ���ؽ� ���۸� ����ŵ�ϴ�.
	// ���۸� �ϳ� �����մϴ�. vertexbuffer �� ��� �ĺ��ڸ� �ֽ��ϴ�
	glGenBuffers(1, &vertexbuffer);
	// �Ʒ��� ��ɾ���� �츮�� "vertexbuffer" ���ۿ� ���ؼ� �ٷ�̴ϴ�
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// �츮�� ���ؽ����� OpenGL�� �Ѱ��ݴϴ�
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// ������ ù��° �Ӽ���(attribute) : ���ؽ���
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // 0��° �Ӽ�(attribute). 0 �� �� Ư���� ������ ������, ���̴��� ���̾ƿ�(layout)�� �ݵ�� ���߾�� �մϴ�.
		3,                  // ũ��(size)
		GL_FLOAT,           // Ÿ��(type)
		GL_FALSE,           // ����ȭ(normalized)
		0,                  // ���� ��� ���� ����(stride)
		(void*)0            // �迭 ������ ������(offset; �ű�� ��)
	);

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

	glGenBuffers(1, &lightbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, lightbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, lightbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	unsigned int projectionLocation = glGetUniformLocation(ourShaderID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	unsigned int viewLocation = glGetUniformLocation(ourShaderID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}


void loadOBJ::setTransform(glm::mat4 Transforme)
{

	int lightPosLocation = glGetUniformLocation(ourShaderID, "lightPos"); //--- lightPos ������ 
	glUniform3f (lightPosLocation, 0, 800, 2000);

	int lightColorLocation = glGetUniformLocation(ourShaderID, "lightColor"); //--- lightColor������ 
	glUniform3f (lightColorLocation, 1.0, 1.0, 0.9);

	int lightViewLocation = glGetUniformLocation(ourShaderID, "viewPos");
	glUniform3f(lightViewLocation, 0.0, 45.0, 50);

	unsigned int transformLocation = glGetUniformLocation(ourShaderID, "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(Transforme));
}


void loadOBJ::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vertexIndices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &lightbuffer);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
}
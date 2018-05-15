#include <stdio.h>
#include <GL/glew.h>        // GLEW��չ��,ע��glew.h����Ҫд��ǰ��
#include <GL/freeglut.h>  // freeGLUTͼ�ο�
#include "ogldev_math_3d.h" // ����OpenGL��3d��ѧ��,������Ҫ�õ��˶���������ݽṹ�����汨��Ĵ��������ע�͵�

GLuint VBO;		//ȫ��GLuint���ñ��������������㻺��������

//��Ⱦ�ص�����
static void RenderCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);	// �����ɫ����

	glEnableVertexAttribArray(0);	// ������������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		//��GL_ARRAY_BUFFER������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	// ���߽���bufer�е�����

	glDrawArrays(GL_POINTS, 0, 1);	 // ��ʼ���Ƽ���ͼ��(����һ����)
	glDisableVertexAttribArray(0); 	 //  ���ö�������
	glutSwapBuffers();	// ����ǰ�󻺴�
}

//�������㻺����
static void CreateVertexBuffer()
{
	Vector3f Vertices[1];	// ��������һ������Ķ�������
	Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);	// ����������Ļ����

	glGenBuffers(1, &VBO);	// ����������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	  // ��GL_ARRAY_BUFFER������

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);	 // �󶨶�������
}

//��ں���
int main(int argc, char ** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ��ʾģʽ��˫���塢RGBA

	glutInitWindowSize(400, 400);     
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("����һ������");  
									   
	glutDisplayFunc(RenderCallBack);	// ��ʼ��Ⱦ

	// ���GLEW�Ƿ����������Ҫ��GLUT��ʼ��֮��
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//������պ����ɫֵ
	CreateVertexBuffer();	//�������㻺����
	glutMainLoop();	  //֪ͨ��ʼGLUT���ڲ�ѭ��

	return 0;
}

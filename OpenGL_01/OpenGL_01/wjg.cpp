#include<GL/freeglut.h>  //freeglut���ڿ�
#include<iostream>

//��Ⱦ�ص�����
void RenderCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);	//��յ�ǰ֡����
	glutSwapBuffers();	//����ǰ�󻺴�
}

int main(int argc,char ** argv)
{
	glutInit(&argc, argv);	//��ʼ��GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//��ʾģʽ��˫���壬RGBA

	glutInitWindowPosition(200, 200);	//���ڵ�λ��
	glutInitWindowSize(400, 400);	//���ڵĴ�С
	glutCreateWindow("�ҵĵ�һ��OpenGL����");	//���ڵı���

	glutDisplayFunc(RenderCallBack);	//��ʼ��Ⱦ
	glClearColor(100.0f, 0.0f, 0.0f, 0.0f);	//������պ����ɫֵ
	glutMainLoop();		//��ʼGLUT���ڲ�ѭ��

	return 0;
}
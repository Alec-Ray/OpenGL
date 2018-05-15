#include<GL/freeglut.h>  //freeglut窗口库
#include<iostream>

//渲染回掉函数
void RenderCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);	//清空当前帧缓存
	glutSwapBuffers();	//交换前后缓存
}

int main(int argc,char ** argv)
{
	glutInit(&argc, argv);	//初始化GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	//显示模式：双缓冲，RGBA

	glutInitWindowPosition(200, 200);	//窗口的位置
	glutInitWindowSize(400, 400);	//窗口的大小
	glutCreateWindow("我的第一个OpenGL程序");	//窗口的标题

	glutDisplayFunc(RenderCallBack);	//开始渲染
	glClearColor(100.0f, 0.0f, 0.0f, 0.0f);	//缓存清空后的颜色值
	glutMainLoop();		//开始GLUT的内部循环

	return 0;
}
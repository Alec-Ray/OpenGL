#include <stdio.h>
#include <GL/glew.h>        // GLEW扩展库,注意glew.h必须要写在前面
#include <GL/freeglut.h>  // freeGLUT图形库
#include "ogldev_math_3d.h" // 用于OpenGL的3d数学库,这里主要用到了顶点这个数据结构，里面报错的代码可以先注释掉

GLuint VBO;		//全局GLuint引用变量，来操作顶点缓冲器对象

//渲染回调函数
static void RenderCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);	// 清空颜色缓存

	glEnableVertexAttribArray(0);	// 开启顶点属性
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		//绑定GL_ARRAY_BUFFER缓冲器
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	// 管线解析bufer中的数据

	glDrawArrays(GL_POINTS, 0, 1);	 // 开始绘制几何图形(绘制一个点)
	glDisableVertexAttribArray(0); 	 //  禁用顶点数据
	glutSwapBuffers();	// 交换前后缓存
}

//创建顶点缓冲器
static void CreateVertexBuffer()
{
	Vector3f Vertices[1];	// 创建含有一个顶点的顶点数组
	Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);	// 将点置于屏幕中央

	glGenBuffers(1, &VBO);	// 创建缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	  // 绑定GL_ARRAY_BUFFER缓冲器

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);	 // 绑定顶点数据
}

//入口函数
int main(int argc, char ** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 显示模式：双缓冲、RGBA

	glutInitWindowSize(400, 400);     
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("这是一个顶点");  
									   
	glutDisplayFunc(RenderCallBack);	// 开始渲染

	// 检查GLEW是否就绪，必须要在GLUT初始化之后！
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//缓存清空后的颜色值
	CreateVertexBuffer();	//创建顶点缓冲器
	glutMainLoop();	  //通知开始GLUT的内部循环

	return 0;
}

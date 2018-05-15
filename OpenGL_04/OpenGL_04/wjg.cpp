#include <stdio.h>
#include<string.h>
#include <GL/glew.h>        // GLEW扩展库,注意glew.h必须要写在前面
#include <GL/freeglut.h>    // freeGLUT图形库

#include "ogldev_math_3d.h"    //用于OpenGL的3d数学库,这里主要用到了顶点这个数据结构，里面报错的代码可以先注释掉
#include "ogldev_util.h"	//用于读取文本文件

GLuint VBO;   //全局GLuint引用变量，来操作顶点缓冲器对象

// 定义要读取的顶点着色器脚本和片断着色器脚本的文件名，作为文件读取路径
const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void RenderCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT); //清空颜色缓存

	glEnableVertexAttribArray(0);   //开启顶点属性
	glBindBuffer(GL_ARRAY_BUFFER, VBO);   //绑定GL_ARRAY_BUFFER缓冲器
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);   //管线解析bufer中的数据

	glDrawArrays(GL_TRIANGLES, 0, 3);   //画三角形，3个顶点
	glDisableVertexAttribArray(0);   //禁用顶点数据
	glutSwapBuffers();   //交换前后缓存
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderCallBack);
}

static void CreateVertexBuffer()
{
	Vector3f Vertices[3];   //创建含有3个顶点的顶点数组
	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f); 
	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f); 
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f); 

	glGenBuffers(1, &VBO);   //创建缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO);   //绑定GL_ARRAY_BUFFER缓冲器

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);   //绑定顶点数据
}

//使用shader文本编译shader对象，并绑定shader都想到着色器程序中
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	// 根据shader类型参数定义两个shader对象
	GLuint ShaderObj = glCreateShader(ShaderType);
	// 检查是否定义成功
	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	// 定义shader的代码源
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0]= strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);	   // 编译shader对象

	// 检查和shader相关的错误
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	// 将编译好的shader对象绑定到program object程序对象上
	glAttachShader(ShaderProgram, ShaderObj);
}

// 编译着色器函数
static void CompileShaders()
{
	// 创建着色器程序
	GLuint ShaderProgram = glCreateProgram();
	// 检查是否创建成功
	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// 存储着色器文本的字符串缓冲
	string vs, fs;

	// 分别读取着色器文件中的文本到字符串缓冲区
	if (!ReadFile(pVSFileName, vs)) {
		exit(1);
	};
	if (!ReadFile(pFSFileName, fs)) {
		exit(1);
	};

	// 添加顶点着色器和片段着色器
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	// 链接shader着色器程序，并检查程序相关错误
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// 检查验证在当前的管线状态程序是否可以被执行
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// 设置到管线声明中来使用上面成功建立的shader程序
	glUseProgram(ShaderProgram);
}

int main(int argc, char ** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 

	glutInitWindowSize(400, 400);     
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("Shader三角形");  

	glutDisplayFunc(RenderCallBack);  //开始渲染

	InitializeGlutCallbacks();

    // 检查GLEW是否就绪，必须要在GLUT初始化之后！
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //缓存清空后的颜色值
	CreateVertexBuffer(); //创建顶点缓冲器
				  
	CompileShaders();	// 编译着色器

	glutMainLoop();   //通知开始GLUT的内部循环

	return 0;
}



	

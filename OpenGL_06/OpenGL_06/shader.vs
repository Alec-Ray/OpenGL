#version 330  //���߱��������ǵ�Ŀ��GLSL�������汾��3.3

// �󶨶��������������ԣ���ʽ���������Ժ�shader���Զ�Ӧӳ��
layout (location = 0) in vec3 Position; 

// ƽ�Ʊ任�۾���һ�±���
uniform mat4 gWorld;

void main()
{
	// ��ƽ�Ʊ任�������ͼ�ζ���λ�ö�Ӧ��4X4������ˣ����ƽ�Ʊ任
    gl_Position = gWorld * vec4(Position, 1.0);
}



#version 330  //���߱��������ǵ�Ŀ��GLSL�������汾��3.3

layout (location = 0) in vec3 Position; // �󶨶��������������ԣ���ʽ���������Ժ�shader���Զ�Ӧӳ��

void main()
{
    gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0); // ΪglVertexAttributePointer�ṩ����ֵ
}
#version 330  //告诉编译器我们的目标GLSL编译器版本是3.3

layout (location = 0) in vec3 Position; // 绑定定点属性名和属性，方式二缓冲属性和shader属性对应映射

uniform float gScale;

//在 Shader 中声明一个一致变量 
void main()
{
    gl_Position = vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0); // 为glVertexAttributePointer提供返回值
}
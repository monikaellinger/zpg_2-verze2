#include "Shader.h"

Shader::Shader(GLenum shaderType, const char* shaderSource)
{
    this->shaderType = shaderType;
    this->shaderSource = shaderSource;
    this->shaderID = glCreateShader(this->shaderType);
    glShaderSource(this->shaderID, 1, &this->shaderSource, NULL);
    glCompileShader(this->shaderID);

    // Check compilation status
    GLint status;
    glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(this->shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(this->shaderID, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}
GLuint Shader::getShaderId()
{
    return this->shaderID;
}
void Shader::setUniformMatrix4fv(GLuint programID, const char* uniformName, const glm::mat4& matrix)
{
    GLint idModelTransform = glGetUniformLocation(programID, uniformName);
    if (idModelTransform == -1) {
        fprintf(stderr, "Uniform variable '%s' not found!\n", uniformName);
        return; 
    }
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(matrix));
}

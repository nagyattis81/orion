#include "spdlog/spdlog.h"

#include "program.hpp"
#include "shader.hpp"

Program::~Program() {
  if (id == GL_NONE)
    return;
  glDeleteProgram(id);
}

bool Program::Load(const char *vertexShaderPath,
                   const char *fragmentShaderPath) {
  spdlog::info("Program load [{}, {}]", vertexShaderPath, fragmentShaderPath);

  vsPath = vertexShaderPath;
  fsPath = fragmentShaderPath;

  Shader vs;
  if (!vs.Load(vertexShaderPath, GL_VERTEX_SHADER))
    return false;

  Shader fs;
  if (!fs.Load(fragmentShaderPath, GL_FRAGMENT_SHADER))
    return false;

  id = glCreateProgram();
  if (id == GL_NONE) {
    spdlog::critical("program create error");
    return false;
  }
  vs.Attach(id);
  fs.Attach(id);
  glLinkProgram(id);

  GLint linkStatus = GL_TRUE;
  glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
  if (linkStatus == GL_FALSE) {
    GLint infoLogLength = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
    GLchar *info = new GLchar[infoLogLength + 1];
    glGetProgramInfoLog(id, infoLogLength, 0, info);
    spdlog::critical("program link error: {}", info);
    delete[] info;
    return false;
  }
  return true;
}

void Program::Bind() const { glUseProgram(id); }

void Program::UnBind() const { glUseProgram(GL_NONE); }

bool Program::Location(GLint &location, const char *name) {
  location = glGetUniformLocation(id, name);
  if (location == -1) {
    spdlog::critical("Uniform location '{}' not found in [{}, {}]", name,
                     vsPath, fsPath);
    return false;
  }
  return true;
}
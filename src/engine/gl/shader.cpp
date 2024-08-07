#include "spdlog/spdlog.h"

#include "shader.hpp"
#include <fstream>
#include <sstream>

using namespace std;

Shader::~Shader() {
  if (id == GL_NONE)
    return;
  glDeleteShader(id);
}

bool Shader::Load(const char *path, const GLenum type) {
  ifstream file(path);
  if (!file) {
    spdlog::critical("file load error: {}", path);
    return false;
  }
  file.ignore(numeric_limits<streamsize>::max());
  auto size = file.gcount();
  if (size > 0x10000) {
    spdlog::critical("file load error size limit: {}", path);
    return false;
  }

  file.clear();
  file.seekg(0, ios_base::beg);
  stringstream sstr;
  sstr << file.rdbuf();
  file.close();

  const auto source = sstr.str();
  if (source == "") {
    spdlog::critical("empty shader source: {}", path);
    return false;
  }

  id = glCreateShader(type);
  if (id == GL_NONE) {
    spdlog::critical("create shader error: {}", path);
    return false;
  }

  const char *source_ptr = source.c_str();
  glShaderSource(id, 1, &source_ptr, nullptr);

  glCompileShader(id);
  GLint compiled = GL_TRUE;
  glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

  if (compiled == GL_FALSE) {
    GLint infoLogLength = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
      GLchar *info = new GLchar[infoLogLength + 1];
      glGetShaderInfoLog(id, infoLogLength, nullptr, info);
      spdlog::critical("shader compile error: {}\n{}", path, info);
      delete[] info;
    }
    return false;
  }

  return true;
}

void Shader::Attach(const GLuint program) { glAttachShader(program, id); }
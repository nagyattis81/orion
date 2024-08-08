#include "spdlog/spdlog.h"

#include "fbo.hpp"

namespace gl {

static bool LOGERR(const char *msg) {
  spdlog::critical(msg);
  return false;
}

static bool FBOValidate(const GLuint id) {
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  switch (status) {
  case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    return LOGERR("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
  case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
    return LOGERR("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
  case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
    return LOGERR("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
  case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
    return LOGERR("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
  case GL_FRAMEBUFFER_UNSUPPORTED:
    return LOGERR("GL_FRAMEBUFFER_UNSUPPORTED");
  case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
    return LOGERR("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
  case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
    return LOGERR("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS");
  }
  glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
  return true;
}

bool FBO::Create(const ivec2 size) {
  if (id != GL_NONE) {
    glDeleteFramebuffers(1, &id);
    id = GL_NONE;
  }

  glGenFramebuffers(1, &id);
  if (id == GL_NONE)
    return false;

  this->size = size;

  glBindFramebuffer(GL_FRAMEBUFFER, id);

  color.Create(size, GL_LINEAR, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
  color.SetClampToEdge();
  color.Framebuffer(GL_COLOR_ATTACHMENT0);

  depth.Create(size, GL_LINEAR, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT,
               GL_UNSIGNED_INT);
  depth.Framebuffer(GL_DEPTH_ATTACHMENT);

  glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);

  if (!FBOValidate(id))
    return false;

  return true;
}

void FBO::Bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  glViewport(0, 0, size.x, size.y);
}

void FBO::UnBind() const { glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE); }

} // namespace gl
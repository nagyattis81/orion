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

  glGenTextures(1, &color);
  glBindTexture(GL_TEXTURE_2D, color);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB,
               GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, GL_NONE);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         color, 0);

  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
  glBindRenderbuffer(GL_RENDERBUFFER, GL_NONE);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, rbo);

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
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

bool FBO::Create(const ivec2 size, const unsigned int samples) {
  if (fbo != GL_NONE) { // TODO fbo Delete
    glDeleteFramebuffers(1, &fbo);
    fbo = GL_NONE;
  }

  glGenFramebuffers(1, &fbo);
  if (fbo == GL_NONE)
    return false;

  this->size = size;

  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  color.Delete();
  color.Create(size, GL_LINEAR, GL_RGB, GL_RGB);
  color.Framebuffer(GL_COLOR_ATTACHMENT0);

  if (depthBuffer != GL_NONE) { // TODO rbo Delete
    glDeleteRenderbuffers(1, &depthBuffer);
    depthBuffer = GL_NONE;
  }
  glGenRenderbuffers(1, &depthBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
  glBindRenderbuffer(GL_RENDERBUFFER, GL_NONE);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, depthBuffer);

  glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);

  if (!FBOValidate(fbo))
    return false;

  this->samples = samples;
  if (this->samples == 0)
    return true;

  // TODO rbo Delete
  glGenRenderbuffers(1, &colorBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, colorBuffer);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER, this->samples, GL_RGBA8,
                                   size.x, size.y);

  // TODO rbo Delete
  glGenRenderbuffers(1, &depthBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER, this->samples,
                                   GL_DEPTH_COMPONENT, size.x, size.y);

  // TODO fbo Delete
  glGenFramebuffers(1, &mfbo);
  glBindFramebuffer(GL_FRAMEBUFFER, mfbo);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                            GL_RENDERBUFFER, colorBuffer);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, depthBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);

  return true;
}

void FBO::Render(function<void(void)> render) const {
  if (!render)
    return;
  glViewport(0, 0, size.x, size.y);
  if (samples == 0) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    render();
  } else {
    glBindFramebuffer(GL_FRAMEBUFFER, mfbo);
    render();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mfbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    glBlitFramebuffer(0, 0, size.x, size.y, 0, 0, size.x, size.y,
                      GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
  }
  glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

const Texture2D &FBO::GetColor() const { return color; }

} // namespace gl
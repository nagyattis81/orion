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

static void DeleteFramebuffer(GLuint &id) {
  if (id == GL_NONE)
    return;
  glDeleteFramebuffers(1, &id);
  id = GL_NONE;
}

static void CreateFramebuffer(GLuint &id, function<void(void)> setup) {
  glGenFramebuffers(1, &id);
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  setup();
  glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

static void DeleteRenderbuffer(GLuint &id) {
  if (id == GL_NONE)
    return;
  glDeleteRenderbuffers(1, &id);
  id = GL_NONE;
}

static void CreateRenderbuffer(GLuint &id, const ivec2 &size,
                               const GLenum internalformat,
                               const GLsizei samples = 0) {
  glGenRenderbuffers(1, &id);
  glBindRenderbuffer(GL_RENDERBUFFER, id);
  if (samples > 0)
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat,
                                     size.x, size.y);
  else
    glRenderbufferStorage(GL_RENDERBUFFER, internalformat, size.x, size.y);
  glBindRenderbuffer(GL_RENDERBUFFER, GL_NONE);
}

bool FBO::Create(const ivec2 size, const unsigned int samples) {
  this->size = size;

  DeleteFramebuffer(fbo);
  CreateFramebuffer(fbo, [=]() {
    color.Delete();
    color.Create(size, GL_LINEAR, GL_RGB, GL_RGB);
    DeleteRenderbuffer(depthBuffer);
    CreateRenderbuffer(depthBuffer, size, GL_DEPTH24_STENCIL8);
    color.Framebuffer(GL_COLOR_ATTACHMENT0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, depthBuffer);
  });

  if (!FBOValidate(fbo))
    return false;

  this->samples = samples;
  if (samples == 0)
    return true;

  DeleteFramebuffer(mfbo);
  CreateFramebuffer(mfbo, [=]() {
    DeleteRenderbuffer(colorBuffer);
    CreateRenderbuffer(colorBuffer, size, GL_RGBA8, samples);
    DeleteRenderbuffer(depthBuffer);
    CreateRenderbuffer(depthBuffer, size, GL_DEPTH_COMPONENT, samples);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, colorBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, depthBuffer);
  });

  return FBOValidate(mfbo);
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
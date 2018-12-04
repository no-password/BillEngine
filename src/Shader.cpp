#include "Shader.h"
#include <cstdio>
#include <cstdlib>

static char* readShaderSource(const char* shaderFile) {
  FILE* fp = fopen(shaderFile, "r");

  if ( fp == NULL ) { return NULL; }

  fseek(fp, 0L, SEEK_END);
  long size = ftell(fp);

  fseek(fp, 0L, SEEK_SET);
  char* buf = (char *) malloc(size + 1);
  fread(buf, 1, size, fp);

  buf[size] = '\0';
  fclose(fp);

  return buf;
}

GLuint initshader(const char* vShaderFile, const char* fShaderFile){
  struct Shader {
    const char*  filename;
    GLenum       type;
    GLchar*      source;
  }  shaders[2] = {
    {vShaderFile, GL_VERTEX_SHADER, NULL},
    {fShaderFile, GL_FRAGMENT_SHADER, NULL}
  };

  printf("A\n");
  GLuint program = glCreateProgram();
  printf("AB\n");
  int i;
  struct Shader *s;
  GLint  shader, compiled, linked, logSize;
  char   *logMsg;


  printf("B\n");
  for (i = 0; i < 2; ++i) {
    s = &shaders[i];
    s->source = readShaderSource(s->filename);
    if (shaders[i].source == NULL) {
      fprintf(stderr, "Failed to read %s\n", s->filename);
      exit(EXIT_FAILURE);
    }

  printf("C\n");
    shader = glCreateShader(s->type);
    glShaderSource(shader, 1, (const GLchar**) &s->source, NULL);
    glCompileShader(shader );

  printf("D\n");
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
      fprintf(stderr, "%s failed to compile\n", s->filename);
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
      logMsg = (char *) malloc(logSize);
      glGetShaderInfoLog(shader, logSize, NULL, logMsg);
      fprintf(stderr, "%s\n", logMsg);
      free(logMsg);

      exit( EXIT_FAILURE );
    }

  printf("E\n");
    free(s->source);

  printf("F\n");
    glAttachShader(program, shader);
  }

  /* link  and error check */
  glLinkProgram(program);

  glGetProgramiv( program, GL_LINK_STATUS, &linked );
  if ( !linked ) {
    fprintf(stderr, "Shader program failed to link\n");
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
    logMsg = (char *) malloc(logSize);
    glGetProgramInfoLog(program, logSize, NULL, logMsg);
    fprintf(stderr, "%s\n", logMsg);
    free(logMsg);

    exit( EXIT_FAILURE );
  }

  return program;
}


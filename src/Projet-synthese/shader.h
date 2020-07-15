#ifndef _SHADER_H
#define _SHADER_H
#include <cstdio>
#include <cstring>

#include "glcore.h"
#include "window.h"

#include "program.h"
#include "uniforms.h"

#include "texture.h"
#include "mesh.h"
#include "wavefront.h"

#include "vec.h"
#include "mat.h"
#include "orbiter.h"

#include "text.h"
#include "widgets.h"
#include "glcore.h"

#include "draw.h"


struct Filename
{
    char path[1024];
    
    Filename( ) { path[0]= 0; }
    Filename( const char *_filename ) { strcpy(path, _filename); }
    operator const char *( ) { return path; }
};

class shader
{
public:
    void init();
    void reloade_program(GLuint & program);
    void edraw(Mesh & mesh,Transform  T,Orbiter  & camera,GLuint  & texture,Point luxPosition,Point Direction,GLuint & Porgram);
    void quit();
    GLuint & getProgram(int i);
    int foudreControle;
    int nbindice=0;
    float time=0.0;
protected :
    Filename program_filename;
    GLuint program;
    GLuint program1;
    Widgets widgets;

    // affichage des erreurs
    std::string program_log;
    int program_area;
    bool program_failed;
    Filename mesh_filename;
    Mesh mesh;
    DrawParam gl;

    std::vector<Filename> texture_filenames;
    std::vector<GLuint> textures;
};
#endif
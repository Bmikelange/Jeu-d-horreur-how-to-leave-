#include "shader.h"

#include "draw.h"

#include "program.h"


void shader::init()
{
    widgets= create_widgets();
    program= 0;
    program1=0;
    program_filename= Filename("data/projet/shader/shader7.glsl");
    reloade_program(program);
    program_filename= Filename("data/projet/shader/shader6.glsl");
    reloade_program(program1);
    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClearDepth(1.f);
    
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glDisable(GL_CULL_FACE);
    
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void shader::reloade_program(GLuint & Program )
{
    if(Program == 0)
        Program= read_program(program_filename);
    else
        reload_program(Program, program_filename);
    
    // recupere les erreurs, si necessaire
    program_area= program_format_errors(Program, program_log);
    
    if(program_log.size() > 0)
        printf("[boom]\n%s\n", program_log.c_str());
    
    program_failed= (program_log.size() > 0);
}

void shader::quit()
{
    release_program(program);
    release_program(program1);
}

GLuint & shader::getProgram(int i)
{
    if(i==0) return program;
    if(i==1) return program1;
    return program;
}

void shader::edraw(Mesh &mesh,Transform T,Orbiter & camera,GLuint & texture,Point luxPosition,Point Direction,GLuint & Program)
{
    // recupere les transformations
    
    Transform model= T;
    Transform view= camera.view();
    Transform projection= camera.projection(window_width(), window_height(), 45);
    
    Transform mvp= projection * view * model;
    
    GLuint vao= mesh.create_buffers(mesh.has_texcoord(), mesh.has_normal(), mesh.has_color());
        
    // configuration minimale du pipeline
    glBindVertexArray(vao);
    glUseProgram(Program);

    // affecte une valeur aux uniforms
    // transformations standards
    program_uniform(Program, "modelMatrix", model);
    program_uniform(Program, "viewInvMatrix", view.inverse());

    
    program_uniform(Program, "mvpMatrix", mvp);
    
    program_uniform(Program, "source", luxPosition);
    program_uniform(Program,"direction",Point(0,0,0)-Direction);
    program_uniform(Program, "foudre", foudreControle);
    program_uniform(Program,"time",time);

    char uniform[1024];
    sprintf(uniform, "diffuse_color");
    program_use_texture(Program, uniform, 1, texture);
    
    
    // textures
    
    // go
    glDrawArrays(GL_TRIANGLES, 0,mesh.vertex_count());
    
    begin(widgets);
    label(widgets, "indices collectes :");
    begin_line(widgets);
    label(widgets, "      %d/6", nbindice);
    end(widgets);
    
    draw(widgets, window_width(), window_height());
}
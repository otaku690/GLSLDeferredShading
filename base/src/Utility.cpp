#include "Utility.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace Utility {

	char* loadFile(const char *fname, GLint &fSize)
	{
		ifstream::pos_type size;
		char * memblock;
		std::string text;

		// file read based on example in cplusplus.com tutorial
		ifstream file (fname, ios::in|ios::binary|ios::ate);
		if (file.is_open())
		{
			size = file.tellg();
			fSize = (GLuint) size;
			memblock = new char [size];
			file.seekg (0, ios::beg);
			file.read (memblock, size);
			file.close();
			cout << "file " << fname << " loaded" << endl;
			text.assign(memblock);
		}
		else
		{
			cout << "Unable to open file " << fname << endl;
			exit(1);
		}
		return memblock;
	}

	// printShaderInfoLog
	// From OpenGL Shading Language 3rd Edition, p215-216
	// Display (hopefully) useful error messages if shader fails to compile
	void printShaderInfoLog(GLint shader)
	{
		int infoLogLen = 0;
		int charsWritten = 0;
		GLchar *infoLog;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

		// should additionally check for OpenGL errors here

		if (infoLogLen > 0)
		{
			infoLog = new GLchar[infoLogLen];
			// error check for fail to allocate memory omitted
			glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
			cout << "InfoLog:" << endl << infoLog << endl;
			delete [] infoLog;
		}

		// should additionally check for OpenGL errors here
	}

	void printLinkInfoLog(GLint prog) 
	{
		int infoLogLen = 0;
		int charsWritten = 0;
		GLchar *infoLog;

		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

		// should additionally check for OpenGL errors here

		if (infoLogLen > 0)
		{
			infoLog = new GLchar[infoLogLen];
			// error check for fail to allocate memory omitted
			glGetProgramInfoLog(prog,infoLogLen, &charsWritten, infoLog);
			cout << "InfoLog:" << endl << infoLog << endl;
			delete [] infoLog;
		}
	}

    GLuint initshaders (GLenum type, const char *filename) 
    {
        GLuint shader = glCreateShader(type) ; 
        GLint compiled ; 
        char *ss;
        GLint slen;

        ss = loadFile(filename,slen);
        const char * cs = ss;

        glShaderSource (shader, 1, &cs, &slen) ; 
        glCompileShader (shader) ; 
        glGetShaderiv (shader, GL_COMPILE_STATUS, &compiled) ; 
		if (!compiled)
		{
			cout << "Vertex shader not compiled." << endl;
			printShaderInfoLog(shader);
		} 
        delete [] ss;

        return shader ; 
    }

	shaders_t loadShaders(const char * vert_path, const char * frag_path, const char * geom_path) {
		GLuint f, v, g = 0;

		v = initshaders( GL_VERTEX_SHADER, vert_path );
        f = initshaders( GL_FRAGMENT_SHADER, frag_path );
        if( geom_path )
            g = initshaders( GL_GEOMETRY_SHADER, geom_path );

        shaders_t out; out.vertex = v; out.fragment = f; out.geometry = g;

		return out;
	}

	void attachAndLinkProgram( GLuint program, shaders_t shaders) {
		glAttachShader(program, shaders.vertex);
		glAttachShader(program, shaders.fragment);
        if( shaders.geometry )
            glAttachShader(program, shaders.geometry  );

		glLinkProgram(program);
		GLint linked;
		glGetProgramiv(program,GL_LINK_STATUS, &linked);
		if (!linked) 
		{
			cout << "Program did not link." << endl;
			printLinkInfoLog(program);
		}
	}
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "EGE3dErrorHandler.h"

std::string getGlErrorDescription(int errorCode){
    switch(errorCode){
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM - Given when an enumeration parameter is not a legal enumeration for that function. This is given only for local problems; if the spec allows the enumeration in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead."; 
            break;
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE - Given when a value parameter is not a legal value for that function. This is only given for local problems; if the spec allows the value in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead.";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION - Given when the set of state for a command is not legal for the parameters given to that command. It is also given for commands where combinations of parameters define what the legal parameters are."; 
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION - Given when doing anything that would attempt to read from or write/render to a framebuffer that is not complete.";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY - Given when performing an operation that can allocate memory, and the memory cannot be allocated. The result of OpenGL functions that return this error are undefined; it is allowable for partial operations to happen.";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW - Given when a stack popping operation cannot be done because the stack is already at its lowest point..";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW - Given when a stack pushing operation cannot be done because it would overflow the limit of that stack's size..";
        default:
            return "No GL Error description found";
    }
};

static void checkGlError(char* message){
    int errCode=glGetError();
    if(errCode!=0){
        //Errore attivo
        std::cout << "ERR(" << errCode << ") RILEVATO ERRORE glGetError() : " << message << std::endl;
        
        if(errCode==GL_INVALID_ENUM) { std::cout << "GL_INVALID_ENUM - Given when an enumeration parameter is not a legal enumeration for that function. This is given only for local problems; if the spec allows the enumeration in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead." << std::endl; }
        if(errCode==GL_INVALID_VALUE) {std::cout << "GL_INVALID_VALUE - Given when a value parameter is not a legal value for that function. This is only given for local problems; if the spec allows the value in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead." << std::endl; }
        if(errCode==GL_INVALID_OPERATION) {std::cout << "GL_INVALID_OPERATION - Given when the set of state for a command is not legal for the parameters given to that command. It is also given for commands where combinations of parameters define what the legal parameters are." << std::endl; }
        if(errCode==GL_INVALID_FRAMEBUFFER_OPERATION) {std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION - Given when doing anything that would attempt to read from or write/render to a framebuffer that is not complete." << std::endl; }
        if(errCode==GL_OUT_OF_MEMORY) {std::cout << "GL_OUT_OF_MEMORY - Given when performing an operation that can allocate memory, and the memory cannot be allocated. The results of OpenGL functions that return this error are undefined; it is allowable for partial operations to happen." << std::endl; }
        if(errCode==GL_STACK_UNDERFLOW) {std::cout << "GL_STACK_UNDERFLOW - Given when a stack popping operation cannot be done because the stack is already at its lowest point.." << std::endl; }
        if(errCode==GL_STACK_OVERFLOW) {std::cout << "GL_STACK_OVERFLOW - Given when a stack pushing operation cannot be done because it would overflow the limit of that stack's size.." << std::endl; }
        //if(errCode==GL_CONTEXT_LOST) {std::cout << "GL_STACK_OVERFLOW - Given when a stack pushing operation cannot be done because it would overflow the limit of that stack's size.." << std::endl; }
    }
};



int egeLogEx(int egeCode, std::string func, std::string errMessage){
    int res;
	
    if(egeCode==EGE_CHECK_FOR_OPENGL_ERROR){
        
        int errCode=glGetError();
        if(errCode!=0){
            std::cout << "12:00:00 - egeLogEx - OpenGL Error Code:[" << errCode << "] Description:{" <<getGlErrorDescription(errCode) << "}"; 
                std::cout << " ==>> Call Function - " << func << std::endl;
                std::cout << "Extended Application message: " << errMessage << "\n" << std::endl;
            res=errCode;
        }    
    }else{
            std::cout << "12:00:00 - egeLogEx - Internal Error Code:[" << egeCode << "]"; 
            std::cout << " ==>> Call Function - " << func << std::endl;
            std::cout << "Extended Application message: " << errMessage << "\n" << std::endl;
    } 
	return res;
}

// Log dedicato shaders opengl
void egeLogProgram(const int programId,bool content){
    GLchar *buffer=NULL; int sizebuffer=0;
    
    if(!content){
        glGetProgramInfoLog(programId, 1024, &sizebuffer, buffer);
        std::string strBuffer=(std::string)buffer;
        std::cout << "Extended OpenGL PROGRAM INFO LOG : " << strBuffer << std::endl;
    }else{
        glGetShaderSource(programId, 4096, &sizebuffer, buffer);
        std::string strShader=(std::string)buffer;
        std::cout << "Program Content : " << strShader << std::endl;
    }
    if(buffer)delete buffer;
}

// Log dedicato shaders opengl
void egeLogShader(const int shaderId,bool content){
    GLchar *buffer; int sizebuffer;
    
    if(!content){
        glGetShaderInfoLog(shaderId, 1024, &sizebuffer, buffer);
        std::string strBuffer=(std::string)buffer;
        std::cout << "Extended OpenGL Message : " << strBuffer << std::endl;
    }else{
        glGetShaderSource(shaderId, 4096, &sizebuffer, buffer);
        std::string strShader=(std::string)buffer;
        std::cout << "Shader Content : " << strShader << std::endl;
    }
    delete buffer;
	
}

int egeLog(int egeCode, std::string errMessage, IObject* caller){
    IObject* obj=NULL;
    
    if(caller){     obj=(IObject*)caller;   } 
    int res=0;
    
        if(egeCode>0){  
            std::cout << "12:00:00 - egeLog - EGE::system::error code[" << egeCode << "]" << std::endl; 
            res=egeCode;
            if(obj){
                    std::cout << " ==>> Application Class - " << obj->__IObject_globalClassName() << " (with ID[" << obj->__IObject_globalClassUID() << "])" << std::endl;
                    std::cout << " ==>> Call Function - " << obj->__IObject_globalFunctionName() << std::endl;
            }else{
                    std::cout << " *** There are no Class informations for this object. (no IObject inherit) ***" << std::endl;
            }
    
        std::cout << "Extended Application message: " << errMessage << "\n" << std::endl; 
        
        if(egeCode==EGE_NULL_POINTER){ std::cout << " GENERIC ERROR : NULL POINTER - Si sta invocando una membro di classe da una istanza null.\n" << std::endl;  }
        
    }
    
    if(egeCode==EGE_CHECK_FOR_OPENGL_ERROR){
		
        int errCode=0;
#ifndef EGE_EMSCRIPTEN
        errCode=glGetError();
#else
        errCode=0;    
        std::cout << " glGetError() call function is skipped with EMSCRIPTEN\n" << std::endl; 
#endif        
                
        if(errCode!=0){
            std::cout << "12:00:00 - egeLog - OpenGL Error Code:[" << errCode << "] Description:{" << getGlErrorDescription(errCode) << "}" << std::endl; 
            if(obj){
                std::cout << " ==>> Application Class - " << obj->__IObject_globalClassName() << " (with ID[" << obj->__IObject_globalClassUID() << "])" << std::endl;
                std::cout << " ==>> Call Function - " << obj->__IObject_globalFunctionName() << std::endl;
            }else{
                std::cout << " *** There are no Class informations for this object. (no IObject inherit) ***" << std::endl;
            }
            std::cout << "Extended Application message: " << errMessage << "\n" << std::endl; 
            
            res=egeCode;
        } 
		
    }
	
    return res;
};

void GLFW_error_callback(int error, const char* description)
{
    std::cout << "GLFW Error Code : " << error << " - Description : " << description << std::endl; 
};


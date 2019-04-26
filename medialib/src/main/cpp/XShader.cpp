//
// Created by Eyey on 2019/4/9.
//

#include "XShader.h"
#include "ELog.h"

#define GET_STR(x) #x

static const char *vertex_shader = GET_STR(
        attribute vec4 aPosition; //顶点坐标
        attribute vec2 aTexCoord; //材质顶点坐标
        varying vec2 vTexCoord;   //输出的材质坐标
        void main(){
            vTexCoord = vec2(aTexCoord.x,1.0-aTexCoord.y);
            gl_Position = aPosition;
        }
//        attribute vec4 aPosition; //顶点坐标
//        attribute vec2 aTexCoord; //材质顶点坐标
//        varying vec2 vTexCoord;   //输出的材质坐标
//        void main(){
//            vTexCoord = vec2(aTexCoord.x,1.0-aTexCoord.y);
//            gl_Position = aPosition;
//        }
);


static const char *frag_shader = GET_STR(
        precision mediump float;
        varying vec2 vTexCoord;
        uniform sampler2D uTextureY;
        uniform sampler2D uTextureU;
        uniform sampler2D uTextureV;

        void main() {
            vec3 yuv;
            vec3 rgb;
            yuv.r = texture2D(uTextureY, vTexCoord).r;
            yuv.g = texture2D(uTextureU, vTexCoord).r - 0.5;
            yuv.b = texture2D(uTextureV, vTexCoord).r - 0.5;
            rgb = mat3(1.0, 1.0, 1.0,
                       0.0, -0.39465, 2.03211,
                       1.13983, -0.58060, 0.0) * yuv;
            gl_FragColor = vec4(rgb, 1.0);
        }


//        precision mediump float;    //精度
//        varying vec2 vTexCoord;     //顶点着色器传递的坐标
//        uniform sampler2D yTexture; //输入的材质（不透明灰度，单像素）
//        uniform sampler2D uTexture;
//        uniform sampler2D vTexture;
//        void main(){
//            vec3 yuv;
//            vec3 rgb;
//            yuv.r = texture2D(yTexture,vTexCoord).r;
//            yuv.g = texture2D(uTexture,vTexCoord).r - 0.5;
//            yuv.b = texture2D(vTexture,vTexCoord).r - 0.5;
//            rgb = mat3(1.0,     1.0,    1.0,
//                       0.0,-0.39465,2.03211,
//                       1.13983,-0.58060,0.0)*yuv;
//            //输出像素颜色
//            gl_FragColor = vec4(rgb,1.0);
//        }
);


/**
 * 世界坐标系显示窗口
 */
static const float cube[] = {
        1.0f,-1.0f,0.0f,
        -1.0f,-1.0f,0.0f,
        1.0f,1.0f,0.0f,
        -1.0f,1.0f,0.0f,
};


/**
 * 纹理坐标系
 */
static const float textureCube[] = {
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
};

static GLuint loadShader(const char *code, GLenum type) {
    GLuint iShader = glCreateShader(type);
    glShaderSource(iShader, 1, &code, 0);
    glCompileShader(iShader);
    GLint status = 0;
    glGetShaderiv(iShader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        GLchar buff[1024] = {0};
        glGetShaderInfoLog(iShader, 1024, NULL, buff);
        ELOGError("Load Shader Failed %s", buff);
    }
    return iShader;
}

bool XShader::init() {
    vsh = loadShader(vertex_shader, GL_VERTEX_SHADER);
    if (vsh == 0) {
        ELOGInfo("Load Program Vertex Shader Failed");
        return false;
    }
    fsh = loadShader(frag_shader, GL_FRAGMENT_SHADER);
    if (fsh == 0) {
        ELOGInfo("Load Program Fragment Shader Failed");
        return false;
    }
    program = glCreateProgram();

    glAttachShader(program, vsh);
    glAttachShader(program, fsh);
    glLinkProgram(program);
    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus <= 0) {
        ELOGInfo("Load Program Linking Failed");
        return false;
    }

    glUseProgram(program);
    //绑定顶点数据
    GLuint aPosId = static_cast<GLuint>(glGetAttribLocation(program, "aPosition"));
    glEnableVertexAttribArray(aPosId);
    glVertexAttribPointer(aPosId, 3, GL_FLOAT, GL_FALSE, 12, cube);
    //绑定纹理顶点数据
    GLuint aTexCo = static_cast<GLuint>(glGetAttribLocation(program, "aTexCoord"));
    glEnableVertexAttribArray(aTexCo);
    glVertexAttribPointer(aTexCo, 2, GL_FLOAT, GL_FALSE, 8, textureCube);

    glUniform1i(glGetUniformLocation(program, "uTextureY"), 0);
    glUniform1i(glGetUniformLocation(program, "uTextureU"), 1);
    glUniform1i(glGetUniformLocation(program, "uTextureV"), 2);
    ELOGInfo("init Shader success");
    return true;
}

void XShader::getTexture(unsigned int index, int width, int height, unsigned char *buf) {
    if (texts[index] == 0) {
        glGenTextures(1, &texts[index]);
        glBindTexture(GL_TEXTURE_2D, texts[index]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE,
                     GL_UNSIGNED_BYTE, NULL);
    }
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texts[index]);
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,width,height,GL_LUMINANCE,GL_UNSIGNED_BYTE,buf);


}

void XShader::draw() {
    if (!program)
        return;
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

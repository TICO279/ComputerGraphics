#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Movil.cpp"
#include "VEC3.h"

#include <iostream>
#include <cmath>
#include "linmath.h"
#include <learnopengl/filesystem.h>

#include <learnopengl/shader_s.h>

#include "Resorte_03_Caras_TEX.cpp"
//#include "Resorte_04_Normales_TEX_ejes.cpp"

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

VEC3 pos_1 = {0.0, 0.0, 0.0};
VEC3 vel_1 = {0.0, 0.0, 0.0};

VEC3 pos_2 = {384.403E6, 0.0, 0.0};
VEC3 vel_2 = {0.0, 946.6322, 0.0};

VEC3 pos_3 = { 6.37E6, 0.0, 0.0 };
VEC3 vel_3 = { 0.0, 7674.005, 0.0 };


double deltaT = 10;                //1 * 3600; // segundos en una hora
//double t_horas = 0.0f;

Movil mov_1("Tierra", 5.9736E24, pos_1, vel_1);
Movil mov_2(" Luna", 7.35E22, pos_2, vel_2);
Movil mov_3(" Satelite", 1500, pos_3, vel_3);

void generaPosiciones() {
  //t_horas += deltaT / 3600;

  mov_1.limpiaFza();
  mov_2.limpiaFza();
  mov_3.limpiaFza();
  //mov_3.limpiaFza();

  mov_1.interactua(&mov_2);
  mov_1.limpiaFza();
  mov_1.interactua(&mov_3);
  //mov_2.interactua(&mov_3);

  mov_1.mueve(deltaT);
  mov_2.mueve(deltaT);
  mov_3.mueve(deltaT);

 

  // mov_2.impFza();

  VEC3 dr;
  float radio;
  dr = mov_2.r - mov_1.r;

  radio = dr.norma();
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



const char* vertexShaderSource = "#version 330 core\n"
"uniform mat4 MVP;\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"	gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	ourColor = aColor;\n"
"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"// texture sampler\n"
"uniform sampler2D texture1;\n"
"void main()\n"
"{\n"
"     FragColor = texture(texture1, TexCoord);\n"
"}\n\0";








void mouse_callback(GLFWwindow* window, double xpos, double ypos);

struct V3
{
    float x;
    float y;
    float z;
};


vec3 eye, target, up;

V3 eye0 = { 0.0f, 0.0f, -12.0f };   //{ 0.0f, 0.0f, -20.0f};
V3 target0 = { 0.0f, 0.0f,  -6.0f };   //{ 0.0f, 0.0f, -0.1f};
V3 up0 = { 0.0f, 1.0f,   0.0f };   //{ 0.0f, 1.0f, 0.0f};

float radio_camara;
float cameraSpeed = 0.5f;
float lastX = 400, lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;


glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//float xpos = 500, ypos = 200;

//float lastX = 400, lastY = 300;




int main()
{
   

    

    eye[0] = eye0.x;
    eye[1] = eye0.y;
    eye[2] = eye0.z;

    vec3 radio_vector;
    vec3_sub(radio_vector, eye, target);

    radio_camara = vec3_len(radio_vector);

    
    target[0] = target0.x;
    target[1] = target0.y;
    target[2] = target0.z;
    

    up[0] = up0.x;
    up[1] = up0.y;
    up[2] = up0.z;



    GLint mvp_location, vpos_location, vcol_location;

    

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simulador Tierra-Luna", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

  

    
    glfwSetCursorPosCallback(window, mouse_callback);
    

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    mvp_location = glGetUniformLocation(shaderProgram, "MVP");
   

 


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

   


    int num_indices;


    int           num_vertices_esfera;
    int           num_indices_esfera;
    VERTICE_TEX* vertices_esfera;
    unsigned int* indices_esfera;

    int           num_vertices_esfera2;
    int           num_indices_esfera2;
    VERTICE_TEX* vertices_esfera2;
    unsigned int* indices_esfera2;

    int           num_vertices_satelite;
    int           num_indices_satelite;
    VERTICE_TEX* vertices_satelite;
    unsigned int* indices_satelite;



    int ESFERAG = 1;
    int ESFERAC = 2;
    int SATELITE = 3;
    
    int TIPO;

    


    creaSolRevCaras(ESFERAC,
                    &num_vertices_esfera, &vertices_esfera, // notense los & para obtener el lugar de memoria (referencia) de las variables
                    &num_indices_esfera,  &indices_esfera);

    creaSolRevCaras(ESFERAG,
        &num_vertices_esfera2, &vertices_esfera2, // notense los & para obtener el lugar de memoria (referencia) de las variables
        &num_indices_esfera2, &indices_esfera2);

    creaSolRevCaras(SATELITE,
        &num_vertices_satelite, &vertices_satelite, // notense los & para obtener el lugar de memoria (referencia) de las variables
        &num_indices_satelite, &indices_satelite);


    

    //
    // se despliegan ambos arreglos
    //
    // printf("modificar_072_SolRev: nu_vertices=%d, num_indices=%d\n",num_vertices_prisma, num_indices_prisma);

    /* int k,j,ikj;

     for(k = 0; k < num_vertices; k++) printf("%d %f %f %f %f %f %f\n",k,vertices[k].x,vertices[k].y,vertices[k].z,vertices[k].r,vertices[k].g,vertices[k].b);
     ikj = 0;
     for(k = 0; k < num_indices / 3; k++) for(j = 0; j < 3; j++) printf("%d %d %d\n",k,j,indices[ikj++]);
    */

    // codigo como siempre (solo se cambiaron los tamaños de los arreglos para estos datos)



    // ================================================================================
    //                               ESFERA Chica
    // ================================================================================

    unsigned int VBO_esfera, VAO_esfera, EBO_esfera;

    //if(TIPO == ESFERA)
    
        glGenVertexArrays(1, &VAO_esfera);
        glGenBuffers(1, &VBO_esfera);
        glGenBuffers(1, &EBO_esfera);

        num_indices = num_indices_esfera;

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO_esfera);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_esfera);
        glBufferData(GL_ARRAY_BUFFER, num_vertices_esfera * sizeof(VERTICE_TEX), vertices_esfera, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE_TEX), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE_TEX), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_esfera);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices_esfera * sizeof(unsigned int), indices_esfera, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTICE_TEX), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
    // ================================================================================
    //                              FIN DE ESFERA Chica
    // ================================================================================

    // ================================================================================
    //                               ESFERA Grande
    // ================================================================================

        unsigned int VBO_esfera2, VAO_esfera2, EBO_esfera2;

        //if(TIPO == ESFERA)

        glGenVertexArrays(1, &VAO_esfera2);
        glGenBuffers(1, &VBO_esfera2);
        glGenBuffers(1, &EBO_esfera2);

        num_indices = num_indices_esfera2;

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO_esfera2);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_esfera2);
        glBufferData(GL_ARRAY_BUFFER, num_vertices_esfera2 * sizeof(VERTICE_TEX), vertices_esfera2, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE_TEX), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE_TEX), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_esfera2);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices_esfera2 * sizeof(unsigned int), indices_esfera2, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTICE_TEX), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        

        // ================================================================================
        //                              FIN DE ESFERA Grande
        // ================================================================================


    // ================================================================================
    //                               Satelite
    // ================================================================================

        unsigned int VBO_satelite, VAO_satelite, EBO_satelite;

        

        glGenVertexArrays(1, &VAO_satelite);
        glGenBuffers(1, &VBO_satelite);
        glGenBuffers(1, &EBO_satelite);

        num_indices = num_indices_satelite;

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO_satelite);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_satelite);
        glBufferData(GL_ARRAY_BUFFER, num_vertices_satelite * sizeof(VERTICE_TEX), vertices_satelite, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE_TEX), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTICE_TEX), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_satelite);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices_satelite * sizeof(unsigned int), indices_satelite, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTICE_TEX), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
       
        // ================================================================================
        //                              FIN DE Satelite
        // ================================================================================

      

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);


    // load and create a texture
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/earthSpherical.jpg").c_str(), &width, &height, &nrChannels, 0);



    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    //textura2
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data2 = stbi_load(FileSystem::getPath("resources/textures/Moon_Spherical.jpg").c_str(), &width, &height, &nrChannels, 0);




    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data2);


    //textura2
    unsigned int texture3;
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data3 = stbi_load(FileSystem::getPath("resources/textures/marble.jpg").c_str(), &width, &height, &nrChannels, 0);




    if (data3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data3);






    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can
    // just bind it beforehand before rendering the respective triangle; this is another approach.
    

    float x, y, z;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        //processInput(window);
        //cout << "Camera speed: " << cameraSpeed << endl;

        // render
        // ------
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // be sure to activate the shader before any calls to glUniform
        glUseProgram(shaderProgram);

        float ratio;
        int width, height;
        mat4x4 m, p, mvp, pers, mk, mtr, mk2, mvp2, mtr2, mcam, mw;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        //glClear(GL_COLOR_BUFFER_BIT);

        //mat4x4_identity(m);
        //mat4x4_rotate_X(m, m, (float)glfwGetTime());
        //mat4x4_rotate_Y(m, m, (float)glfwGetTime());

        //mat4x4_ortho( p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //mat4x4_mul(mvp, p, m);

        float tr_y[2] = { 0.3f, -0.3f }; //{ 0.3f, -0.3f};
        float tr_x[2] = { 0.3f, -0.3f }; //{ 0.3f, -0.3f};
        float tr_z[2] = { -6.0f, -5.0f }; //{-6.0f, -5.0f};


        // generaPosiciones();

        mat4x4_perspective(pers, 30.0 * atan(1.0) / 45.0, 800.0 / 600.0, 1.0, 40.0);

        // mat4x4_perspective(pers, 20.0 * atan(1.0) / 45.0, 800.0 / 600.0, 1.0, 40.0); //Con angulo de 20, distancia de 1 de la camara y llega a una profundidad de 40 unidades

        for (int t = 0; t < 3; t++)
        {





            generaPosiciones();

            mat4x4_identity(m);

            mat4x4_rotate_Z(m, m, (t == 1 ? -1.0 : 1.0) * (float)glfwGetTime());

            //mat4x4_rotate_Y(m, m, (1.0) * (float)glfwGetTime());


            mat4x4_dup(mk, m);

            if (t == 1) {
                // mat4x4_translate(mtr, mov_2.r.x / 4.2e8, mov_2.r.y / 4.2e8, -6.0f);
                x = mov_2.r.x / 4.20E8;
                y = mov_2.r.y / 4.20E8;
                z = -6.0f;




            }
            else if (t == 2) {
                x = mov_1.r.x / 4.20E8;
                y = mov_1.r.y / 4.20E8;
                z = -6.0f;


            }

            else {

                x = mov_3.r.x / 2.20E7;
                y = mov_3.r.y / 2.20E7;
                z = -6.0f;


            }

            // mat4x4_perspective(pers, 30.0 * atan(1.0) / 45.0, 800.0 / 600.0,
              //   0.0f, 10.0f);



            target[0] = mov_1.r.x / 4.20E8;
            target[1] = mov_1.r.y / 4.20E8;
            target[2] = mov_1.r.z / 4.20E8;
           // cout << "mov_1.r.x : " << mov_1.r.x/4.20E8 << endl;


            eye[0] = (target[0] - cameraFront[0]); //* cosf((float)glfwGetTime()); esto los hace girar
            eye[1] = (target[1] + cameraFront[1]);
            //eye[2] = (target[2]- 0.75 * (radio_camara)); //* sinf((float)glfwGetTime()); esto los hace girar  // esto estaba antes 
            //cout << "Eye[2] : " << eye[2] << endl;

            processInput(window);

            
            


            mat4x4_look_at(mcam, eye, target, up);
            mat4x4_mul(mvp, pers, mcam);

            // mat4x4_mul(mk, mtr, mk);

            mat4x4_translate(mtr, x, y, z);
            mat4x4_mul(mk, mtr, mk);

           // mat4x4_dup(mw, mk);
            mat4x4_identity(mvp);
            mat4x4_mul(mvp, mcam, mk);
            mat4x4_mul(mvp, pers, mvp);

            //mat4x4_mul(mvp, pers, mk);
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);

            if (t == 1) {

                glBindTexture(GL_TEXTURE_2D, texture2);
                /*
                glUniformMatrix4fv(mw_location, 1, GL_FALSE, (const GLfloat*)mw);
                glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
                glUniformMatrix4fv(cam_location, 1, GL_FALSE, (const GLfloat*)eye);
                glUniform4fv(color_amb_location, 1, (const GLfloat*)ColorAmb);
                glUniform4fv(luz_color_location, 1, (const GLfloat*)elcolor);
                */

                glBindVertexArray(VAO_esfera);

            }

            else if (t == 2) {

                glBindTexture(GL_TEXTURE_2D, texture);
                /*
                glUniformMatrix4fv(mw_location, 1, GL_FALSE, (const GLfloat*)mw);
                glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
                glUniformMatrix4fv(cam_location, 1, GL_FALSE, (const GLfloat*)eye);
                glUniform4fv(color_amb_location, 1, (const GLfloat*)ColorAmb);
                glUniform4fv(luz_color_location, 1, (const GLfloat*)elcolor);
                */

                glBindVertexArray(VAO_esfera2);
            }

            else {

                glBindTexture(GL_TEXTURE_2D, texture3);
                
                /*
                glUniformMatrix4fv(mw_location, 1, GL_FALSE, (const GLfloat*)mw);
                glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
                glUniformMatrix4fv(cam_location, 1, GL_FALSE, (const GLfloat*)eye);
                glUniform4fv(color_amb_location, 1, (const GLfloat*)ColorAmb);
                glUniform4fv(luz_color_location, 1, (const GLfloat*)elcolor);

                */
                glBindVertexArray(VAO_satelite);

            }



            glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);

        }


        
           

            

        
    
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------


      glDeleteVertexArrays(1, &VAO_esfera);
      glDeleteBuffers(1,      &VBO_esfera);
      glDeleteBuffers(1,      &EBO_esfera);

      glDeleteVertexArrays(1, &VAO_esfera2);
      glDeleteBuffers(1, &VBO_esfera2);
      glDeleteBuffers(1, &EBO_esfera2);

      glDeleteVertexArrays(1, &VAO_satelite);
      glDeleteBuffers(1, &VBO_satelite);
      glDeleteBuffers(1, &EBO_satelite);


    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
 // adjust accordingly


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    
   
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        eye[2] -= cameraSpeed * cameraFront[1]/20; // *target[2];
        cout << "Eye[2]: " << eye[2] << endl;
        //cout << "Target[2]: " << target[2] << endl;
    }
       
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
       // cout << "Click en W" << endl;
        eye[2] += cameraSpeed * cameraFront[1]/20; //* target[2];
        cout << "Eye[2]: " << eye[2] << endl;

    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        eye[0] += cameraSpeed * cameraFront[1]/20; // *target[2];
        cout << "Eye[2]: " << eye[0] << endl;
        //cout << "Target[2]: " << target[2] << endl;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // cout << "Click en W" << endl;
        eye[0] -= cameraSpeed * cameraFront[1]/20; //* target[2];
        cout << "Eye[2]: " << eye[0] << endl;

    }

    
    
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    cout << "XPos: " << xpos << " YPos: " << ypos << endl;
}











// glfw: whenever the window size ch
// anged (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

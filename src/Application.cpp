/* OpenGl */
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

/* Atributes */
#include "Atributes.h"

/* UI */
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

/* STREAM */
//for raise(SIGTRAP) function in gcc - instead of __debugbreak()
#include <signal.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/* CLASSES */
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Grid.h"

/* Math */
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtx/intersect.hpp"


/* Sketcher */
grid::Buffer B;


Atributes atr;
float width = atr.rows;
float height = atr.colums;


int SCREEN_WIDTH = atr.ScreenWidth;
int SCREEN_HEIGHT = atr.ScreenHeight;


float ColorClick = 1.f;

double MouseXpos, MouseYpos, MouseXpos2, MouseYpos2, MouseXposGreda, MouseYposGreda, msX, msY, MouseXposDoor, MouseYposDoor;
int brojacRKlik,brojacLKlik, brojacZid, brojacStub, brojacGreda, brojacEraser, brojacDoor;
int trackerCount, trackerGredaCount, roolerCount;
int memoryCount, memoryCount2, MemoryGredaCount, MemoryEraserCount, MemoryDoorCount;

float VALUE_COUNT;

int scroolback_flag;
int *sf = &scroolback_flag;
int element ;
bool lbutton_down;


unsigned int side = 1;
unsigned int mirror = 1;

//////////////////////////////////////////////////////////////
////////////////////// RE-HASHING //////////////////////////////
//////////////////////////////////////////////////////////////
#define MAX_NAME 256
#define TABLE_SIZE 36
#define DELETED_NODE (column*)(0xFFFFFFFFFFFFFFFFUL)
#define DELETED_NODE2 (field*)(0xFFFFFFFFFFFFFFFFUL)


typedef struct 
{
    double msX;
    double msY;

    char id [ MAX_NAME ];
    char material [ MAX_NAME ];

    int POS;
    // float  color;
    //....add other stuff here
} field;


typedef struct
{
    char name [MAX_NAME];
    char obradaPoda [MAX_NAME];//ovdje bi trebao hechove da ubacujes
    float area;
}room;

field* hash_id_table[TABLE_SIZE];




unsigned int hash_id(double msX, double msY)//mogao bi ovo prije da izracunas da isto prima id kao parametar da bi mogao da 
{    
    unsigned int hash_id_value;

    double celijaX = SCREEN_WIDTH/width;      
    double celijaY = SCREEN_HEIGHT/height;

    double  Ix = msX/celijaX;//treba da zaokruzis ovo na donju
    double res1;
    res1 = floor (Ix);

    double  Iy = (SCREEN_HEIGHT - msY)/celijaY;//treba da zaokruzis ovo na donju
    double  res2;
    res2 = floor (Iy);

    unsigned int id= res1 + res2*width;//prvi indeks. Donji lijevi

    hash_id_value = id;

    return hash_id_value;
}


void init_hash_id_table() 
{
    for (int i=0; i<TABLE_SIZE; i++){
        hash_id_table[i] = NULL; //postavio si sve pointere na nulu
    }
    //table is empty
}


void print_id_table() 
{
    std::cout<<"start"<<std::endl;
    for (int i=0; i< TABLE_SIZE; i++) 
    {
      if (hash_id_table[i]==NULL)
      {
         std::cout<<i<<"-----"<<std::endl;

      } else if (hash_id_table[i] == DELETED_NODE2){
          std::cout<<i<<"---<deleted>"<<std::endl;
      } else {
          std::cout<<i<<hash_id_table[i]->id<<std::endl;
      }
    }
    std::cout<<"End"<<std::endl;

} 

bool hash_table_id_insert(field *f)
{
  if (f == NULL) return false;
  int index = hash_id( f->msX, f->msY);//ovde moraju ici dva double elementa (pozicije misa) da on izracuna na osnovu toga index
  if(hash_id_table[index] != NULL)
  {
      return false;
  }
  hash_id_table[index] = f;
  return true;
}

/* //find an element in the table by their name
column *hash_table_lookup ( char const *id2 )
{
    int index = hash(id2);
    for (int i=0; i< TABLE_SIZE; i++)
    {
        int put = (index + i) % TABLE_SIZE;
        if (hash_table[put] == NULL)
        {
            return NULL; //not here`
        }
        if(hash_table[put] == DELETED_NODE) return NULL;
        if (hash_table[put]!=NULL && strncmp (hash_table[index] ->id2, id2, TABLE_SIZE)==0)
        {
            return hash_table[put];
        }
    }
    return NULL;
} */


/* insert */
/* lookup */
/* delete */




//////////////////////////////////////////////////////////////
////////////////////// FUNKCIJE //////////////////////////////
//////////////////////////////////////////////////////////////


void cursorPositionCallback ( GLFWwindow *window, double xPos, double yPos)
{
    // std::cout<< xPos << "   :   " << yPos << std::endl;
}


void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
    glViewport(0, 0, fbW, fbH);
}

/* Escape button for terminateing the window */
void updateInput(GLFWwindow* window)
{

    //    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//////////KRAJ
    //    {
    //          glfwTerminate();    

    //    }

    if (glfwGetKey(window, GLFW_KEY_1 ) == GLFW_PRESS){ side = 1; mirror = 1; }
    else if (glfwGetKey(window, GLFW_KEY_2 ) == GLFW_PRESS){ side = 1; mirror = 2; }
    else if (glfwGetKey(window, GLFW_KEY_3 ) == GLFW_PRESS){ side = 2; mirror = 1; }
    else if (glfwGetKey(window, GLFW_KEY_4 ) == GLFW_PRESS){ side = 2; mirror = 2; }
    else if (glfwGetKey(window, GLFW_KEY_5 ) == GLFW_PRESS){ side = 3; mirror = 1; }
    else if (glfwGetKey(window, GLFW_KEY_6 ) == GLFW_PRESS){ side = 3; mirror = 2; }
    else if (glfwGetKey(window, GLFW_KEY_7 ) == GLFW_PRESS){ side = 4; mirror = 1; }
    else if (glfwGetKey(window, GLFW_KEY_8 ) == GLFW_PRESS){ side = 4; mirror = 2; }




}

/* On click comands */
void mouseButtonCallback ( GLFWwindow *window, int button, int action, int mods)
{

    /* 
    element 0 je element
    element 1 je stub
    element 2 je greda - zid
    element 3 je gumica
    element 4 je vrata

     */

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
    brojacLKlik +=1;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        brojacRKlik+=1;
        lbutton_down = true;



        if(element == 0){//element
            
        VALUE_COUNT +=0.25f;

        brojacZid += 1;
        glfwGetCursorPos(window, &MouseXpos, &MouseYpos);
    
        }else if(element == 1){//stub
            
        VALUE_COUNT +=1.f;

        brojacStub += 1;
        glfwGetCursorPos(window, &MouseXpos2, &MouseYpos2);

        }else if( element ==2 ){//zid

        VALUE_COUNT +=0.75f;
        brojacGreda +=1;
        glfwGetCursorPos(window, &MouseXposGreda, &MouseYposGreda);

        }else if ( element ==3){//gumica

            VALUE_COUNT -=1.f;            

            brojacEraser +=1;
            glfwGetCursorPos(window, &MouseXposGreda, &MouseYposGreda);

        }else if (element == 4){//vrata

            VALUE_COUNT -=0.5f;

            brojacDoor +=1;
            glfwGetCursorPos(window, &MouseXposDoor, &MouseYposDoor);

        }
        
        ColorClick = 1.0f;
    }

    else if( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE )
    {
        lbutton_down = false;
        glfwGetCursorPos(window, &msX, &msY);

        field edge = { msX, msY, "  test", "celik", 1};//trebao bi na klik da ovo radis

        hash_table_id_insert(&edge);
        // print_id_table();
    }       

}

/* Scroll comands */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset > 0)
    {
          
     *sf = 0;
	// std::cout << tt << std::endl;
    }
	else{
    *sf = 1;   

	// std::cout << tt << std::endl;
    }
    
}

/* Meny bar */
static void ShowExampleAppMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}


//////////////////////////////////////////////////////////////
////////////////////// HASHING //////////////////////////////
//////////////////////////////////////////////////////////////



// typedef struct 
// {
//     char id2 [ MAX_NAME ];
//     // char material [ MAX_NAME ];

//     int POS2;
//     // float  color;
//     //....add other stuff here
// } column;


// column* hash_table[TABLE_SIZE];


// unsigned int hash( char const *id2)
// {
//     int lenght = strnlen (id2, MAX_NAME);
//     unsigned int hash_value = 0;
//     for (int i=0; i<lenght; i++)
//     {
//         hash_value +=id2[i];
//         hash_value = (hash_value * id2[i]) % TABLE_SIZE;
//     }
//     return hash_value;
// }



// void init_hash_table() 
// {
//     for (int i=0; i<TABLE_SIZE; i++){
//         hash_table[i] = NULL; //postavio si sve pointere na nulu
//     }
//     //table is empty
// }


// void print_table() 
// {
//     std::cout<<"start"<<std::endl;
//     for (int i=0; i< TABLE_SIZE; i++) 
//     {
//       if (hash_table[i]==NULL)
//       {
//          std::cout<<i<<"-----"<<std::endl;

//       } else if (hash_table[i] == DELETED_NODE){
//           std::cout<<i<<"---<deleted>"<<std::endl;
//       } else {
//           std::cout<<i<<hash_table[i]->id2<<std::endl;
//       }
//     }
//     std::cout<<"End"<<std::endl;

// } 

// bool hash_table_insert(column *c)
// {
//     if (c==NULL) return false;
//     int index = hash (c->id2);
//     for (int i=0; i< TABLE_SIZE; i++)
//     {
        
//         int put = (i+ index) % TABLE_SIZE;
//         if (hash_table[put] == NULL || hash_table[put] == DELETED_NODE)
//         {
//             hash_table[put] = c;
//             return true;
//         }
//     }

//     return true;
// }

//find an element in the table by their name
// column *hash_table_lookup ( char const *id2 )
// {
//     int index = hash(id2);
//     for (int i=0; i< TABLE_SIZE; i++)
//     {
//         int put = (index + i) % TABLE_SIZE;
//         if (hash_table[put] == NULL)
//         {
//             return NULL; //not here`
//         }
//         if(hash_table[put] == DELETED_NODE) return NULL;
//         if (hash_table[put]!=NULL && strncmp (hash_table[index] ->id2, id2, TABLE_SIZE)==0)
//         {
//             return hash_table[put];
//         }
//     }
//     return NULL;
// }



/* Main function */
int main (void)
{

    /* Hash */
    init_hash_id_table();


    int frameBufferWidth = 0;
    int frameBufferHeight = 0;

    /* Setting up OpenGL and GLFW */
    GLFWwindow* window;


    if (!glfwInit())
        return -1;

    

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// GLFW_OPENGL_CORE_PROFILE  GLFW_OPENGL_COMPAT_PROFILE 


    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sketcher", NULL, NULL);


    if(!window)
    {
        glfwTerminate();
        return -1;
    }


    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    // glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    



    glfwMakeContextCurrent(window);

    glfwSwapInterval(0.5);


    GLenum err1 = glewInit();
    if (GLEW_OK != err1)
    {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err1));    
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout, "Status: Using GL %s\n", glGetString(GL_VERSION));   

    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetMouseButtonCallback ( window, mouseButtonCallback );
    glfwSetScrollCallback(window, scroll_callback);
    //=======================================================================
    //=======================================================================
    //=======================================================================

    /* Important stuf */
 {

    //===========  BATCHED POSITIONS =======================


    /* Setting up the Batch coordinates */

    //verteksi
    int countVertexXYZ = atr.countCoordinatesXYZ;
    int countVertexXYZ_RGBA = atr.countAllXYZ;

    float* verteksi2 = new float[countVertexXYZ];
    float* verteksiAll = new float[countVertexXYZ_RGBA];


    B.VertexBuffer_XYZ( verteksi2);
    B.VertexBuffer_XYZ_RGBA (verteksiAll);

    //=============== INDECIES =============================

    /* Wires indecies */
    std::vector <unsigned int> indeksi;
    B.IndexBufferWires( indeksi );

    //pretvaras vektor u array
    int countIndeks = atr.countIndeks;
    unsigned int* indeksiNiz = new unsigned int [countIndeks];
    indeksiNiz = &indeksi[0];

    //==========
    /*Secundary Wires indecies */
    std::vector<unsigned int> wiresSecundaryVector;
    B.IndexBufferWiresSecundary (wiresSecundaryVector);

    //pretvaras vektor u array
    int wiresSecundaryCount =atr.countWiresSecundaryIndeks;//ovo da izracunas
    unsigned int* wiresSecundaryArray = new unsigned int [wiresSecundaryCount];
    wiresSecundaryArray = &wiresSecundaryVector[0];

    /* Indeksi koji se memorisu. 1 i 2 zato sto imas dva aktivna elementa 1x1 i 2x2 */
    //Nemam pojma zasto radi kad mu nisam definisao koliko je count
   
    

    unsigned int* Memory = new unsigned int [ 100+memoryCount ];//stub
    unsigned int* Memory2 = new unsigned int [ 100 + memoryCount2 ];//prozor
    unsigned int* MemoryGreda = new unsigned int [ 100+MemoryGredaCount];//greda-zid
    unsigned int* MemoryDoor = new unsigned int [MemoryDoorCount];//vrata
    unsigned int* MemoryEraser = new unsigned int [100 + MemoryEraserCount];//gumica

   


    //=============== LAYOUT =========================


    // GLCall(glEnable(GL_BLEND));
    // GLCall(glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)  );


    /* Vertex array layout */
    VertexArray va;
    VertexBuffer vb(verteksi2, countVertexXYZ * 3 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);


    /* Index arrays */
    IndexBuffer ib_Wires(indeksiNiz, countIndeks);
    IndexBuffer ib_WiresSecundary(wiresSecundaryArray, wiresSecundaryCount);


    //=============== CAMERA =========================

    /* Matrices   */
    glm::mat4 proj  = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
    // glm::mat4 view  = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    // bool glm::intersectRayTriangle( orig, );

    
    // glm::intersectRayTriangle(ve3orig, vec3dir,vec3vert0,vec3vert1,vec3vert2,vec2baryPosition,distance)
    

    //=============== SHADERS =========================


    /* Shader for wires */
    Shader shaderWires("../res/shaders/Basic2.shader");
    shaderWires.Bind();
    shaderWires.SetUniform4f("u_Color",0.2f, 0.2f, 0.2f, 0.15f );

    /* Shader for secundary wires  */
    Shader shaderWiresSecundary("../res/shaders/Basic2.shader");
    shaderWiresSecundary.Bind();
    shaderWiresSecundary.SetUniform4f("u_Color",0.2f, 0.2f, 0.f, 0.2f);

     /* Shader for tracker */
    Shader shaderTracker("../res/shaders/Basic2.shader");
    shaderTracker.Bind();

      /* Shader for tracker 2 */
    Shader shaderTracker2("../res/shaders/Basic2.shader");
    shaderTracker2.Bind();

    /* Shader za tracker Grede */
    Shader shaderTrackerGreda("../res/shaders/Basic2.shader");
    shaderTrackerGreda.Bind();

    /* Shader for Memory */
    Shader shaderElement("../res/shaders/Basic2.shader");
    shaderElement.Bind();
    shaderElement.SetUniform4f("u_Color",0.5f, 0.8f, 0.5f, 0.7f );

    /* Shader for Memory 2 */
    Shader shaderColumn("../res/shaders/Basic2.shader");
    shaderColumn.Bind();
    shaderColumn.SetUniform4f( "u_Color",0.2f, 0.4f, 0.6f, 0.7f );

    /* Shader for Memory greda */
    Shader shaderGreda( "../res/shaders/Basic2.shader" );
    shaderGreda.Bind();
    shaderGreda.SetUniform4f( "u_Color",0.2f, 0.4f, 0.6f, 0.7f );

    /* Shader for Memory Eraser */
    Shader shaderEraser( "../res/shaders/Basic2.shader" );
    shaderEraser.Bind();
    shaderEraser.SetUniform4f( "u_Color",0.2f, 0.4f, 0.6f, 0.7f );//zelena

    /* Shader for Memory Door */
    Shader shaderDoor ( "../res/shaders/Basic2.shader"  );
    shaderDoor.Bind();


    //=============== UNBIND =========================

    va.Unbind();
    vb.Unbind();
    ib_Wires.Unbind();
    ib_WiresSecundary.Unbind();

    shaderWires.Unbind();
    shaderWiresSecundary.Unbind();
    

    shaderElement.Unbind();
    shaderColumn.Unbind();
    shaderGreda.Unbind();
    shaderEraser.Unbind();
    shaderDoor.Unbind();

    shaderTracker.Unbind();
    shaderTracker2.Unbind();
    shaderTrackerGreda.Unbind();
    

    Renderer renderer;

    //=============== IMGUI =========================

    /* Setup Dear ImGui context */     
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; 
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();


    //flags for trigerring imGui 
    bool show_another_window = true;
    bool show_demo_window = true;

    bool primarniGrid   = true;
    bool sekundarniGrid = false;
    bool constructionAxis = false;


    bool coloredMatrix = true;
    bool valueMatrix = false;

    bool Table = false;


    static bool show_app_main_menu_bar = true;





    //====================================================
    //=============== WHILE LOOP =========================
    //====================================================

    while(!glfwWindowShouldClose(window))
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.Clear();
        

       
        ImGui_ImplGlfw_NewFrame();  
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();           

        //===========================================================
        /* BLOK KODA ZA INTERAKCIJU */
        //===========================================================


        /* Playground */
        {

            GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));// GL_FRONT, GL_FRONT_AND_BACK...  GL_FILL  GL_LINE  GL_POINT            
            /* Mouse position */
            double mouseX, mouseY;
            /* Detektujes mis za tracker */
            glfwGetCursorPos(window, &mouseX, &mouseY);   

            /* test for out of screen  */
            if(mouseX<=0 || mouseY<=0 || mouseX>=atr.ScreenWidth || mouseY>=atr.ScreenHeight)
            {
            mouseX = 2;
            mouseY = 2;
            }


            trackerCount = 6;
            trackerGredaCount = 6;
            roolerCount = 2;


            memoryCount = brojacZid*6;
            memoryCount2 = brojacStub*6;
            MemoryGredaCount = brojacGreda*6;
            MemoryEraserCount = brojacEraser*6;
            MemoryDoorCount = brojacDoor*3;
            

         //=========================================================
         //================ ODABIR ELEMENTA ZA TRAKER ===============
         //=========================================================
         

            if( element == 0)//element
            {
            
            //Tracker
            unsigned int* Tracker = new unsigned int [trackerCount];
            // unsigned in* Rooler = new unsigned int [roolerCount];

            B.IndexBufferElement(mouseX, mouseY, Tracker);
            IndexBuffer ib_Tracker (Tracker, trackerCount);
            // IndexBuffer ib_Rooler (Rooler, roolerCount);


            /* Ovo je shader za tracker */
            shaderTracker.Bind();
            shaderTracker.SetUniform4f("u_Color",ColorClick, 1.f, 0.5f, 0.5f );
            shaderTracker.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_Tracker, shaderTracker);  

            // renderer.DrawLines(va, ib_Rooler, shaderTracker);

            shaderTracker.Unbind();
            delete[] Tracker;
            // delete[] Rooler;

            }
            else if(element == 1)//column
            {   

            //Tracker II
            /* uslov za izuzetak na desnom i gornjem kraju ekrana */
            if( mouseX >= atr.ScreenWidth - atr.ScreenWidth/ atr.rows || mouseY <= atr.ScreenHeight/ atr.colums  )
               {
                mouseX = mouseX - atr.ScreenWidth / atr.rows;
                mouseY = mouseY + atr.ScreenHeight / atr.colums;
               }


            unsigned int* Tracker2 = new unsigned int [trackerCount];
            B.IndexBufferElement2(mouseX, mouseY, Tracker2);
            IndexBuffer ib_Tracker2(Tracker2, trackerCount);


              /* Ovo je shader za tracker 2 */
            shaderTracker2.Bind();
            shaderTracker2.SetUniform4f("u_Color",ColorClick, 1.f, 0.5f, 0.5f );
            shaderTracker2.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_Tracker2, shaderTracker2);        
          
        
            shaderTracker2.Unbind();
            delete[] Tracker2;
            }
            else if (element == 2)//wall
            {
                //Tracker
                unsigned int* Tracker = new unsigned int [trackerCount];

                B.IndexBufferElement(mouseX, mouseY, Tracker);
                IndexBuffer ib_Tracker (Tracker, trackerCount);

                /* Ovo je shader za tracker */
                shaderTracker.Bind();
                shaderTracker.SetUniform4f("u_Color",ColorClick, 1.f, 0.5f, 0.5f );
                shaderTracker.SetUniformMat4f("u_MVP", proj);
                renderer.Draw(va, ib_Tracker, shaderTracker);  

                shaderTracker.Unbind();
                delete[] Tracker;       
            }else if (element == 3){/* prozor */

            unsigned int* Tracker = new unsigned int [trackerCount];

            B.IndexBufferElement(mouseX, mouseY, Tracker);
            IndexBuffer ib_Tracker (Tracker, trackerCount);

            /* Ovo je shader za tracker */
            shaderTracker.Bind();
            shaderTracker.SetUniform4f("u_Color",ColorClick, 1.f, 0.5f, 0.5f );
            shaderTracker.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_Tracker, shaderTracker);  

            shaderTracker.Unbind();
            delete[] Tracker;   

            }else if (element == 4){

            /* vrata */
            //ovo ti je dio koda za tacker
            unsigned int* Tracker = new unsigned int [trackerCount];

            B.IndexBufferElement(mouseX, mouseY, Tracker);
            IndexBuffer ib_Tracker (Tracker, trackerCount);

            /* Ovo je shader za tracker */
            shaderTracker.Bind();
            shaderTracker.SetUniform4f("u_Color",ColorClick, 1.f, 0.5f, 0.5f );
            shaderTracker.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_Tracker, shaderTracker);  

            shaderTracker.Unbind();
            delete[] Tracker;   
            }
  
         //================ PUNJENJE MEMORIJE - ide po prioritetu ===============

            /* uslov za izuzetak na desnom i gornjem kraju ekrana */
            if( MouseXpos2 >= atr.ScreenWidth - atr.ScreenWidth/ atr.rows ||  MouseYpos2 <= atr.ScreenHeight/ atr.colums )
               {
                MouseXpos2 = MouseXpos2 - atr.ScreenWidth / atr.rows;
                MouseYpos2 = MouseYpos2 + atr.ScreenHeight / atr.colums;
               }

            //Greda--> ZID
            if(lbutton_down && element == 2)
            {
            B.IndexBufferGreda(MouseXposGreda,MouseYposGreda, mouseX,mouseY, brojacGreda, MemoryGreda);
            }
            IndexBuffer ib_MemoryGreda(MemoryGreda,MemoryGredaCount); 

            //Element
            B.IndexBufferMemory (MouseXpos,MouseYpos, brojacZid, Memory);   
            IndexBuffer ib_Memory (Memory, memoryCount);

            //Stub
            B.IndexBufferMemory2 (MouseXpos2,MouseYpos2, brojacStub, Memory2);  
            IndexBuffer ib_Memory2 (Memory2, memoryCount2);

            //Vrata
            B.IndexBufferDoor(MouseXposDoor, MouseYposDoor, brojacDoor, side, mirror, MemoryDoor);
            IndexBuffer ib_MemoryDoor ( MemoryDoor, MemoryDoorCount);

      

            // IndexBuffer ib_Wires(indeksiNiz, countIndeks);

            //Gumica
            if(lbutton_down && element == 3)
            {
            B.IndexBufferGreda(MouseXposGreda,MouseYposGreda, mouseX,mouseY, brojacEraser, MemoryEraser);
            }
            IndexBuffer ib_MemoryEraser( MemoryEraser, MemoryEraserCount);


        //============== ISCRTAVANJE ====================================

            /* Ovo je shader za memoriju grede -->zida (jer ona moze preko stuba) */ 
            shaderGreda.Bind();
            shaderGreda.SetUniform4f( "u_Color",ColorClick, 1.f, 1.f, 1.f );
            shaderGreda.SetUniformMat4f( "u_MVP", proj );
            renderer.Draw (va, ib_MemoryGreda, shaderGreda);            
            shaderGreda.Unbind();

             /* Ovo je shader za memoriju  - aka element */           
            shaderElement.Bind();
            shaderElement.SetUniform4f("u_Color",ColorClick, 0.6f, 0.f, 1.f );
            shaderElement.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_Memory, shaderElement); 
            shaderElement.Unbind();

            /*  Ovo je shsder za vrata */
            shaderDoor.Bind();
            shaderDoor.SetUniform4f("u_Color",ColorClick, 0.3f, 1.f, 0.1f );
            shaderDoor.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_MemoryDoor, shaderDoor); 
            shaderDoor.Unbind();



             /* Ovo je shader za memoriju 2 - aka stub */
            shaderColumn.Bind();
            shaderColumn.SetUniform4f("u_Color",ColorClick, 0.f, 0.f, 1.f );
            shaderColumn.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_Memory2, shaderColumn);  
            shaderColumn.Unbind();

             /* Ovo je shader za Eraser 2 - aka gumica */
            shaderEraser.Bind();
            shaderEraser.SetUniform4f("u_Color", 0.f, 1.f, 0.f, 0.f );
            shaderEraser.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_MemoryEraser, shaderEraser); 
            shaderEraser.Unbind();


            //============================================
            /* ovdje ce ti doci vrata jer 
            vrata mogu preko zida ali ne mogu preko stuba */
            //============================================

        }

        if(sekundarniGrid)
        {
            GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));// GL_FRONT, GL_FRONT_AND_BACK...  GL_FILL  GL_LINE  GL_POINT
            shaderWires.Bind();
            shaderWires.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_Wires, shaderWires);      
            shaderWires.Unbind();
        }

        if(primarniGrid)
        {
            GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));// GL_FRONT, GL_FRONT_AND_BACK...  GL_FILL  GL_LINE  GL_POINT
            shaderWiresSecundary.Bind();
            shaderWiresSecundary.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_WiresSecundary, shaderWiresSecundary);      
            shaderWiresSecundary.Unbind();            

        }


        /* ImGui UI */
        if( show_another_window)
        {
            

            ImGui::Begin("OPTIONS");    
            // if (show_app_main_menu_bar)       ShowExampleAppMainMenuBar();
            //if buttn onda nesto    

            ImGui::RadioButton("Element", &element, 0); ImGui::SameLine();
            ImGui::RadioButton("Column", &element, 1); ImGui::SameLine();
            ImGui::RadioButton("Wall", &element, 2);
            
        ImGui::Separator();

            ImGui::RadioButton("Window", &element, 3); ImGui::SameLine();
            ImGui::RadioButton("Door", &element, 4); 

            ImGui::RadioButton("Elevation", &element, 5); ImGui::SameLine();
            // ImGui::RadioButton("Lift", &element, 6); 

        ImGui::Separator();


            // ImGui::RadioButton("Kuhinjski Sto", &element, 7); ImGui::SameLine();
            // ImGui::RadioButton("Stolica", &element, 8); ImGui::SameLine();
            // ImGui::RadioButton("Kuhinjski Element", &element, 9); 

            // ImGui::RadioButton("Trosjed", &element, 10);ImGui::SameLine();
            // ImGui::RadioButton("Dvosjed", &element, 11);ImGui::SameLine();
            // ImGui::RadioButton("Fotelja", &element, 12);ImGui::SameLine();
            // ImGui::RadioButton("Klub sto", &element, 13);

            // ImGui::RadioButton("Krevet - Bracni", &element, 14);ImGui::SameLine();
            // ImGui::RadioButton("Krevet - Djeciji", &element, 15);ImGui::SameLine();
            // ImGui::RadioButton("Plakar", &element, 16);ImGui::SameLine();
            // ImGui::RadioButton("Radni sto", &element, 17);


        ImGui::Separator();

            // ImGui::RadioButton("Eraser", &element, 3); 

         
        /*     {
            const char* items[] = { "Element", "Column", "Wall", "Otvor", "Vrata", "Prozor", "Stepenice", "Stolica", "Lift", "Kuhinjski Sto", "Stolica","Kuhinjski Element", 
            "Trosjed", "Dvosjed","Fotelja","Klub sto", "Krevet - Bracni", "Krevet - Djeciji", "Plakar", "Radni sto" };
            static int item_current = 0;
            ImGui::Combo("Leyers", &item_current, items, IM_ARRAYSIZE(items));
            // ImGui::SameLine(); HelpMarker("Refer to the \"Combo\" section below for an explanation of the full BeginCombo/EndCombo API, and demonstration of various flags.\n");
            }
         */

        ImGui::Separator();
                   
            ImGui::Checkbox("Primary Grid", &primarniGrid); ImGui::SameLine();
            ImGui::Checkbox("Secondary Grid", &sekundarniGrid);ImGui::SameLine();
            ImGui::Checkbox("Construction axis", &constructionAxis);
        ImGui::Separator();
            ImGui::Checkbox("Value matrix",   &valueMatrix); ImGui::SameLine();
            ImGui::Checkbox("Colored matrix", &coloredMatrix); 

            
        ImGui::Separator();
        ImGui::Separator();

            static int clicked = 0;
            if(ImGui::Button("Reset"))
            clicked++;
            if(clicked & 1)
            {
            ImGui::SameLine();
            ImGui::Text("Hit me one more time!");

    


            brojacZid = 0;
            brojacStub = 0;
            brojacGreda = 0;
            brojacEraser = 0;
            brojacDoor = 0;
            }

            static int save = 0;
            if(ImGui::Button("Save"))
            save++;
            if(save & 1)
            {
            ImGui::SameLine();
            ImGui::Text("Hit me one more time!");
            }

            static int katalog = 0;
            if(ImGui::Button("Katalog"))
            katalog++;
            if(katalog & 1)
            {
            ImGui::SameLine();
            ImGui::Text("Hit me one more time!");
            }


        ImGui::Separator();   
           
            double gx;
            double gy;
            glfwGetCursorPos(window, &gx, &gy);   
            ImGui::Text("Mouse pos: (%g, %g)", gx, gy);
            ImGui::Text("Scroolback flag: (%i) ", *sf);
            ImGui::Text("Left click count : (%i) ",brojacLKlik );
            ImGui::Text("right click count: (%i) ",brojacRKlik );
            ImGui::Text("Indeks mapped: (%i, %i, %i, %i) ",hash_id(gx,gy),hash_id(gx,gy),hash_id(gx,gy),hash_id(gx,gy) );
            
            ImGui::Text("Value counter: (%g)", VALUE_COUNT);


        ImGui::Separator();   

            // hash_id(gx,gy);
            ImGui::Text("ID: (%i)", hash_id(gx,gy));
            ImGui::Text("Value: ");
            ImGui::Text("Type: ");
            ImGui::Text("Material: ");
            ImGui::Text("POS: "); 


        ImGui::Separator();
        ImGui::Separator();
          ImGui::Text("Ubaci tabelu ovdje: "); 

            /*    
             static int hide = 0;
            if(ImGui::Button("hide"))
            hide++;
            if(hide & 1)
            {
            // renderer.Clear();            
            } */

            // ImGui::ShowDemoWindow(&show_demo_window);

            ImGui::End();
  
        }

    
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());    

        updateInput(window);//ovo ti je funkcija za tastaturu koja pravi core dumped.
        // Nastaje zato sto zatvoris prozor a ostane neizbrisan delta time u imguiu. Mora ovdje jer prima window kontekst. Dolje ne moze jer nema konteksta.
        glfwSwapBuffers(window);
        glfwPollEvents();        


    }

    delete[] indeksiNiz;
    delete[] wiresSecundaryArray;
    delete[] verteksiAll;
    delete[] verteksi2;

    delete[] Memory;
    delete[] Memory2;
    delete[] MemoryGreda;
    delete[] MemoryEraser;
    delete[] MemoryDoor;
    
 }
    ImGui_ImplGlfw_Shutdown();   
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();    
    glfwTerminate();

    return 0;

}


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

grid::Buffer B;


float ColorClick = 1.f;

int brojacZid = 0;
int brojacStub = 0;
int brojacGreda = 0;
int brojacEraser = 0;

double MouseXpos, MouseYpos, MouseXpos2, MouseYpos2, MouseXposGreda, MouseYposGreda;
int tt = 0;
int trackerCount, trackerGredaCount, roolerCount;
int element = 0;
int memoryCount, memoryCount2, MemoryGredaCount, MemoryEraserCount;

bool lbutton_down;


void cursorPositionCallback ( GLFWwindow *window, double xPos, double yPos)
{
    std::cout<< xPos << "   :   " << yPos << std::endl;
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

}

/* On click comands */
void mouseButtonCallback ( GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // ColorClick = 1.0f;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {

        if(element == 0)
        {

        brojacZid += 1;
        glfwGetCursorPos(window, &MouseXpos, &MouseYpos);

        }else if(element == 1)
        {

        brojacStub += 1;
        glfwGetCursorPos(window, &MouseXpos2, &MouseYpos2);

        }else if( element ==2)
        {

        brojacGreda +=1;
        glfwGetCursorPos(window, &MouseXposGreda, &MouseYposGreda);
        lbutton_down = true;

        }else if ( element ==3){
            brojacEraser +=1;
            glfwGetCursorPos(window, &MouseXposGreda, &MouseYposGreda);
            lbutton_down = true;
        }


        // std::cout<<brojac<<std::endl;
        ColorClick = 1.0f;
    }

    else if( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE )
    {
        lbutton_down = false;
    }




   

        

}

/* Mislim da se ne koristi nigdje ali neka ga za sada */
void mouseButtonCallback2 ( GLFWwindow *window, int button, int action, int mods)
{
     if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // ColorClick = 1.0f;
   
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &MouseXpos, &MouseYpos);
        if(element == 0)
        {

        brojacZid += 1;
        }else if(element == 1)
        {

        brojacStub += 1;
        }

        // std::cout<<brojac<<std::endl;
        ColorClick = 1.0f;

    }
}

/* Scroll comands */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset > 0)
    {
          
     tt = 0;
	// std::cout << tt << std::endl;
    }
	else{
    tt = 1;   

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

/* Main function */
int main (void)
{
    Atributes atr;
    // grid::Buffer B;
    float width = atr.rows;
    float height = atr.colums;



    int SCREEN_WIDTH = atr.ScreenWidth;
    int SCREEN_HEIGHT = atr.ScreenHeight;

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
   
    

    unsigned int* Memory = new unsigned int [4000 + memoryCount ];//MemoryCount
    unsigned int* Memory2 = new unsigned int [4000 + memoryCount2 ];//MemoryCount
    unsigned int* MemoryGreda = new unsigned int [400 + MemoryGredaCount];
    unsigned int* MemoryEraser = new unsigned int [100 + MemoryEraserCount];

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
    shaderEraser.SetUniform4f( "u_Color",0.2f, 0.4f, 0.6f, 0.7f );

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

    bool stub = false;


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

         
         //================ ODABIR ELEMENTA ZA TRAKER ===============

            if( element == 0)
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
            else if(element == 1)
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
            else if (element == 2)
            {
                //Greda
                
                // unsigned int* TrackerGreda = new unsigned int [trackerGredaCount];

                // if(lbutton_down)
                // B.IndexBufferElement3 (MouseXposGreda, MouseYposGreda, mouseX, mouseY, TrackerGreda);

                // IndexBuffer ib_TrackerGreda(TrackerGreda,trackerGredaCount);

                // /* Ovo je shader za tracker grede */
                // shaderTrackerGreda.Bind();
                // shaderTrackerGreda.SetUniform4f( "u_Color",ColorClick, 1.f, 0.5f, 0.5f );
                // shaderTrackerGreda.SetUniformMat4f("u_MVP", proj);
                // renderer.Draw (va, ib_TrackerGreda, shaderTrackerGreda);

                // shaderTrackerGreda.Unbind();
                // delete[] TrackerGreda; 
                            
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
            }
            else if (element == 3)
            {
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

         //================ USLOV ZA VUCENJE MISA ===============
            std::cout<<lbutton_down<<std::endl;


         //================ PUNJENJE MEMORIJE - ide po prioritetu ===============

            /* uslov za izuzetak na desnom i gornjem kraju ekrana */
            if( MouseXpos2 >= atr.ScreenWidth - atr.ScreenWidth/ atr.rows ||  MouseYpos2 <= atr.ScreenHeight/ atr.colums )
               {
                MouseXpos2 = MouseXpos2 - atr.ScreenWidth / atr.rows;
                MouseYpos2 = MouseYpos2 + atr.ScreenHeight / atr.colums;
               }

            //Greda
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

            //Gumica
            if(lbutton_down && element == 3)
            {
            B.IndexBufferGreda(MouseXposGreda,MouseYposGreda, mouseX,mouseY, brojacEraser, MemoryEraser);
            }
            IndexBuffer ib_MemoryEraser( MemoryEraser, MemoryEraserCount);



        //============== ISCRTAVANJE ====================================

            /* Ovo je shader za memoriju grede (jer ona moze preko stuba) */ 
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

             /* Ovo je shader za memoriju 2 - aka stub */
            shaderColumn.Bind();
            shaderColumn.SetUniform4f("u_Color",ColorClick, 0.f, 0.f, 1.f );
            shaderColumn.SetUniformMat4f("u_MVP", proj);
            renderer.Draw(va, ib_Memory2, shaderColumn);  
            shaderColumn.Unbind();

             /* Ovo je shader za Eraser 2 - aka stub */
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

            // ImGui::RadioButton("Vrata", &element, 3); ImGui::SameLine();
            // ImGui::RadioButton("Prozor", &element, 4); 

            // ImGui::RadioButton("Stepenice", &element, 5); ImGui::SameLine();
            // ImGui::RadioButton("Lift", &element, 6); 

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

            // ImGui::RadioButton("Eraser", &element, 3); `

         
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
            ImGui::Checkbox("Secondary Grid", &sekundarniGrid);


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
            }

        /*     static int hide = 0;
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
    
 }
    ImGui_ImplGlfw_Shutdown();   
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();    
    glfwTerminate();

    return 0;

}


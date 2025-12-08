#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "engine/graphics/light.hpp"
#include "engine/graphics/lightmanager.hpp"
#include "engine/graphics/mesh.hpp"
#include <ostream>
#include <stb_image/stb_image.h>
#include "engine/graphics/shader.hpp"
#include "engine/graphics/texture.hpp"
#include "engine/graphics/camera.hpp"
#include "glm/ext/matrix_transform.hpp"

const int WIDTH = 1500;
const int HEIGHT = 700;

Engine::Graphics::Camera camera(glm::vec3(-2.0f, 2.0f, 5.0f));
Engine::Graphics::LightManager lightManager;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
bool cursorMode = false;


float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width - 600, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Engine::Graphics::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Engine::Graphics::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Engine::Graphics::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Engine::Graphics::RIGHT, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS){
        cursorMode = !cursorMode;
        std::cout << cursorMode << std::endl;
    }
    if(key == GLFW_KEY_F && action == GLFW_PRESS){
        lightManager.setUseFlashLight(!lightManager.getUseFlashLight());
        if(lightManager.getUseFlashLight()){
            std::cout << "Flashlight ON" << std::endl;
        } else {
            std::cout << "Flashlight OFF" << std::endl;
        }
    }
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
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

    if(!cursorMode) camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    // camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

int main()
{
    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Load GLEW so it configures OpenGL
    glewInit();

    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    // Get actual framebuffer size (handles Retina displays)
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width - 600, height);
    
    //ImGUI setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");
    
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    // Generates Shader object using shaders defualt.vert and default.frag
    Engine::Graphics::Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");
    Engine::Graphics::Shader lightProgram("../shaders/light.vert", "../shaders/light.frag");

    // Textures
    
    shaderProgram.Activate();
    Engine::Graphics::Texture Dirt("../textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Dirt.texUnit(shaderProgram, "material.diffuse", 0);
    Dirt.Bind();
    
    Engine::Graphics::Texture Specular("../textures/specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    Specular.texUnit(shaderProgram, "material.specular", 1);
    Specular.Bind();

    Engine::Graphics::Mesh cubeMesh = Engine::Graphics::Mesh::CreateCube(1.0f, &Dirt);
    Engine::Graphics::Mesh lightCube = Engine::Graphics::Mesh::CreateCube(1.0f);
    
    // Check for OpenGL errors
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error after setup: " << err << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    std::cout << "Starting render loop..." << std::endl;
    std::cout << "Camera position: " << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << std::endl;
    
    const int activePointLight = 4;
    std::vector<glm::vec3> pointLightPositions(activePointLight);
    
    // Directional light properties
    Engine::Graphics::DirectionalLight dirLight(
        glm::vec3(-0.2f, -1.0f, -0.3f),
        glm::vec3(0.05f, 0.05f, 0.05f),
        glm::vec3(0.4f, 0.4f, 0.4f),
        glm::vec3(0.5f, 0.5f, 0.5f)
    );
    lightManager.setDirectionalLight(dirLight);
    
    // Point light properties
    for(size_t i = 0; i < 4; i++){
        Engine::Graphics::PointLight light(
            pointLightPositions[i],
            1.0f,
            0.09f,
            0.032f,
            glm::vec3(0.05f, 0.05f, 0.05f),
            glm::vec3(0.8f, 0.8f, 0.8f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );
        lightManager.addPointLight(light);
    }
    
    // FlashLight properties
    Engine::Graphics::FlashLight flashLight(camera.Position, camera.Front);
    lightManager.setFlashLight(flashLight);

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Synchronising delta between frames for all machines
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        //ImGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        static float cutOff = 0.0f;
        static float outerCutOff = 0.0f;
        
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            // Set up the ImGui window to be a fixed panel on the right
            ImGui::SetNextWindowPos(ImVec2(WIDTH - 300, 0));  // Position at right edge
            ImGui::SetNextWindowSize(ImVec2(300, HEIGHT));     // 300px wide, full height
            
            ImGuiWindowFlags window_flags = 0;
            window_flags |= ImGuiWindowFlags_NoResize;
            window_flags |= ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoCollapse;
            
            ImGui::Begin("Light Settings", nullptr, window_flags);
            ImGui::Checkbox("Use Directional Light", lightManager.setUseDirLight());
            
            for(size_t i = 0; i < lightManager.getPointLightCount(); i++){
                std::string label = "Use Point Light " + std::to_string(i + 1);
                bool tempBool = lightManager.getUsePointLight(i);
                if(ImGui::Checkbox(label.c_str(), &tempBool)){
                    lightManager.setUsePointLight(i, tempBool);
                }
                
            }
            ImGui::SliderFloat("Flash Light Cut Off", &cutOff, 0, 45);
            ImGui::SliderFloat("Flash Light Outer Cut Off", &outerCutOff, 0, 45);
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // TODO: Make Point Light / Directional Light / Flashlight configurable
        
            ImGui::Text("FPS: %.1f", io.Framerate);
            ImGui::End();
        }
        ImGui::Render();
        
        processInput(window);
        // Specify the color of the background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if(cursorMode){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else{
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        // Multiple cube positions;
        std::vector<glm::vec3> cubePositions = {
            glm::vec3(1.2f, 2.8f, -1.5f),
            glm::vec3(-2.3f, 0.9f, 3.1f),
            glm::vec3(3.5f, -1.7f, 2.4f),
            glm::vec3(-3.2f, 3.6f, -0.8f),
            glm::vec3(0.7f, -2.5f, 1.9f),
            glm::vec3(-1.8f, 1.4f, -3.3f),
            glm::vec3(2.9f, -3.1f, 0.6f),
            glm::vec3(-0.5f, 2.2f, -2.7f),
            glm::vec3(1.6f, -0.4f, 3.8f),
            glm::vec3(-2.7f, 3.3f, 1.1f)
        };
        
        shaderProgram.Activate();
        
        shaderProgram.setVec3("lightColor", lightColor);
        shaderProgram.setVec3("viewPos", camera.Position);
        
        // Material properties
        // 
        shaderProgram.setFloat("material.shininess", 16.0f);
        
        
        // Point light positions
        for(size_t i = 0; i < pointLightPositions.size(); i++){
            if(i % 2 == 0){
            float x = 4 * glm::sin(currentFrame +  i * 3.14 / 2);
            pointLightPositions[i] = glm::vec3(x, 0.0, 0.0);
            }
            else{
            float y = 4 * glm::sin(currentFrame +  i * 3.14 / 2);
            pointLightPositions[i] = glm::vec3(0.0, y, 0.0);
            }
        }
        
        for(size_t i = 0; i < pointLightPositions.size(); i++){
            Engine::Graphics::PointLight& pLight = lightManager.setPointLight(i);
            pLight.setPosition(pointLightPositions[i]);
        }
        
        // Update Flashlight
        if(lightManager.getUseFlashLight()){
            Engine::Graphics::FlashLight& fLight = lightManager.setFlashLight();
            fLight.setPosition(camera.Position);
            fLight.setDirection(camera.Front);
            fLight.setCutOff(glm::cos(glm::radians(cutOff)), glm::cos(glm::radians(outerCutOff)));
        }
        
        

        lightManager.applyAll(shaderProgram);

        glm::mat4 proj = glm::mat4(1.0f);

        proj = glm::perspective(glm::radians(camera.GetZoom()), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        glm::mat4 view = camera.GetViewMatrix();

        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("proj", proj);
        
        glm::mat4 model;
        for(int i = 0; i < cubePositions.size(); i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            shaderProgram.setMat4("model", model);
            cubeMesh.Draw(shaderProgram);
        }
        

        lightProgram.Activate();
        lightProgram.setVec3("lightColor", lightColor);
        lightProgram.setMat4("view", view);
        lightProgram.setMat4("proj", proj);
        
        for(int i = 0; i < pointLightPositions.size(); i++){
            if(lightManager.getUsePointLight(i)){
                model = glm::mat4(1.0f);
                model = glm::translate(model, pointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f)); 
                lightProgram.setMat4("model", model);
                lightCube.Draw(lightProgram);
            }
        }

        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the objects we've created
    Dirt.Delete();
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
#include <GLFW/glfw3.h>
#include<iostream>
#include <time.h>
#include <stdio.h>
#include <chrono>
#include <functional>


using namespace std;
#define size 1280
using namespace std;



void first() {
    int array[size];
}

void second() {
    int* array = new int[size];
    delete[] array;
}

void PrintTime(std::chrono::duration<double> elapsed, int count, std::string msg)
{
    std::cout << msg << elapsed.count() / count << " s\n";
}

int main()
{
    int iterations = 1280; //256x256 // 512x512 // 768x768 // 1024x2024 // 1280x1280
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto finish = std::chrono::high_resolution_clock::now();
    
    }
   
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i <= iterations; i++)
        {
            first();
            second();
        }
        auto finish = std::chrono::high_resolution_clock::now();
        PrintTime(finish - start, iterations, "Execution time for 1280x1280 Array with OpenGL: ");

    }
  
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Screen is open", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
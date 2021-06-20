#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Define varias opciones posibles para el movimiento de la cámara.
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Valores default de la camara
const float YAW         = -90.0f; //movimiento inicial de la camara en el eje X
const float PITCH       =  0.0f; //movimiento inicial de la camara en el eje Y
const float SPEED       =  2.5f; //velocidad de la camara al moverse
const float SENSITIVITY =  0.1f; //sensivilidad al responder con un comando
const float ZOOM        =  45.0f; //movimiento de la camara al aplicar un acercamiento


// La clase abstracta de camara que procesa la entrada y calcula los ángulos, vectores y matrices de Euler correspondientes para su uso en OpenGL
class Camera
{
public:
    // Atributos de la camara
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Angulos de Euler
    float Yaw;
    float Pitch;

    // Opciones de la camara
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Constructor con vectores
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Constructor con valores escalares
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Regresa la vista de la matriz usando lookAt
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // procesa los inputs provenientes de cualquier tipo de teclado.
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // procesa el input proveniente al mover el mouse
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        //se asegura de que la camara no se salga de los limites, asi la pantalla no se da vuelta
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // hace un update a la camara
        updateCameraVectors();
    }

    // Procesa el input de la rueda del mouse
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f; 
    }

    private:
    // Calcula los vectores de la camara para actualizar las posiciones y direcciones
    void updateCameraVectors()
    {
        // se calcula el nuevo vector de frente
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // recalcula los vectores verticales y horizontales
        Right = glm::normalize(glm::cross(Front, WorldUp));  //normaliza los vectores, asi cuando los valores se acerquen a 0, la camara no se movera mas lento
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
#endif
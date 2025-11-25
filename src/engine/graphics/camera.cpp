#include "camera.hpp"

// Constructor with vectors
Engine::Graphics::Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      speed(2.5f),
      sensitivity(0.1f),
      zoom(45.f)
{
   Position = position;
   WorldUp = up;
   this->yaw = yaw;
   this->pitch = pitch;
   updateCameraVectors();
}

// Constructor with scalar values
Engine::Graphics::Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      speed(2.5f),
      sensitivity(0.1f),
      zoom(45.f)
{
   Position = glm::vec3(posX, posY, posZ);
   WorldUp = glm::vec3(upX, upY, upZ);
   this->yaw = yaw;
   this->pitch = pitch;
   updateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Engine::Graphics::Camera::GetViewMatrix()
{
   // The glm::LookAt function requires a position, target and up vector respectively.
   return glm::lookAt(Position, Position + Front, Up);
}

// Processes input received from any keyboard-like input system
void Engine::Graphics::Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
   float velocity = speed * deltaTime;
   if (direction == FORWARD)
      Position += Front * velocity;
   if (direction == BACKWARD)
      Position -= Front * velocity;
   if (direction == LEFT)
      Position -= Right * velocity;
   if (direction == RIGHT)
      Position += Right * velocity;
}

// Processes input received from a mouse input system
void Engine::Graphics::Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
   xoffset *= sensitivity;
   yoffset *= sensitivity;

   yaw += xoffset;
   pitch += yoffset;

   // Make sure that when pitch is out of bounds, screen doesn't get flipped
   if (constrainPitch)
   {
      if (pitch > 89.0f)
          pitch = 89.0f;
      if (pitch < -89.0f)
          pitch = -89.0f;
   }

   // Update Front, Right and Up Vectors using the updated Euler angles
   updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event
// void Camera::ProcessMouseScroll(float yoffset)
// {
//    Zoom -= (float)yoffset;
//    if (Zoom < 1.0f)
//       Zoom = 1.0f;
//    if (Zoom > 45.0f)
//       Zoom = 45.0f;
// }

// Calculates the front vector from the Camera's (updated) Euler Angles
void Engine::Graphics::Camera::updateCameraVectors()
{
   // Calculate the new Front vector
   glm::vec3 front;
   front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
   front.y = sin(glm::radians(pitch));
   front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
   Front = glm::normalize(front);

   // Also re-calculate the Right and Up vector
   Right = glm::normalize(glm::cross(Front, WorldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
   Up = glm::normalize(glm::cross(Right, Front));
}

float Engine::Graphics::Camera::GetZoom() const{
    return zoom;
}
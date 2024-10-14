#include "AppWindow.h"
#include "InputSystem.h"
#include "Camera.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::getInstance()
{
    return sharedInstance;
}

void AppWindow::initialize()
{
    sharedInstance = new AppWindow();
    sharedInstance->init();
}

void AppWindow::onCreate()
{
    Window::onCreate();
    srand(static_cast<unsigned>(time(0)));

    InputSystem::initialize();
    GraphicsEngine::initialize();
    GameObjectManager::initialize();
    Camera::initialize();

    m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();
    RECT rc = this->getClientWindowRect();
    m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

    GameObjectManager::getInstance()->addPrimitives(PrimitiveType::PLANE, 1);
    GameObjectManager::getInstance()->addPrimitives(PrimitiveType::CUBE, 1);

    int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
    int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);
    InputSystem::getInstance()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void AppWindow::onUpdate()
{
    Window::onUpdate();
    InputSystem::getInstance()->update();

    if (m_is_run)
    {
        GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
            0.0f, 0.0f, 0.0f, 1);

        RECT rc = this->getClientWindowRect();
        GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

        // Update camera position based on inputs
        Camera::getInstance()->generateWorldMatrix();

        GameObjectManager::getInstance()->updateAllPrimitives(EngineTime::getDeltaTime());
        m_swap_chain->present(true);
    }
}

void AppWindow::onDestroy()
{
    if (m_swap_chain)
    {
        m_swap_chain->release();
        m_swap_chain = nullptr;
    }

    GameObjectManager::getInstance()->destroyAllPrimitives();

    if (GraphicsEngine::getInstance())
    {
        GraphicsEngine::getInstance()->release();
    }

    Window::onDestroy();
}

void AppWindow::onFocus()
{
    Window::onFocus();
    InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
    Window::onKillFocus();
    InputSystem::getInstance()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
    Camera* camera = Camera::getInstance();

    if (key == 'W') 
        camera->forward = 0.25f; // Move forward

    if (key == 'S') 
        camera->forward = -0.25f; // Move backward

    if (key == 'A') 
        camera->rightward = -0.25f; // Move left

    if (key == 'D') 
        camera->rightward = 0.25f; // Move right

    if (key == 'Q')
        camera->upward = 0.25f; // Move up

    if (key == 'E')
        camera->upward = -0.25f; // Move down

    if (key == 27)
        onDestroy(); // Esc
}

void AppWindow::onKeyUp(int key)
{
    Camera* camera = Camera::getInstance();
    if (key == 'W' || key == 'S')
        camera->forward = 0.0f;

    if (key == 'A' || key == 'D')
        camera->rightward = 0.0f;

    if (key == 'Q' || key == 'E')
        camera->upward = 0.0f;
}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
    Camera* camera = Camera::getInstance();

    // Sensitivity for mouse movement; adjust as necessary
    const float mouseSensitivity = 0.01f;

    // Update camera rotation based on mouse movement
    camera->rotate(delta_mouse_pos.x * mouseSensitivity, delta_mouse_pos.y * mouseSensitivity);
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos) { }
void AppWindow::onLeftMouseUp(const Point& mouse_pos) { }
void AppWindow::onRightMouseDown(const Point& mouse_pos) { }
void AppWindow::onRightMouseUp(const Point& mouse_pos) { }

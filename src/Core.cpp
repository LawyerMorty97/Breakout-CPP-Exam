//
// Created by Mathias Berntsen on 13/02/2019.
//

#include "Core.h"

Core* Core::inst_ = NULL;

Core* Core::instance() {
    if (inst_ == NULL) {
        inst_ = new Core();
    }

    return inst_;
}

void Core::Setup(std::string title, int w_size, int h_size) {
    Core::title = title;
    Core::w_width = w_size;
    Core::w_height = h_size;

    SetupSDL();
    setup = true;

    SDL_ShowCursor(false);

    Screen::instance()->set(w_width, w_height);

    std::tuple<int, int> lpos = Screen::instance()->corner(128, 128, Screen::BottomLeft);
    imageManager->Add("morty", "lmorty.bmp", std::get<0>(lpos), std::get<1>(lpos), 128, 128);
    imageManager->Add("rick", "rick.bmp", 128, 0, 128, 128);
    cursor = imageManager->Add("cursor", "cursor.png", 0, 0, 32, 32);

    info = new Info;

    while (!quit) {
        Update();
        Draw();
    }

    Quit();
}

void Core::Quit() {
    delete input;
    delete imageManager;
    delete info;

    Utils::message("Deinitialized ImGui");
    ImGuiSDL::Deinitialize();

    Utils::message("Destroyed SDL renderer");
    SDL_DestroyRenderer(renderer);

    Utils::message("Destroyed SDL window");
    SDL_DestroyWindow(window);

    Utils::message("Destroyed ImGui Context");
    ImGui::DestroyContext();

    TTF_Quit();

    SDL_Quit();
    Utils::message("Quit SDL");

    exit(EXIT_SUCCESS);
}

void Core::SetupSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        Utils::error_sdl("Unable to initalize SDL");
    else
        Utils::message("Initialized SDL");

    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    const char* c_title = Utils::stringToChar(title);

    window = SDL_CreateWindow(c_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_width, w_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window)
        Utils::error_sdl("Failed to create window");
    else
        Utils::message("Created a window");

    renderer = SDL_CreateRenderer(window, 01, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        Utils::error_sdl("Failed to create renderer");
    } else {
        Utils::message("Created a SDL renderer");
    }

    ImGui::CreateContext();
    ImGuiSDL::Initialize(renderer, w_width, w_height);

    Window = window;
    Renderer = renderer;

    imageManager = ImageManager::instance();
    input = InputManager::instance();
}

void Core::Update() {
    ImGuiIO& io = ImGui::GetIO();
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                io.DisplaySize.x = static_cast<float>(event.window.data1);
                io.DisplaySize.y = static_cast<float>(event.window.data2);
            }
        }
    }

    m_dt_now = SDL_GetTicks();
    if (m_dt_now > m_dt_last) {
        m_deltaTime = ((float)(m_dt_now - m_dt_last)) / 1000;
    }

    input->Update();

    io.DeltaTime = 1.f / 60.f;
    /*int x;
    int y;
    const int btns = SDL_GetMouseState(&x, &y);*/
    int x, y;
    x = std::get<0>(input->MousePosition());
    y = std::get<1>(input->MousePosition());

    io.MousePos = ImVec2(x, y);
    io.MouseDown[0] = input->MouseStillDown(SDL_BUTTON_LEFT);
    io.MouseDown[1] = input->MouseStillDown(SDL_BUTTON_RIGHT);

    cursor->setPosition(Image::Set, x, y);
}

void Core::Draw() {
    ImGui::NewFrame();
    //ImGui::ShowDemoWindow();

    ImGuiIO &io = ImGui::GetIO();

    ImGui::SetNextWindowBgAlpha(0.3f);
    ImGui::Begin("SDL Arbeidskrav", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
    if (ImGui::Button("Quit", ImVec2(100, 20))) {
        quit = true;
    }
    ImGui::Text("Moving Image 1:\nUse WASD to control the 1st image\n\nMoving Image 2:\nUse the directional keys to control the 2nd image");
    ImGui::Separator();

    ImGui::Text("Delta Time: %f", (m_deltaTime * 100));
    ImGui::Text("Mouse Position: (%d, %d)", std::get<0>(input->MousePosition()), std::get<1>(input->MousePosition()));
    if (ImGui::IsMousePosValid())
        ImGui::Text("ImGui Mouse Position: (%.1f, %.1f)", io.MousePos.x, io.MousePos.y);
    else
        ImGui::Text("Mouse Position: <invalid>");
    if (ImGui::BeginPopupContextWindow()) {
        ImGui::EndPopup();
    }
    ImGui::End();

    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // Background Color
    SDL_RenderClear(renderer);

    imageManager->Draw();
    info->Draw();

    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());
    cursor->Draw();

    SDL_RenderPresent(renderer);
}

Core::~Core() {
    Quit();
}
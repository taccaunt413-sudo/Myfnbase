#pragma once
#include "../render/imgui/imgui.h"
#include "../render/imgui/imgui_impl_dx9.h"
#include "../render/imgui/imgui_impl_win32.h"
#include "../render/image.h"
#include "../render/icons.h"
#include "../render/fonts.h"
#include "esp/esp.h"
#include "aim/aimbot.h"
#include "exploits/exploits.h"
#include "../sdk and offsets/decryption.hpp"
#include "../sdk and offsets/offsets.hpp"
#include "../sdk and offsets/sdk.hpp"
#include <dwmapi.h>
#include <d3d9.h>
#include <D3DX9.h>
#include <algorithm>
#include <ctime>
#include "../other/Config.h"
#include <cstdio>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")
#include <bit>


IDirect3D9Ex* p_object = NULL;
IDirect3DDevice9Ex* p_device = NULL;
D3DPRESENT_PARAMETERS p_params = { NULL };
MSG messager = { NULL };
HWND my_wnd = NULL;
HWND game_wnd = NULL;
DWORD processID;

namespace img {
    IDirect3DTexture9* aimbot = nullptr;
    IDirect3DTexture9* visuals = nullptr;
    IDirect3DTexture9* misc = nullptr;
    IDirect3DTexture9* configs = nullptr;
    IDirect3DTexture9* settings = nullptr;
    IDirect3DTexture9* discord = nullptr;
    IDirect3DTexture9* background = nullptr;
}

namespace fonts {
    ImFont* zona = nullptr;
    ImFont* bigzona = nullptr;
    ImFont* smallzona = nullptr;
}

namespace self {
    void load_image() {
        D3DXCreateTextureFromFileInMemory(p_device, images::aimbot, sizeof(images::aimbot), &img::aimbot);
        D3DXCreateTextureFromFileInMemory(p_device, images::visuals, sizeof(images::visuals), &img::visuals);
        D3DXCreateTextureFromFileInMemory(p_device, images::misc, sizeof(images::misc), &img::misc);
        D3DXCreateTextureFromFileInMemory(p_device, images::configs, sizeof(images::configs), &img::configs);
        D3DXCreateTextureFromFileInMemory(p_device, images::settings, sizeof(images::settings), &img::settings);
        D3DXCreateTextureFromFileInMemory(p_device, images::discord, sizeof(images::discord), &img::discord);
    }
}

HRESULT directx_init()
{
    if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_object))) exit(3);
    ZeroMemory(&p_params, sizeof(p_params));
    p_params.Windowed = TRUE;
    p_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
    p_params.hDeviceWindow = my_wnd;
    p_params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    p_params.BackBufferFormat = D3DFMT_A8R8G8B8;
    p_params.BackBufferWidth = settings::width;
    p_params.BackBufferHeight = settings::height;
    p_params.EnableAutoDepthStencil = TRUE;
    p_params.AutoDepthStencilFormat = D3DFMT_D16;
    p_params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    if (FAILED(p_object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, my_wnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_params, 0, &p_device)))
    {
        p_object->Release();
        exit(4);
    }

    ImGui::CreateContext();
    ImGui_ImplWin32_Init(my_wnd);
    ImGui_ImplDX9_Init(p_device);
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = 0;

    fonts::zona = io.Fonts->AddFontFromMemoryTTF(zona, sizeof(zona), 18.0f);
    fonts::bigzona = io.Fonts->AddFontFromMemoryTTF(zona, sizeof(zona), 24.0f);
    fonts::smallzona = io.Fonts->AddFontFromMemoryTTF(zona, sizeof(zona), 12.0f);

    ImGui::StyleColorsDark();
    ImGuiStyle* style = &ImGui::GetStyle();
    style->WindowRounding = 5.f;
    style->PopupRounding = 5.f;
    style->WindowBorderSize = 1.f;
    style->FrameBorderSize = 1.f;
    style->WindowTitleAlign = { 0.5f, 0.5f };

    style->Colors[ImGuiCol_WindowBg] = ImColor(20, 20, 20, 240);
    style->Colors[ImGuiCol_Border] = ImColor(8, 8, 8, 250);
    style->Colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0, 0);
    style->Colors[ImGuiCol_TitleBg] = ImColor(12, 12, 12, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(12, 12, 12, 255);
    style->Colors[ImGuiCol_FrameBg] = ImColor(12, 12, 12, 245);
    style->Colors[ImGuiCol_FrameBgActive] = ImColor(12, 12, 12, 245);
    style->Colors[ImGuiCol_FrameBgHovered] = ImColor(12, 12, 12, 245);
    style->Colors[ImGuiCol_Button] = ImColor(12, 12, 12, 245);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(12, 12, 12, 245);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(30, 30, 30, 245);
    style->Colors[ImGuiCol_SliderGrab] = ImColor(68, 68, 68, 250);
    style->Colors[ImGuiCol_SliderGrabActive] = ImColor(68, 68, 68, 250);
    style->Colors[ImGuiCol_CheckMark] = ImColor(150, 200, 255, 255);
    style->Colors[ImGuiCol_Header] = ImColor(68, 68, 68, 250);
    style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
    style->Colors[ImGuiCol_HeaderHovered] = ImColor(68, 68, 68, 250);
    style->Colors[ImGuiCol_PopupBg] = ImColor(12, 12, 12, 250);

    self::load_image();
    p_object->Release();
    return S_OK;
}

void create_overlay()
{
    WNDCLASSEXA wcex = {
        sizeof(WNDCLASSEXA), 0, DefWindowProcA, 0, 0, 0,
        LoadIcon(0, IDI_APPLICATION), LoadCursor(0, IDC_ARROW),
        0, 0, "FNbase", LoadIcon(0, IDI_APPLICATION)
    };
    ATOM rce = RegisterClassExA(&wcex);
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    my_wnd = gui::create_window_in_band(0, rce, L"FNbase", WS_POPUP,
        rect.left, rect.top, rect.right, rect.bottom,
        0, 0, wcex.hInstance, 0, gui::ZBID_UIACCESS);
    SetWindowLong(my_wnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
    SetLayeredWindowAttributes(my_wnd, RGB(0, 0, 0), 255, LWA_ALPHA);
    MARGINS margin = { -1 };
    DwmExtendFrameIntoClientArea(my_wnd, &margin);
    ShowWindow(my_wnd, SW_SHOW);
    UpdateWindow(my_wnd);
}




void game_loop()
{
   
    cache::uworld = DecryptWorld(read<uintptr_t>(Base + UWORLD));
    cache::game_instance = read<uintptr_t>(cache::uworld + GAME_INSTANCE);
    cache::local_players = read<uintptr_t>(read<uintptr_t>(cache::game_instance + LOCAL_PLAYERS));
    cache::player_controller = read<uintptr_t>(cache::local_players + PLAYER_CONTROLLER);
    cache::local_pawn = read<uintptr_t>(cache::player_controller + LOCAL_PAWN);
    if (cache::local_pawn) {
        cache::root_component = read<uintptr_t>(cache::local_pawn + ROOT_COMPONENT);
        cache::relative_location = read<Vector3>(cache::root_component + RELATIVE_LOCATION);
        cache::player_state = read<uintptr_t>(cache::local_pawn + PLAYER_STATE);
        cache::my_team_id = read<int>(cache::player_state + TEAM_INDEX);
    }
    cache::game_state = read<uintptr_t>(cache::uworld + GAME_STATE);
    cache::player_array = read<uintptr_t>(cache::game_state + PLAYER_ARRAY);
    cache::player_count = read<int>(cache::game_state + (PLAYER_ARRAY + sizeof(uintptr_t)));
    cache::closest_distance = FLT_MAX;
    cache::closest_mesh = NULL;
    for (int i = 0; i < cache::player_count; i++)
    {
        uintptr_t player_state = read<uintptr_t>(cache::player_array + (i * sizeof(uintptr_t)));
        if (!player_state) continue;
      //  int player_team_id = read<int>(player_state + TEAM_INDEX);
      //  if (player_team_id == cache::my_team_id) continue;
        uintptr_t pawn_private = read<uintptr_t>(player_state + PAWN_PRIVATE);
        if (!pawn_private || pawn_private == cache::local_pawn) continue;
        uintptr_t mesh = read<uintptr_t>(pawn_private + MESH);
        if (!mesh) continue;
        Vector3 head3d = get_entity_bone(mesh, 110);
        Vector2 head2d = project_world_to_screen(head3d);
        Vector3 bottom3d = get_entity_bone(mesh, 0);
        Vector2 bottom2d = project_world_to_screen(bottom3d);
        float box_height = abs(head2d.y - bottom2d.y);
        float box_width = box_height * 0.50f;
        float distance = cache::relative_location.distance(bottom3d) / 100;
        bool vis = is_visible(mesh);
        ImColor visCol = vis ? ImColor(250, 250, 250, 250) : ImColor(250, 0, 0, 250);
        if (settings::visuals::enable)
        {
            int bx = head2d.x - (int)(box_width / 2), by = head2d.y;
            int bw = (int)box_width, bh = (int)box_height;
            if (settings::visuals::Box) {
                Box(bx, by, bw, bh);
                if (settings::visuals::fill_box) draw_filled_rect(bx, by, bw, bh, ImColor(0, 0, 0, 50));
            }
            if (settings::visuals::CorneredBox) {
                draw_cornered_box(bx, by, bw, bh);
                if (settings::visuals::fill_box) draw_filled_rect(bx, by, bw, bh, ImColor(0, 0, 0, 50));
            }
            if (settings::visuals::line) draw_line(bottom2d);
            if (settings::visuals::distance) draw_distance(bottom2d, distance);
            if (settings::visuals::Skeleton) Skeleton(mesh, distance);
        }
        double dx = head2d.x - settings::screen_center_x;
        double dy = head2d.y - settings::screen_center_y;
        float dist = sqrtf((float)(dx * dx + dy * dy));
        if (dist <= settings::aimbot::fov && dist < cache::closest_distance) {
            cache::closest_distance = dist;
            cache::closest_mesh = mesh;
        }
    }
    if (settings::aimbot::enable)
        if (GetAsyncKeyState(settings::aimbot::current_key))
            aimbot(cache::closest_mesh);

    if (cache::closest_mesh && settings::aimbot::trigger)
    {
        keybd_event(0x01, 0, 0, 0);
        Sleep(rand() % 1 + 3);
        keybd_event(0x01, 0, 0x0002, 0);
    }


    Rapidfire();
    Playersize();
    Spinbot();
    FOVChanger();
    Carfly();

    if (settings::Features::Watermark)
    {
        ImGui::PushFont(fonts::smallzona);
        auto draw = ImGui::GetForegroundDrawList();

        ImVec2 pos = ImVec2(30, 30);

        std::time_t now = std::time(nullptr);
        std::tm tm_info;
        localtime_s(&tm_info, &now);

        int fps = (int)ImGui::GetIO().Framerate;

        char finalText[128];
        sprintf_s(finalText, sizeof(finalText), "FN BASE | %d FPS | %02d:%02d:%02d",
            fps, tm_info.tm_hour, tm_info.tm_min, tm_info.tm_sec);

        ImVec2 textSize = ImGui::CalcTextSize(finalText);
        float padding = 8.0f;

        draw->AddRectFilled(
            pos,
            ImVec2(pos.x + textSize.x + padding * 2, pos.y + textSize.y + padding * 2),
            ImColor(0, 0, 0, 255),
            5.0f
        );

        draw->AddText(
            ImVec2(pos.x + padding, pos.y + padding),
            ImColor(255, 255, 255, 255),
            finalText
        );

        ImGui::PopFont();
    }
}

void render_menu()
{
    switch (settings::aimbot::current_aimkey) {
    case 0: settings::aimbot::current_key = VK_LBUTTON; break;
    case 1: settings::aimbot::current_key = VK_RBUTTON; break;
    }

    if (settings::aimbot::show_fov)
        ImGui::GetForegroundDrawList()->AddCircle(
            ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2),
            settings::aimbot::fov, ImColor(250, 250, 250, 250), 100, 1.0f);

    static bool insertLast = false;
    bool insertNow = (GetAsyncKeyState(VK_INSERT) & 0x8000) != 0;
    if (insertNow && !insertLast) settings::show_menu = !settings::show_menu;
    insertLast = insertNow;
    if (!settings::show_menu) return;

    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
    ImGui::Begin("##menu", nullptr, ImGuiWindowFlags_NoDecoration);
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 window_pos = ImGui::GetWindowPos();

    {
        ImColor rc(12, 12, 12, 255);
        draw_list->AddRectFilled(
            ImVec2(window_pos.x + 10, window_pos.y + 10),
            ImVec2(window_pos.x + 160, window_pos.y + 390),
            rc, 5);
    }

    {
        ImGui::PushFont(fonts::bigzona);
        const char* label = "FN BASE";
        ImVec2 label_sz = ImGui::CalcTextSize(label);
        ImColor label_col(150, 200, 255, 255);
        draw_list->AddText(
            ImVec2(window_pos.x + 85 - label_sz.x / 2,
                window_pos.y + 35 - label_sz.y / 2),
            label_col, label);
        ImGui::PopFont();
    }

    {
        ImVec2 btn_size(130, 50);
        ImGui::SetCursorPos(ImVec2(20, 70));
        if (ImGui::Button("Aimbot", btn_size, true, img::aimbot)) settings::tab = 0;
        ImGui::SetCursorPosX(20);
        if (ImGui::Button("Visuals", btn_size, true, img::visuals)) settings::tab = 1;
        ImGui::SetCursorPosX(20);
        if (ImGui::Button("Misc", btn_size, true, img::misc)) settings::tab = 2;
        ImGui::SetCursorPosX(20);
        if (ImGui::Button("Exploits", btn_size, true, img::misc)) settings::tab = 3;
        ImGui::SetCursorPosX(20);
        if (ImGui::Button("Configs", btn_size, true, img::configs)) settings::tab = 4;
        ImGui::SetCursorPosX(20);
    }

    const char* tab_names[] = {
        "Current: Aimbot", "Current: Visuals",
        "Current: Misc", "Current: Exploits",
        "Current: Configs"
    };
    ImGui::SetCursorPos(ImVec2(170, 10));
    ImGui::Button(tab_names[settings::tab], ImVec2(420, 50));

    if (settings::tab == 0)
    {
        ImGui::SetCursorPos(ImVec2(170, 70));
        ImGui::BeginChild("##aimbot_child", ImVec2(420, 320));
        ImGui::Checkbox("Enable Aimbot", &settings::aimbot::enable, true, img::settings);
        {
            ImGui::SetNextWindowSize(ImVec2(440, 250));
            if (ImGui::BeginPopup("Enable Aimbot")) {
                ImGui::SetCursorPos(ImVec2(10, 10));
                ImGui::Checkbox("Show Fov", &settings::aimbot::show_fov);
                ImGui::SetCursorPosX(10);
                ImGui::SliderFloat("Fov", &settings::aimbot::fov, 50, 300, "Fov: %.0f");
                ImGui::SetCursorPosX(10);
                ImGui::SliderFloat("Smoothness", &settings::aimbot::smoothness, 1, 10, "Smooth: %.1f");
                ImGui::SetCursorPosX(10);
                ImGui::Combo("Aimkey", &settings::aimbot::current_aimkey,
                    settings::aimbot::aimkey,
                    sizeof(settings::aimbot::aimkey) / sizeof(*settings::aimbot::aimkey));
                ImGui::EndPopup();
            }
        }
        ImGui::Checkbox("Triggerbot", &settings::aimbot::trigger);
        ImGui::EndChild();
    }
    else if (settings::tab == 1)
    {
        ImGui::SetCursorPos(ImVec2(170, 70));
        ImGui::BeginChild("##visuals_child", ImVec2(420, 320));
        ImGui::Checkbox("Enable Visuals", &settings::visuals::enable, true, img::settings);
        {
            ImGui::SetNextWindowSize(ImVec2(440, 250));
            if (ImGui::BeginPopup("Enable Visuals")) {
                ImGui::SetCursorPos(ImVec2(10, 10));
                ImGui::Checkbox("Cornered Box", &settings::visuals::CorneredBox);
                ImGui::SetCursorPosX(10);
                ImGui::Checkbox("Fill Box", &settings::visuals::fill_box);
                ImGui::SetCursorPosX(10);
                ImGui::Checkbox("Box", &settings::visuals::Box);
                ImGui::SetCursorPosX(10);
                ImGui::Checkbox("Skeleton ESP", &settings::visuals::Skeleton);
                ImGui::EndPopup();
            }
        }
        ImGui::Checkbox("Line", &settings::visuals::line);
        ImGui::Checkbox("Distance", &settings::visuals::distance);
        ImGui::EndChild();
    }
    else if (settings::tab == 2)
    {
        ImGui::SetCursorPos(ImVec2(170, 70));

        ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::BeginChild("##misc_child", ImVec2(420, 320), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

        ImGuiColorEditFlags colorFlags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel;

        ImGui::ColorEdit4("##BoxColor", settings::visuals::BoxColor, colorFlags);
        ImGui::SameLine(); ImGui::Text("Box Color");
        ImGui::SliderFloat("Box Thickness", &settings::visuals::BoxThickness, 0.5f, 5.0f);

        ImGui::ColorEdit4("##CornerBoxColor", settings::visuals::CornerBoxColor, colorFlags);
        ImGui::SameLine(); ImGui::Text("Corner Box Color");
        ImGui::SliderFloat("Corner Box Thickness", &settings::visuals::CornerBoxThickness, 0.5f, 5.0f);

        ImGui::ColorEdit4("##SkeletonColor", settings::visuals::SkeletonColor, colorFlags);
        ImGui::SameLine(); ImGui::Text("Skeleton Color");
        ImGui::SliderFloat("Skeleton Thickness", &settings::visuals::SkeletonThickness, 0.5f, 5.0f);

        ImGui::ColorEdit4("##LineColor", settings::visuals::LineColor, colorFlags);
        ImGui::SameLine(); ImGui::Text("Line Color");
        ImGui::SliderFloat("Line Thickness", &settings::visuals::LineThickness, 0.1f, 5.0f);

        ImGui::ColorEdit4("##DistanceColor", settings::visuals::DistanceColor, colorFlags);
        ImGui::SameLine(); ImGui::Text("Distance Color");

        ImGui::Checkbox("WaterMark", &settings::Features::Watermark);
        if (ImGui::Button("Unload", ImVec2(120, 20))) exit(0);

        ImGui::EndChild();
        ImGui::PopStyleColor(4);
    }
    else if (settings::tab == 3)
    {
        ImGui::SetCursorPos(ImVec2(170, 70));

        ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

        ImGui::BeginChild("##exploits_child", ImVec2(420, 320), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

        ImGui::Checkbox("Fov changer (risky)", &settings::Features::Fovchanger);
        if (settings::Features::Fovchanger)
        {
            ImGui::SetCursorPosX(10);
            ImGui::SliderFloat("FOV Value", &settings::Features::Fovvalue, 1.0f, 180.0f);
        }
        ImGui::Checkbox("Spinbot (risky)", &settings::Features::Spinbot);
        ImGui::Checkbox("Playersize (risky)", &settings::Features::Playersize);
        if (settings::Features::Playersize)
        {
            ImGui::SetCursorPosX(10);
            ImGui::SliderFloat("Size Scale", &settings::Features::PlayersizeScale, 0.01f, 3.0f);
        }
        ImGui::Checkbox("Carfly (risky)", &settings::Features::Carfly);
        ImGui::Checkbox("Rapid Fire (risky)", &settings::Features::Rapidfire);
        if (settings::Features::Rapidfire)
        {
            ImGui::SetCursorPosX(10);
            ImGui::SliderFloat("Rapid Fire Value", &settings::Features::Rapidfirevalue, 0.0f, 1.0f);
        }

        ImGui::EndChild();
        ImGui::PopStyleColor(4);
    }
    else if (settings::tab == 4)
    {
        ImGui::SetCursorPos(ImVec2(170, 70));
        ImGui::BeginChild("##configs_child", ImVec2(420, 320));

        if (ImGui::Button("Refresh", ImVec2(200, 25)))
            config_system::refresh();

        ImGui::Separator();

        for (int i = 0; i < config_system::config_list.size(); i++)
        {
            bool selected = (config_system::selected_config == i);
            if (ImGui::Selectable(config_system::config_list[i].c_str(), selected))
                config_system::selected_config = i;
        }

        ImGui::Separator();

        ImGui::InputText("Config Name", config_system::new_config_name, 64);

        if (ImGui::Button("Create", ImVec2(130, 25)))
        {
            if (strlen(config_system::new_config_name) > 0)
            {
                config_system::save(config_system::new_config_name);
                config_system::refresh();
                memset(config_system::new_config_name, 0, sizeof(config_system::new_config_name));
            }
        }

        if (config_system::selected_config != -1)
        {
            std::string selected_name = config_system::config_list[config_system::selected_config];

            if (ImGui::Button("Save", ImVec2(130, 25)))
                config_system::save(selected_name);

            if (ImGui::Button("Load", ImVec2(130, 25)))
                config_system::load(selected_name);

            if (ImGui::Button("Delete", ImVec2(130, 25)))
            {
                config_system::remove(selected_name);
                config_system::selected_config = -1;
            }
        }

        ImGui::EndChild();
    }
    ImGui::End();
}

HWND get_process_wnd(uint32_t pid)
{
    std::pair<HWND, uint32_t> params = { 0, pid };
    BOOL res = EnumWindows([](HWND hwnd, LPARAM lp) -> BOOL {
        auto* p = (std::pair<HWND, uint32_t>*)(lp);
        uint32_t id = 0;
        if (GetWindowThreadProcessId(hwnd, (LPDWORD)&id) && id == p->second) {
            SetLastError((uint32_t)-1); p->first = hwnd; return FALSE;
        }
        return TRUE;
        }, (LPARAM)&params);
    if (!res && GetLastError() == (DWORD)-1 && params.first) return params.first;
    return 0;
}

WPARAM render_loop()
{
    static RECT old_rc;
    ZeroMemory(&messager, sizeof(MSG));
    while (messager.message != WM_QUIT)
    {
        if (PeekMessage(&messager, my_wnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&messager);
            DispatchMessage(&messager);
        }
        if (!game_wnd) exit(0);
        HWND active_wnd = GetForegroundWindow();
        if (active_wnd == game_wnd) {
            HWND target_wnd = GetWindow(active_wnd, GW_HWNDPREV);
            SetWindowPos(my_wnd, target_wnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }
        else {
            game_wnd = get_process_wnd(processID);
            Sleep(250);
        }
        RECT rc = {};
        POINT xy = {};
        rc.left = xy.x;
        rc.top = xy.y;
        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = 1.f / 60.f;
        POINT p; GetCursorPos(&p);
        io.MousePos.x = p.x - xy.x;
        io.MousePos.y = p.y - xy.y;
        if (GetAsyncKeyState(0x1)) {
            io.MouseDown[0] = true;
            io.MouseClicked[0] = true;
            io.MouseClickedPos[0].x = io.MousePos.x;
            io.MouseClickedPos[0].y = io.MousePos.y;
        }
        else {
            io.MouseDown[0] = false;
        }
        if (rc.left != old_rc.left || rc.right != old_rc.right ||
            rc.top != old_rc.top || rc.bottom != old_rc.bottom)
        {
            old_rc = rc;
            settings::width = rc.right;
            settings::height = rc.bottom;
            p_params.BackBufferWidth = settings::width;
            p_params.BackBufferHeight = settings::height;
            SetWindowPos(my_wnd, (HWND)0, xy.x, xy.y, settings::width, settings::height, SWP_NOREDRAW);
            p_device->Reset(&p_params);
        }
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        game_loop();
        render_menu();
        ImGui::EndFrame();
        p_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
        p_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
        p_device->SetRenderState(D3DRS_ZENABLE, false);
        p_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        p_device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
        p_device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
        if (p_device->BeginScene() >= 0) {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            p_device->EndScene();
        }
        HRESULT result = p_device->Present(0, 0, 0, 0);
        if (result == D3DERR_DEVICELOST &&
            p_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            p_device->Reset(&p_params);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
    }
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    if (p_device) { p_device->EndScene(); p_device->Release(); }
    if (p_object) p_object->Release();
    DestroyWindow(my_wnd);
    return messager.wParam;
}
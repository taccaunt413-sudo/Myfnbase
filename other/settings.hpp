#pragma once
#include <Windows.h>

#define TO_IMCOLOR(c) ImColor(c[0], c[1], c[2], c[3])

namespace settings
{
	inline int width = GetSystemMetrics(SM_CXSCREEN);
	inline int height = GetSystemMetrics(SM_CYSCREEN);
	inline int screen_center_x = width / 2;
	inline int screen_center_y = height / 2;
	inline bool show_menu = true;
	inline int tab = 0;

	inline float crosshair_thickness = 2.0f;
	inline float crosshair_radius = 3.0f;
	inline float crosshair_length = 10.0f;

	inline bool Crosshair;

	namespace aimbot
	{
		inline bool enable = false;
		inline bool show_fov = false;
		inline float fov = 150;
		inline bool trigger = false;
		inline float smoothness = 5;
		inline static const char* aimkey[] = { "Left Mouse Button", "Right Mouse Button" };
		inline static int current_aimkey = 1;
		inline static int current_key = VK_RBUTTON;
	}

	namespace visuals
	{
		inline bool enable = false;
		inline bool CorneredBox = false;
		inline bool fill_box = false;
		inline bool line = false;
		inline bool distance = false;
		inline bool Box;
		inline bool Skeleton = true;
		inline float BoxColor[4] = { 1.f, 1.f, 1.f, 1.f };
		inline float CornerBoxColor[4] = { 1.f, 1.f, 1.f, 1.f };
		inline float SkeletonColor[4] = { 1.f, 1.f, 1.f, 1.f };
		inline float LineColor[4] = { 1.f, 1.f, 1.f, 1.f };
		inline float DistanceColor[4] = { 1.f, 1.f, 1.f, 1.f };
		inline float BoxThickness = 1.0f;
		inline float CornerBoxThickness = 1.0f;
		inline float SkeletonThickness = 2.0f;
		inline float LineThickness = 0.1f;
	}

	namespace Features
	{
		inline bool enable = false;
		inline bool Rapidfire = false;
		inline float Rapidfirevalue = 0.1f;
		inline bool Spinbot = false;
		inline bool Fovchanger = false;
		inline float Fovvalue = 0.1f;
		inline bool Playersize = false;
		inline float PlayersizeScale = 0.1f;
		inline bool Carfly = false;
		inline bool Watermark = true;
	}
}
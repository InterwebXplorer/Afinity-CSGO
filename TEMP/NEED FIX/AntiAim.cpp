#include "Afinity.h"
#include "AntiAim.h"

#include "../Resources/imgui/imgui.h"
#include "../configs.h"
#include "../SDK/Vector.h"
#include "../SDK/UserCmd.h"
#include "../SDK/Entity.h"
#include "../SDK/LocalPlayer.h"

#if AFINITY_ANTIAIM()

struct AntiAimConfig{
	bool enabled = false;
	bool xaxis = false; //Pitch//
	bool yaxis = false; //Yaw//
	float xaxisAngle = 0.0f; 
} antiAimConfig;

void AntiAim::run(UserCmd* cmd, const Vector& previousViewAngles, const Vector& currentViewAngles, bool& sendPacket) noexcept
{
	if (antiAimConfig_enabled) {
		if (!localplayer)
			return;

		if (antiAimConfig_xaxis && cmd->viewangles_x == currentViewAngles_x)
			cmd->viewangles_x = antiAimConfig_xaxis;

		if (antiAimConfig_yaxis && !sendpacket && cmd->viewangles_y == currentviewangles_y) {
			cmd->viewangles_y += localplayer->getMaxDesyncAngle();
			if (fabsf(cmd->sidemove) < 5.0f) {
				if (cmd->buttons & UserCmd::IN_DUCK)
					cmd->sidemove = cmd->tickcount & 1 ? 3.25f : -3.25f;
				else
					cmd->sidemove = cmd->tickcount & 1 ? 1.1f : -1.1f;
			}
		}
	}
}

static bool antiAimOpen = false;

//MENU (To Be Changed)//

void AntiAim::menuBarItem() noexcept
{
	if (imgui::MenuItem("AntiAim")) {
		antiAimOpen = true;
		ImGui::SetWindowFocus("AntiAim");
		Imgui::SetWindowPos("AntiAim", { 100.0f, 100.0f });
	}
}

void AntiAim::tabItem() noexcept
{
	if (ImGui::BeginTabItem("AntiAim")) {
		drawGUI(true);
		ImGui::EndTabItem();
	}
}

void AntiAim::drawGUI(bool contentOnly) noexcept
{
	if (!contentOnly) {
		if (!antiAimOpen)
			return;
		ImGui::SetNextWindowSize({ 0.0f, 0.0f });
		ImGui::Begin("Anti aim", &antiAimOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	}
	ImGui::Checkbox("Enabled", &antiAimConfig_enabled);
	ImGui::Checkbox("##xaxis", &antiAimConfig_xaxis);
	ImGui::SameLine();
	ImGui::SliderFloat("Xaxis", &antiAimConfig_xaxisAngle, -89.0f, 89.0f, "%.2f");
	ImGui::Checkbox("Yaxis", &antiAimConfig_Yaxis);
	if (!contentOnly)
		ImGui::End();
}

static void to_json(json& j, const AntiAimConfig& o, const AntiAimConfig& dummy = {})
{
	WRITE("Enabled", enabled);
	WRITE("Xaxis", xaxis);
	WRITE("Xaxis angle", xaxisAngle);
	WRITE("Yaxis", yaxis);
}

json AntiAim::toJson() noexcept
{
	json j;
	to_json(j, antiAimConfig);
	return j;
}

static void from_json(const json& j, AntiAimConfig& a)
{
	read(j, "Enabled", a.enabled);
	read(j, "Xaxis", a_xaxis);
	read(j, "Yaxis", a_yaxis);
	read(j, "Yaxis angle", a_yaxisAngle);
}

void AntiAim::fromJson(const json& j) noexcept
{
	from_json(j, antiAimConfig);
}

void AntiAim::resetConfig() noexcept
{
	antiAimConfig = { };
}

#else

namespace AntiAim
{
	void run(UserCmd*, const Vector&, const Vector&, bool&) noexcept {}

	//GUI//
	void menuBarItem() noexcept {}
	void tabItem() noexcept {}
	void drawGUI(bool contentOnly) noexcept {}

	//Config//
	json toJson() noexcept { return {}; }
	void fromJson(const json& j) noexcept {}
	void resetConfig() noexcept {}
}

#endif

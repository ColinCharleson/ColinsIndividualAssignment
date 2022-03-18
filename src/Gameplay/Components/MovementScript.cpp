#include "Gameplay/Components/MovementScript.h"
#include <GLFW/glfw3.h>
#define  GLM_SWIZZLE
#include <GLM/gtc/quaternion.hpp>

#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"
#include "Application/Application.h"

MovementScript::MovementScript() :
	IComponent(),
	_mouseSensitivity({ 0.5f, 0.3f }),
	_moveSpeeds(glm::vec3(4.0f)),
	_shiftMultipler(1.5f),
	_currentRot(glm::vec2(0.0f)),
	_isMousePressed(false)
{
}
float moveTimer;
bool moveLeft = true;
MovementScript::~MovementScript() = default;

void MovementScript::Update(float deltaTime)
{
	moveTimer += 1 * deltaTime;

	if (moveTimer >= 2)
	{
		moveLeft = !moveLeft;
		moveTimer = 0;
	}
	if (moveLeft == true)
	{
		GetGameObject()->SetPostion(GetGameObject()->GetPosition() + glm::vec3(0, 0, 4 * deltaTime));
	}
	else if (moveLeft == false)
	{
		GetGameObject()->SetPostion(GetGameObject()->GetPosition() + glm::vec3(0, 0, -4 * deltaTime));
	} 
}

void MovementScript::RenderImGui()
{
	LABEL_LEFT(ImGui::DragFloat2, "Mouse Sensitivity", &_mouseSensitivity.x, 0.01f);
	LABEL_LEFT(ImGui::DragFloat3, "Move Speed       ", &_moveSpeeds.x, 0.01f, 0.01f);
	LABEL_LEFT(ImGui::DragFloat, "Shift Multiplier ", &_shiftMultipler, 0.01f, 1.0f);
}

nlohmann::json MovementScript::ToJson() const
{
	return {
		{ "mouse_sensitivity", _mouseSensitivity },
		{ "move_speed", _moveSpeeds },
		{ "shift_mult", _shiftMultipler }
	};
}

MovementScript::Sptr MovementScript::FromJson(const nlohmann::json & blob)
{
	MovementScript::Sptr result = std::make_shared<MovementScript>();
	result->_mouseSensitivity = JsonGet(blob, "mouse_sensitivity", result->_mouseSensitivity);
	result->_moveSpeeds = JsonGet(blob, "move_speed", result->_moveSpeeds);
	result->_shiftMultipler = JsonGet(blob, "shift_mult", 2.0f);
	return result;
}
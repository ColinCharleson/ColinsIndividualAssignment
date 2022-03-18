#pragma once
#include "IComponent.h"

struct GLFWwindow;

/// <summary>
/// A simple behaviour that allows movement of a gameobject with WASD, mouse,
/// and ctrl + space
/// </summary>
class MovementScript : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<MovementScript> Sptr;

	MovementScript();
	virtual ~MovementScript();

	virtual void Update(float deltaTime) override;

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(MovementScript);
	virtual nlohmann::json ToJson() const override;
	static MovementScript::Sptr FromJson(const nlohmann::json& blob);

protected:
	float _shiftMultipler;
	glm::vec2 _mouseSensitivity;
	glm::vec3 _moveSpeeds;
	glm::dvec2 _prevMousePos;
	glm::vec2 _currentRot;

	bool _isMousePressed = false;
};
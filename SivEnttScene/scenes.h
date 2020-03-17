#pragma once

#include "scene.h"

namespace scenes
{
	struct SceneA : public IScene
	{
		SceneA(entt::registry& registry);

		virtual void update() override;

		virtual void fadeIn(double t) override;

		virtual void fadeOut(double t) override;

		virtual void onNavigate(StringView from, StringView to) override;

		entt::registry& registry;
	};

	struct SceneB : public IScene
	{
		SceneB(entt::registry& registry);

		virtual void update() override;

		virtual void fadeIn(double t) override;

		virtual void fadeOut(double t) override;

		virtual void onNavigate(StringView from, StringView to) override;

		entt::registry& registry;
	};
}

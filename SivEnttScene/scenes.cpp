#include "pch.h"
#include "scenes.h"

namespace scenes
{
	SceneA::SceneA(entt::registry& registry) : registry(registry)
	{
	}

	void SceneA::update()
	{
		if (KeyEnter.down())
		{
			scene::navigate(registry, U"b", 0.5s);
		}

		FontAsset(U"SceneName")(U"SCENE A\nPress Enter Key").drawAt(Scene::CenterF(), ColorF(U"#FDF5FB"));
	}

	void SceneA::fadeIn(double t)
	{
		Scene::Rect().draw(ColorF(0, 1 - t));
	}

	void SceneA::fadeOut(double t)
	{
		Scene::Rect().draw(ColorF(0, t));
	}

	void SceneA::onNavigate(StringView from, StringView to)
	{
		if (to == U"a")
		{
			s3d::Scene::SetBackground(ColorF(U"#F092DD"));
		}
	}

	SceneB::SceneB(entt::registry& registry) : registry(registry)
	{
	}

	void SceneB::update()
	{
		if (KeyEnter.down())
		{
			scene::navigate(registry, U"a", 0.5s);
		}

		FontAsset(U"SceneName")(U"SCENE B\nPress Enter Key").drawAt(Scene::CenterF(), ColorF(U"#2F4D49"));
	}

	void SceneB::fadeIn(double t)
	{
		Scene::Rect().draw(ColorF(0, 1 - t));
	}

	void SceneB::fadeOut(double t)
	{
		Scene::Rect().draw(ColorF(0, t));
	}

	void SceneB::onNavigate(StringView from, StringView to)
	{
		if (to == U"b")
		{
			s3d::Scene::SetBackground(ColorF(U"#81D2C7"));
		}
	}
}

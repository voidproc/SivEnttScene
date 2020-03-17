#include "pch.h"
#include "scenes.h"

void Main()
{
	FontAsset::Register(U"SceneName", 48, Typeface::Bold);

	entt::registry registry;

	scene::makeScene<scenes::SceneA>(registry, U"a");
	scene::makeScene<scenes::SceneB>(registry, U"b");
	scene::navigate(registry, U"a", 0.5s);

	while (System::Update())
	{
		scene::update(registry);
	}
}

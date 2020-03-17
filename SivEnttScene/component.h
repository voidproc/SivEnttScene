#pragma once

//fwd
namespace scenes
{
	struct IScene;
}

namespace components
{
	struct Scene
	{
		std::shared_ptr<scenes::IScene> scene;
		String name;

		Scene(const std::shared_ptr<scenes::IScene>& scene, StringView name)
			: scene(scene), name(name) {}
	};

	using ActiveScene = entt::tag<"ActiveScene"_hs>;

	struct Fade
	{
		Duration time;
		Timer timer;

		Fade(const Duration& time) : time(time), timer(time, true) {}
	};

	struct FadeOut : public Fade
	{
		// ‘JˆÚæƒV[ƒ“–¼
		String to;

		FadeOut(StringView to, const Duration& time) : to(to), Fade(time) {}
	};

	struct FadeIn : public Fade
	{
		using Fade::Fade;
	};
}

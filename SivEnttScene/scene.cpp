#include "pch.h"
#include "scene.h"

namespace scene
{
	namespace
	{
		// アクティブなシーンを to に切り替える
		// 遷移元・遷移先のonNavigate()を呼ぶ
		// フェードインを開始する
		void navigateTo(entt::registry& registry, StringView from, StringView to, const Duration& fade)
		{
			registry
				.view<components::Scene, components::ActiveScene>()
				.each([&](auto& scene, const auto& /*active*/)
					{
						scene.scene->onNavigate(from, to);
					});

			registry
				.view<components::Scene>()
				.each([&](auto entity, auto& scene)
					{
						if (scene.name == to)
						{
							registry.assign<components::ActiveScene>(entity);
							registry.assign<components::FadeIn>(entity, fade);
							scene.scene->onNavigate(from, to);
						}
					});
		}
	}

	void scene::navigate(entt::registry& registry, StringView sceneName, const Duration& fade)
	{
		auto viewActive = registry.view<components::Scene, components::ActiveScene>();

		// アクティブなシーンを探してフェードアウトを開始する
		viewActive.each([&](auto entity, auto& /*scene*/, const auto& /*active*/)
			{
				registry.assign<components::FadeOut>(entity, sceneName, fade);
			});

		// アクティブなシーンがない場合はシーン遷移してフェードインを開始する
		if (viewActive.empty())
		{
			navigateTo(registry, U"", sceneName, fade);
		}
	}

	void update(entt::registry& registry)
	{
		// アクティブなシーンを更新
		registry
			.view<components::Scene, components::ActiveScene>()
			.each([&](auto& scene, const auto& /*active*/)
				{
					scene.scene->update();
				});

		// フェードアウト中
		registry
			.view<components::Scene, components::FadeOut, components::ActiveScene>()
			.each([&](auto entity, auto& scene, auto& fade, const auto& /*active*/)
				{
					scene.scene->fadeOut(fade.timer.progress0_1());

					// フェードアウトが終わった？
					if (fade.timer.reachedZero())
					{
						navigateTo(registry, scene.name, fade.to, fade.time);
						registry.remove<components::FadeOut, components::ActiveScene>(entity);
					}
				});

		// フェードイン中
		registry
			.view<components::Scene, components::FadeIn>()
			.each([&](auto entity, auto& scene, auto& fade)
				{
					scene.scene->fadeIn(fade.timer.progress0_1());

					// フェードインが終わった？
					if (fade.timer.reachedZero())
					{
						registry.remove<components::FadeIn>(entity);
					}
				});
	}
}

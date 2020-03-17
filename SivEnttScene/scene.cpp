#include "pch.h"
#include "scene.h"

namespace scene
{
	namespace
	{
		// �A�N�e�B�u�ȃV�[���� to �ɐ؂�ւ���
		// �J�ڌ��E�J�ڐ��onNavigate()���Ă�
		// �t�F�[�h�C�����J�n����
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

		// �A�N�e�B�u�ȃV�[����T���ăt�F�[�h�A�E�g���J�n����
		viewActive.each([&](auto entity, auto& /*scene*/, const auto& /*active*/)
			{
				registry.assign<components::FadeOut>(entity, sceneName, fade);
			});

		// �A�N�e�B�u�ȃV�[�����Ȃ��ꍇ�̓V�[���J�ڂ��ăt�F�[�h�C�����J�n����
		if (viewActive.empty())
		{
			navigateTo(registry, U"", sceneName, fade);
		}
	}

	void update(entt::registry& registry)
	{
		// �A�N�e�B�u�ȃV�[�����X�V
		registry
			.view<components::Scene, components::ActiveScene>()
			.each([&](auto& scene, const auto& /*active*/)
				{
					scene.scene->update();
				});

		// �t�F�[�h�A�E�g��
		registry
			.view<components::Scene, components::FadeOut, components::ActiveScene>()
			.each([&](auto entity, auto& scene, auto& fade, const auto& /*active*/)
				{
					scene.scene->fadeOut(fade.timer.progress0_1());

					// �t�F�[�h�A�E�g���I������H
					if (fade.timer.reachedZero())
					{
						navigateTo(registry, scene.name, fade.to, fade.time);
						registry.remove<components::FadeOut, components::ActiveScene>(entity);
					}
				});

		// �t�F�[�h�C����
		registry
			.view<components::Scene, components::FadeIn>()
			.each([&](auto entity, auto& scene, auto& fade)
				{
					scene.scene->fadeIn(fade.timer.progress0_1());

					// �t�F�[�h�C�����I������H
					if (fade.timer.reachedZero())
					{
						registry.remove<components::FadeIn>(entity);
					}
				});
	}
}

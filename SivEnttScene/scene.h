#pragma once

#include "component.h"

namespace scenes
{
	struct IScene
	{
		virtual ~IScene() = default;

		// �V�[�����X�V����
		// ���t���[���Ă΂��
		virtual void update() = 0;

		// �V�[���J�ڎ��̃t�F�[�h�C������
		virtual void fadeIn(double /*t*/) {}

		// �V�[���J�ڎ��̃t�F�[�h�A�E�g����
		virtual void fadeOut(double /*t*/) {}

		// scene::navigate()�ɂ��V�[�����J�ڂ���ۂɌĂ΂��
		virtual void onNavigate(StringView /*from*/, StringView /*to*/) {}
	};
}

namespace scene
{
	// �G���e�B�e�B���P�쐬���A�V�[���R���|�[�l���g�icomponents::Scene�j���A�T�C������
	// ����args�ɂ��V�[���I�u�W�F�N�gTScene�iscenes::IScene�j���쐬���V�[���R���|�[�l���g�ɃZ�b�g����
	// ����sceneName�̓V�[���J�ڗp�̃L�[
	template <class TScene, class ... Args>
	void makeScene(entt::registry& registry, StringView sceneName, Args&& ... args)
	{
		auto entity = registry.create();
		registry.assign<components::Scene>(
			entity, std::make_shared<TScene>(registry), sceneName, std::forward<Args>(args)...);
	}
	
	// �V�[��sceneName�ւ̑J�ڂ��J�n����
	void navigate(entt::registry& registry, StringView sceneName, const Duration& fade = 1s);

	// �A�N�e�B�u�ȃV�[���̍X�V�E�t�F�[�h����������
	void update(entt::registry& registry);
}

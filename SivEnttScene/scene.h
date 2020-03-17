#pragma once

#include "component.h"

namespace scenes
{
	struct IScene
	{
		virtual ~IScene() = default;

		// シーンを更新する
		// 毎フレーム呼ばれる
		virtual void update() = 0;

		// シーン遷移時のフェードイン処理
		virtual void fadeIn(double /*t*/) {}

		// シーン遷移時のフェードアウト処理
		virtual void fadeOut(double /*t*/) {}

		// scene::navigate()によりシーンが遷移する際に呼ばれる
		virtual void onNavigate(StringView /*from*/, StringView /*to*/) {}
	};
}

namespace scene
{
	// エンティティを１つ作成し、シーンコンポーネント（components::Scene）をアサインする
	// 引数argsによりシーンオブジェクトTScene（scenes::IScene）を作成しシーンコンポーネントにセットする
	// 引数sceneNameはシーン遷移用のキー
	template <class TScene, class ... Args>
	void makeScene(entt::registry& registry, StringView sceneName, Args&& ... args)
	{
		auto entity = registry.create();
		registry.assign<components::Scene>(
			entity, std::make_shared<TScene>(registry), sceneName, std::forward<Args>(args)...);
	}
	
	// シーンsceneNameへの遷移を開始する
	void navigate(entt::registry& registry, StringView sceneName, const Duration& fade = 1s);

	// アクティブなシーンの更新・フェード処理をする
	void update(entt::registry& registry);
}

#include "Base.hpp"
#include "LiveData.hpp"

void drawFunc(const Vec2& pos1, const Vec2& pos2, const Color& color) {

	const auto d = (pos2 - pos1);
	//const auto pos3 = pos1 + (d / 2).rotated(ToRadians(-30));
	const auto pos3 = pos1 + (d / 2);

	Bezier2(pos1, pos3, pos2).draw(5, Color(color, 63));
	Bezier2(pos1, pos3, pos2).draw(3, Color(color, 63));
	Bezier2(pos1, pos3, pos2).draw(1, Color(color, 63));
}

void movie(LiveData& liveData, const Audio& audio);

void Main() {

	Window::Resize(1920, 1080);
	LiveData::SetIconTexture();

	LiveData liveData;
	const Audio audio(U"InstaVista.mp3");

	Effect debugEffect;
	while (System::Update()) {

		for (const auto& icon : liveData.getIconList()) {

			const ScopedRenderStates2D state(BlendState::Additive);

			const Vec2 pos1 = icon.second.getPos();
			const Vec2 pos2 = Scene::Center();

			drawFunc(pos1, pos2, Palette::White);
		}

		for (const auto& icon : liveData.getIconList()) {
			Circle(LiveData::IconSize / 2 * 1.2).drawShadow(icon.second.getPos(), 16, 0, AlphaF(0.5));
		}
		liveData.showAllIcon();


		if (MouseL.down())
		{
			debugEffect.add<LightCircle>(Cursor::PosF(), (static_cast<double>(LiveData::IconSize) / 2 * 1.2));
		}
		debugEffect.update();

		if (KeySpace.down())
		{
			break;
		}
	}

	{
		Timer timer(3s);
		timer.start();
		while (System::Update())
		{
			const int ms = timer.ms();
			ClearPrint();

			Print << ms << U"ms";
			if (ms <= 0) break;
		}
		ClearPrint();
	}

	movie(liveData, audio);
}

void movie(LiveData& liveData, const Audio& audio) {

	const auto drawTransLine = [&](const Vec2& pos1, const Vec2& pos2, const Color& color) {

		const auto d = (pos2 - pos1);
		//const auto pos3 = pos1 + (d / 2).rotated(ToRadians(-30));
		const auto pos3 = pos1 + (d / 2);

		Bezier2(pos1, pos3, pos2).draw(5, Color(color, 15));
		Bezier2(pos1, pos3, pos2).draw(3, Color(color, 15));
		Bezier2(pos1, pos3, pos2).draw(1, Color(color, 15));
	};

	const auto& liveList = liveData.getLiveList();
	LiveData data = liveData;
	for (auto& m : data.getIconList()) {
		m.second.resetCount();
	}
	data.getIconList(U"黛灰").increment();

	Effect effect;
	Stopwatch sw;
	sw.start();
	int inc = 0;
	const int dtime = 333;


	audio.play();
	while (System::Update()) {
		const auto ms = sw.ms() - 2 * 1000;
		if (ms >= inc * dtime + inc / 3) {
			const int begin = static_cast<int>(liveList.size()) * (inc + 0) / (78 * 3);
			const int end = static_cast<int>(liveList.size()) * (inc + 1) / (78 * 3);

			ClearPrint();
			if (begin < liveList.size()) {
				Print << liveList[end - 1].date;
				forstep(i, begin, end) {
					for (const auto& mem : liveList[i].members) {
						const auto& icon = data.getIconList(mem);
						data.getIconList(mem).increment();

						effect.add<LightLine>(icon.getPos(), data.getIconList(U"黛灰").getPos(), Palette::White);
						effect.add<LightCircle>(icon.getPos(), LiveData::IconSize * 1.2 / 2);
					}
				}
			}

			inc++;
		}

		effect.update();

		for (const auto& mem : data.getIconList()) {
			if (0 < mem.second.getCount()) {
				drawTransLine(mem.second.getPos(), data.getIconList()[U"黛灰"].getPos(), Palette::White);
			}
		}
		data.showIncIcon();
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// Siv3D リファレンス
// https://zenn.dev/reputeless/books/siv3d-documentation
//
// Siv3D Reference
// https://zenn.dev/reputeless/books/siv3d-documentation-en
//
// Siv3D コミュニティへの参加（Slack や Twitter, BBS で気軽に質問や情報交換ができます）
// https://zenn.dev/reputeless/books/siv3d-documentation/viewer/community
//
// Siv3D User Community
// https://zenn.dev/reputeless/books/siv3d-documentation-en/viewer/community
//
// 新機能の提案やバグの報告 | Feedback
// https://github.com/Siv3D/OpenSiv3D/issues
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//

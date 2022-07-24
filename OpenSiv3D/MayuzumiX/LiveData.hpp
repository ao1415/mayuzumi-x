#pragma once

#include "base.hpp"

class LiveData {
public:
	using LiveList = Array<LiveObject>;
	using IconList = std::map<String, IconObject>;

	inline static const int IconSize = 48;

private:

	LiveList liveList;
	IconList iconList;
	const Font font;

	void setLiveList() {

		liveList = LiveList();

		JSON json = JSON::Load(U"../../../src/assets/live.json");

		for (const auto& object : json.arrayView())
		{
			LiveObject item;
			item.date = object[U"date"].getString();

			const auto members = object[U"members"].arrayView();
			for (const auto& elem : members) {
				item.members.push_back(elem.getString());
			}
			if (not item.members.empty()) {
				liveList.push_back(item);
			}
		}
	}

	void setIconList() {

		iconList = IconList();

		for (const auto& data : liveList) {
			for (const auto& member : data.members) {
				if (!iconList.contains(member)) {
					iconList[member].setName(member);
				}
				iconList[member].increment();
			}
		}
	}

	void setIconPos() {
		Array<std::pair<int, String>> list;

		for (const auto& data : iconList) {
			list.push_back({ data.second.getCount(),data.first });
		}
		list.sort_by(std::greater<>());

		const double R = IconSize * 1.5;
		int rIndex = 1;
		int index = 0;
		{
			int i = 0;
			while (i < list.size()) {

				const double r = R * rIndex + IconSize;
				const double length = Math::TwoPi * r;
				const int rMax = static_cast<int>(length / (IconSize * 1.5));

				const double dd = Math::TwoPi / rMax;
				const double d = dd * index + (Math::Pi * (rIndex - 1) * 3 / 180);
				const int x = static_cast<int>(Math::Cos(d) * r * 1.20 + Scene::Center().x);
				const int y = static_cast<int>(Math::Sin(d) * r * 1.00 + Scene::Center().y);

				index++;
				if (rMax <= index) {
					index = 0;
					rIndex++;
				}
				if (y < IconSize || Scene::Size().y - (IconSize) < y) {
					continue;
				}

				iconList[list[i].second].setPos(Point(x, y));
				i++;
			}
		}

		iconList[U"黛灰"].setName(U"黛灰");
		iconList[U"黛灰"].setPos(Scene::Center());
	}

public:

	static void SetIconTexture() {

		const auto iconPathList = FileSystem::DirectoryContents(U"./icons");

		for (const auto& path : iconPathList)
		{
			const String name = FileSystem::BaseName(path);
			TextureAsset::Register(name, path);
		}
	}

	LiveData() : font(Font{ 16,Typeface::CJK_Regular_JP }) {
		setLiveList();
		setIconList();

		setIconPos();
	}

	[[nodiscard]] LiveList& getLiveList() { return liveList; }
	[[nodiscard]] IconList& getIconList() { return iconList; }
	[[nodiscard]] IconObject& getIconList(const String key) { return iconList.at(key); }

	void showAllIcon() const {

		for (const auto& icon : iconList) {
			Circle circle(icon.second.getPos(), IconSize / 2);

			const auto& texture = TextureAsset(icon.first);
			if (texture.isEmpty()) {
				circle.setR(IconSize);
				circle.draw(Palette::Gray);
			}
			else {
				circle(texture.resized(IconSize)).draw();
			}
			font(icon.first).drawAt(circle.center);
		}

	}

	void showIncIcon() const {

		for (const auto& icon : iconList) {
			if (0 < icon.second.getCount()) {
				Circle circle(icon.second.getPos(), IconSize / 2);

				const auto& texture = TextureAsset(icon.first);
				if (texture.isEmpty()) {
					circle.draw(Palette::Gray);
				}
				else {
					circle(texture.resized(IconSize)).draw();
				}
			}
		}

	}

};

#pragma once

#include <Siv3D.hpp>

#ifndef _MSC_VER
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

#define WARN_PUSH_DISABLE(x)
#define WARN_POP()
#else
#include <iso646.h>

#define LIKELY(x) x
#define UNLIKELY(x) x

#define WARN_PUSH_DISABLE(x) __pragma(warning(push))\
__pragma(warning(disable:x))
#define WARN_POP() __pragma(warning(pop))
#endif

// [0, END)でCOUNTERを増加させる
#define forange(COUNTER, END) forstep_type(std::remove_cvref_t<decltype(END)>, COUNTER, std::remove_cvref_t<decltype(END)>(), END)
// [0, END)で指定された型のCOUNTERを増加させる
#define forange_type(COUNTER_TYPE, COUNTER, END) forstep_type(COUNTER_TYPE, COUNTER, std::remove_cvref_t<COUNTER_TYPE>(), END)
// [BEGIN, END)でCOUNTERを増加させる
#define forstep(COUNTER, BEGIN, END) forstep_type(std::remove_cvref_t<decltype(BEGIN)>, COUNTER, BEGIN, END)
// [BEGIN, END)で指定された型のCOUNTERを増加させる
#define forstep_type(COUNTER_TYPE, COUNTER, BEGIN, END) \
WARN_PUSH_DISABLE(26496 26498)\
for (COUNTER_TYPE COUNTER = static_cast<COUNTER_TYPE>(BEGIN), _loop_end_##COUNTER = static_cast<COUNTER_TYPE>(END); COUNTER < _loop_end_##COUNTER; COUNTER++)\
WARN_POP()

#define NODISCARD [[nodiscard]]

/**
 * Liveデータ.
 */
struct LiveObject {
	String date;
	Array<String> members;
};

class IconObject {
private:

	int counter = 0;

	String name{};
	Vec2 pos{};

public:

	IconObject() = default;

	void setName(const String& _name) {
		name = _name;
	}
	const String& getName() const {
		return name;
	}
	void setPos(const Vec2& _pos) {
		pos = _pos;
	}
	const Vec2& getPos() const {
		return pos;
	}

	void increment() {
		counter++;
	}

	void resetCount() {
		counter = 0;
	}

	int getCount() const {
		return counter;
	}

};

/**
 * アイコン点滅用のエフェクト.
 */
class LightCircle : public IEffect {
private:

	Vec2 pos;
	double r;

public:

	LightCircle(const Vec2& _pos, const double _r) {
		pos = _pos;
		r = _r;
	}

	bool update(double t) override {

		const double e = 1.0 - EaseInCirc(Min(t, 1.0));

		const ScopedRenderStates2D state(BlendState::Additive);
		Circle(r).drawShadow(pos, 16, 0, AlphaF(e * 3 / 4));

		return t < 1.0;
	}

};

/**
 * 線分用のエフェクト.
 */
class LightLine : public IEffect {
private:

	Vec2 pos1;
	Vec2 pos2;
	Color color;

public:

	LightLine(const Vec2& _pos1, const Vec2& _pos2, const Color& _color) {
		pos1 = _pos1;
		pos2 = _pos2;
		color = _color;
	}

	bool update(double t) override {

		const double e = 1.0 - EaseInCirc(Min(t, 1.0));

		const auto d = (pos2 - pos1);
		//const auto pos3 = pos1 + (d / 2).rotated(ToRadians(-30));
		const auto pos3 = pos1 + (d / 2);

		const ScopedRenderStates2D state(BlendState::Additive);
		Bezier2(pos1, pos3, pos2).draw(5, ColorF(color, e / 4));
		Bezier2(pos1, pos3, pos2).draw(3, ColorF(color, e / 4));
		Bezier2(pos1, pos3, pos2).draw(1, ColorF(color, e / 4));

		return t < 1.0;
	}

};

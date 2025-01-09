#pragma once
#include <memory>
#include <iostream>
#include "container.h"
#include "control.h"

// std::shared_ptr<T>

namespace termform {

	class row_container : public container {
	
	protected:
	
	public:
		paint_return paint(int x, int y) override {
			std::string str{};
			int y_pos = y;
			for (const auto& c : components) {
				auto ret = c->paint(x, y_pos);
				y_pos += ret.height;
				str += ansi_escape_code::get(x, y_pos, c->get_paint_color(), c->get_paint_background(), ret.string);
			}
			return { x,y_pos - y,str };
		}
	};
}
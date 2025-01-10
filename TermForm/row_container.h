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
		paint_return paint(int x, int y, bool force) override {
			std::string str{};
			int y_pos = y;
			for (const auto& c : components) {
				bool is_invalid = c->invalid();
				auto ret = c->paint(x, y_pos, force);
				y_pos += ret.height;
				if (is_invalid || force)
				{
					std::string str_plus_padding = ret.string;
					//str_plus_padding.append(_width - ret.width, ' ');
					str += ansi_escape_code::get(x, y_pos, c->get_paint_color(), c->get_paint_background(), str_plus_padding);
				}
			}
			return { x,y_pos - y,str };
		}
	};
}
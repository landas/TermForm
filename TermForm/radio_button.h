#pragma once
#include <vector>
#include <iostream>
#include "component.h"
#include "control.h"

namespace termform {

	class radio_button : public control {

	public:
		radio_button(const std::string& group) : control() {
			_focusable = true;
			_group_hash = string_hash_16(group);
			_radio_buttons.push_back(this);
		}

		~radio_button() {
			auto it = std::find(_radio_buttons.begin(), _radio_buttons.end(), this);
			if (it != _radio_buttons.end()) {
				_radio_buttons.erase(it);
			}
		}

		inline std::string label() {
			return text();
		}

		inline void label(const std::string& label) {
			text(label);
		}

		inline void on_text_change(const std::string& value) override {
			auto size = string_boxsize("(o) " + value);
			_text = value;
			_width = size.width;
			_height = size.height;
		}

		radio_button* get_selected() {
			for (const auto& e : _radio_buttons) {
				if (e->_group_hash == _group_hash && e->is_selected()) {
					return e;
				}
			}
			return nullptr;
		}

		inline bool is_selected() const {
			return _selected;
		}

		void select() {
			if (!_selected) {
				auto prev_selected = get_selected();
				if (prev_selected != nullptr) {
					prev_selected->_selected = false;
					prev_selected->trigger_change();
				}

				_selected = true;
				trigger_change();
			}
		}

		bool input(int c) override {
			if (c == 32 || c == 13) {
				select();
				return true;
			}
			return false;
		}

		paint_return paint(int x, int y) override {
			return { _width, _height, control::concat_string(is_selected() ? "(o) " : "( ) ", "")};
		}

	private:
		static std::vector<radio_button*> _radio_buttons;
		uint16_t _group_hash{ 0 };
		bool _selected{ false };
	};
}
#pragma once

#include "component.h"
#include "container.h"
#include "tools.h"

namespace termform {

	class control : public component {
	protected:
		std::string _text{ };
		event_handler* _on_change{ nullptr };

	public:
		
		inline paint_return paint(int x, int y, bool force) override {
			auto size = string_boxsize(_text);
			invalid(false);
			return { size.width, size.height, _text };
		}
		
		inline std::string concat_string(std::string front, std::string back) const {
			return front + _text + back;
		}

		std::string text() {
			return _text;
		}

		void text(const std::string& value) {
			if (_text != value) {
				on_text_change(value);
			}
		}

		inline void set_on_change(event_handler* h) {
			_on_change = h;
		}

		bool input(int) override {
			return false;
		}	

		form* get_form() override {
			auto p = parent();
			if (p != nullptr) {
				return p->get_form();
			}
			return nullptr;
		}

	protected:
		bool trigger_change() {
			if (_on_change != nullptr) {
				return _on_change(*this);
			}
			return false;
		}

		virtual void on_text_change(const std::string& value)
		{
			_text = value;
			_width = _text.length() - ansi_escape_code::metadata_lenght(_text);
			_height = ansi_escape_code::count_newlines(_text) + 1;
			trigger_change();
		}

	friend class container;
	};
}


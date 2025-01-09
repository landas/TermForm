#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <type_traits>
#include "component.h"
#include "tools.h"

namespace termform {

	class container : public component {
	
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<component, T>>>
		void add(std::shared_ptr<T> ptr_object)
		{
			ptr_object->x(0);
			ptr_object->parent(this);
			components.push_back(std::static_pointer_cast<component>(ptr_object));
		}

		paint_return paint(int x, int y) override {
			string_vector v{};
			std::string str{};
			int y_pos = y;
			for (const auto &c : components) {
				auto ret = c->paint(x, y_pos);
				y_pos += ret.height;
				str += ansi_escape_code::get(x, y_pos, c->get_paint_color(), c->get_paint_background(), ret.string);	
			}
			return {x,y_pos,str};
		}

		bool input(int chr) override;
		bool try_give_focus() override;
		bool try_give_focus_back() override;
		bool move_cursor_to_next();
		bool move_cursor_to_prev();

		form* get_form() override {

			if (_form != nullptr)
				return _form;

			auto p = parent();
			if (p != nullptr) {
				return p->get_form();
			}
			return nullptr;
		}

	protected:
		inline void set_form(form* pform) {
			_form = pform;
		}

	protected:
		std::vector<component_ptr> components{};
		form* _form{ nullptr };
		component_ptr cursor{ nullptr };

	friend class form;

	};
}
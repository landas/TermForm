#pragma once

#include <iostream>
#include <memory>
#include <type_traits>
#include "ansi_escape_codes.h"
#include "tools.h"
#include "paint_return.h"
#include "container.h"
#include "row_container.h"
#include "control.h"
#include "label.h"
#include "button.h"
#include "checkbox.h"
#include "radio_button.h"
#include "textfield.h"

namespace termform {

	class form {
	protected:
		container_ptr base_container{ nullptr };
		print_function* _print{ nullptr };
		std::string _status{};
		int16_t _width{ 0 };
		int16_t _height{ 0 };
		bool _quit{ false };

	public:
		template <typename T, class... Args, typename = std::enable_if_t<std::is_base_of_v<control, T>>>
		static std::shared_ptr<T> make_control(Args... args)
		{
			return std::shared_ptr<T> { new T(std::forward<Args>(args)...) };
		}

		template <typename T, class... Args, typename = std::enable_if_t<std::is_base_of_v<container, T>>>
		static std::shared_ptr<T> make_container(Args... args)
		{
			return std::shared_ptr<T> { new T(std::forward<Args>(args)...) };
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<container, T>>>
		void set(std::shared_ptr<T> ptr_object)
		{
			if (base_container != nullptr) {
				base_container->set_form(nullptr);
			}

			base_container = std::static_pointer_cast<container>(ptr_object);
			base_container->x(0);
			base_container->y(0);
			base_container->set_form(this);
			base_container->try_give_focus();
		}

		form(int width, int height) : form(width, height, nullptr) { }
		form(int width, int height, print_function* print) : _width(width), _height(height), _print(print) { }

		void set_print_function(print_function* print) {
			_print = print;
		}

		void input(int chr) {
			if (!base_container->input(chr)) {
				//handle something here?
			}
		}

		inline void quit() {
			_quit = true;
		}

		inline bool is_quitting() const {
			return _quit;
		}

		inline std::string status() const {
			return _status;
		}

		inline void status(const std::string& s) {
			_status = s;
		}

		inline void display() const {
			print(ansi_escape_code::get_clear_all());
			print(ansi_escape_code::get_hide_cursor());
			auto ret = base_container->paint(1, 1);
			print(ret.string);
			display_status();
		}

		inline void print(const std::string& s) const {
			if (_print != nullptr)
				_print(s);
		}
	private:
		void display_status() const {
			print(ansi_escape_code::get_move(0, _height-1) + 
				ansi_escape_code::get(ansi_escape_code::color::standard) + 
				ansi_escape_code::get(ansi_escape_code::background::standard) +
				_status);
		}
	};
}
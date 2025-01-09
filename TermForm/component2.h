#pragma once

#include "tools.h"
#include "ansi_escape_codes.h"

namespace termform {


	class component2 {

	public:
		virtual ~component2() = default;
		virtual string_vector paint(int x, int y) const = 0;
		virtual bool input(int) = 0;

	protected:
		
		// event handlers
		event_handler* _on_focus{ nullptr };
		event_handler* _on_leave{ nullptr };
		input_event_handler* _on_input{ nullptr };

		container* _parent{ nullptr };
		/*
		int16_t _x{ 0 };
		int16_t _y{ 0 };
		int16_t _width{ 0 };
		int16_t _height{ 0 };


		union {
			char flags{ 0 };
			struct {
				bool _focusable : 1;
				bool _has_focus : 1;
				char : 2;
			};
		};

		ansi_escape_code::color _color{ ansi_escape_code::color::standard };
		ansi_escape_code::background _background{ ansi_escape_code::background::standard };
		ansi_escape_code::color _color_selected{ ansi_escape_code::color::black };
		ansi_escape_code::background _background_selected{ ansi_escape_code::background::white };
		*/

	};
}
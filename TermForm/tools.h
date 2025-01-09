#pragma once
#include <string>
#include <memory>
#include <vector>



namespace termform {
	class component;
	class container;
	class control;

	constexpr struct {
		int16_t arrow_up = 1000;
		int16_t arrow_down = 1001;
		int16_t arrow_left = 1002;
		int16_t arrow_right = 1003;
	} keycode;

	struct position {
		int x{ 0 };
		int y{ 0 };
	};
	
	struct boxsize {
		int width{ 0 };
		int height{ 0 };
	};

	struct rect {
		int x{ 0 };
		int y{ 0 };
		int width{ 0 };
		int height{ 0 };
	};

	boxsize string_boxsize(const std::string&);
	uint16_t string_hash_16(const std::string&);
	
	using event_handler = bool(component&);// std::function<bool(component&)>;
	using input_event_handler = bool(component&, int); // std::function<bool(component&, int)>;

	using print_function = void(const std::string&); //std::function<void(std::string)>;

	using component_ptr = std::shared_ptr<component>;
	using container_ptr = std::shared_ptr<container>;
	using control_ptr = std::shared_ptr<control>;
	using string_vector = std::vector<std::string>;
}
#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "component.h"

namespace termform {

	class container : public component {
	protected:
		std::vector<std::shared_ptr<component>> objects{};
	
	public:
		template<typename T, typename = std::enable_if_t<std::is_base_of_v<component, T>>>
		void add(std::shared_ptr<T> ptr_object)
		{
			objects.push_back(std::static_pointer_cast<component>(ptr_object));
		}

		void print() const override {
			for (auto &c : objects) {
				c->print();
			}
		}
	};
}
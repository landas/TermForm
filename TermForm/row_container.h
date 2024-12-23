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
		void print() {
			for (auto& c : this->objects) {
				c->print();
				std::cout << std::endl;
			}
		}
	};
}
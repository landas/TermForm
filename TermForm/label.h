#pragma once

#include "component.h"
#include "control.h"

namespace termform {

	class label : public control {

	public:
		bool input(int) override {
			return false;
		}

	};
}
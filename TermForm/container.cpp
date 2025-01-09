#include "container.h"

namespace termform {
	bool container::input(int chr) {
		if (!cursor->input(chr)) {
			switch (chr) {
			case keycode.arrow_down: // DOWN
				move_cursor_to_next();
				return true;
			case keycode.arrow_up: // UP
				move_cursor_to_prev();
				return true;
			case 75: // LEFT
			case 77: // RIGHT
			default:
				break;

			}

			return false;
		}
		return true;
	}

	bool container::try_give_focus() {
		if (cursor != nullptr)
			cursor->release_focus();

		for (auto& e : components) {
			if (e->try_give_focus())
			{
				cursor = e;
				return true;
			}
		}
		return false;
	}	
	
	bool container::try_give_focus_back() {
		if (cursor != nullptr)
			cursor->release_focus();

		for (auto it = components.rbegin(); it != components.rend(); ++it) {
			if ((*it)->try_give_focus_back()) {
				cursor = *it;
				return true;
			}
		}

		return false;
	}


	bool container::move_cursor_to_next() {
		if(cursor != nullptr) 
			cursor->release_focus();

		auto it = std::find(components.begin(), components.end(), cursor);
		if (it != components.end())
		{
			++it;
			while (it != components.end())
			{
				if ((*it)->try_give_focus()) {
					cursor = *it;
					return true;
				}
				++it;
			}
		}

		if (_parent != nullptr) {
			if (_parent->move_cursor_to_next()) {
				return true;
			}
		}

		return try_give_focus();
	}

	bool container::move_cursor_to_prev() {
		if (cursor != nullptr)
			cursor->release_focus();

		{
			auto it = std::find(components.rbegin(), components.rend(), cursor);
			if (it != components.rend())
			{
				++it;
				while (it != components.rend())
				{
					if ((*it)->try_give_focus_back()) {
						cursor = *it;
						return true;
					}
					++it;
				}
			}
		}

		if (_parent != nullptr) {
			if (_parent->move_cursor_to_prev()) {
				return true;
			}
		}

		return try_give_focus_back();
	}
}
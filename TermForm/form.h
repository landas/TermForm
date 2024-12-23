#pragma once

#include <iostream>
#include <memory>
#include <type_traits>
#include "tools.h"
#include "container.h"
#include "row_container.h"
#include "control.h"
#include "text.h"

namespace termform {

	class form {
	protected:
		std::shared_ptr<container> base_container;
		std::shared_ptr<component> cursor;

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
		void add(std::shared_ptr<T> ptr_object)
		{
			base_container = std::static_pointer_cast<container>(ptr_object);
		}

		inline void print() const {
			base_container->print();
		}
	};
}
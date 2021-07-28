#pragma once

namespace ft{
	template< bool CONDITION, typename TYPE = void >
	struct enable_if{};

	template< typename TYPE >
	struct enable_if< true, TYPE > {
		typedef TYPE type;
	};
}

#ifndef BEDROCK_DEF_HPP
#define BEDROCK_DEF_HPP

// Common definitions.

namespace br {
	namespace codes {
		// todo: consult unix spec for error numbers
		constexpr int SUCCESS = 0;
		constexpr int FAILURE = 1;
	}


	#define STR(x) STR2(x)
	#define STR2(x) #x
}

#endif

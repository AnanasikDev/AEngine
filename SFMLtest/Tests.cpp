#define CATCH_CONFIG_MAIN

#include "catch_amalgamated.hpp"

#include "Vector.h"
#include "Mathf.h"
#include "Physics.h"
#include "Bounds.h"

TEST_CASE("Vector operations") {
	REQUIRE(aengine::Vectorf(3, 4).getLength() == 5);
}

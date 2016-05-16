#include <gtest/gtest.h>
#include <hugeint.h>

using hugeint::hugeint_t;

TEST( hugeint_constructors, default_constructor )
{
    hugeint_t x;
    ASSERT_EQ( 1, x.v.size( ) );
    EXPECT_EQ( 0, x.v[ 0 ] );
}
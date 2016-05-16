#include <gtest/gtest.h>
#include <hugeint.h>

namespace hi = hugeint;

TEST( hugeint_constructors, default_constructor )
{
    hi::hugeint_t x;
    ASSERT_EQ( 1, x.v.size( ) );
    EXPECT_EQ( 0, x.v[ 0 ] );
}

TEST( hugeint_constructors, int_constructor )
{
    hi::hugeint< 3 > x( 1 );
    ASSERT_EQ( 1, x.v.size( ) );
    EXPECT_EQ( 1, x.v[ 0 ] );
    x = 1234567890;
    ASSERT_EQ( 4, x.v.size( ) );
    EXPECT_EQ( 890, x.v[ 0 ] );
    EXPECT_EQ( 567, x.v[ 1 ] );
    EXPECT_EQ( 234, x.v[ 2 ] );
    EXPECT_EQ( 1, x.v[ 3 ] );
}

TEST( hugeint_constructors, string_constructor )
{
    hi::hugeint< 3 > x( "1234567891234567891234567890" );
    ASSERT_EQ( 10, x.v.size( ) );
    hi::int_t expected[] = {890, 567, 234, 891, 567, 234, 891, 567, 234, 1};
    for ( size_t i = 0; i < 10; i++ )
    {
        EXPECT_EQ( expected[ i ], x.v[ i ] );
    }
}

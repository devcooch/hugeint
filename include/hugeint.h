#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace hugeint
{
typedef unsigned long long int int_t;

template < int N >
struct hugeint
{
    static_assert( N >= 1, "N >= 1" );
    static_assert( N <= 9, "N <= 9" );

    static constexpr int_t
    get_one( int_t n )
    {
        return n == 1 ? 9 : get_one( n - 1 ) * 10 + 9;
    }

    static constexpr int_t one = get_one( N );

    static constexpr int_t den = one + 1;

    hugeint( int_t x = 0 )
    {
        while ( x > 0 )
        {
            v.push_back( x % den );
            x /= den;
        }
        if ( v.empty( ) )
        {
            v.push_back( 0 );
        }
    }

    hugeint( const char* s, size_t len )
    {
        auto char_to_int = []( const char* begin, const char* end ) {
            int_t result = 0;
            while ( begin != end )
            {
                if ( *begin < '0' || *begin > '9' )
                {
                    throw std::runtime_error( "non-integer digit during conversion from char*" );
                }
                result *= 10;
                result += *begin - '0';
                ++begin;
            }
            return result;
        };
        size_t leading_count = len % N;
        size_t other_count = len / N;
        for ( size_t i = other_count; i > 0; --i )
        {
            v.push_back(
                char_to_int( s + leading_count + ( i - 1 ) * N, s + leading_count + i * N ) );
        }
        if ( leading_count > 0 )
        {
            v.push_back( char_to_int( s, s + leading_count ) );
        }
    }

    hugeint( const std::string& s )
        : hugeint( &s[ 0 ], s.size( ) )
    {
    }

    hugeint&
    operator+( const hugeint& other )
    {
        for ( size_t i = 0; i < other.v.size( ); ++i )
        {
            v[ i ] += other.v[ i ];
            size_t p = i;
            while ( v[ p ] > one )
            {
                v[ p++ ] %= den;
                if ( p == v.size( ) )
                {
                    v.push_back( 0 );
                }
                ++v[ p ];
            }
        }
        return *this;
    }

    hugeint&
    operator-( const hugeint& other )
    {
        if ( *this < other )
        {
            throw std::runtime_error( "hugeint does not support signed numbers!" );
        }
        return *this;
    }

    static int cmp( const hugeint& x, const hugeint& y )
    {
        if ( x.v.size( ) < y.v.size( ) )
        {
            return -1;
        }
        if ( x.v.size( ) > y.v.size( ) )
        {
            return 1;
        }
        for ( size_t i = x.v.size( ); i > 0; --i )
        {
            if ( x.v[ i - 1 ] < y.v[ i - 1 ] )
            {
                return -1;
            }
            if ( x.v[ i - 1 ] > y.v[ i - 1 ] )
            {
                return 1;
            }
        }
        return 0;
    }

    bool
    operator<( const hugeint& other )
    {
        return cmp( *this, other ) < 0;
    }

    bool
    operator>( const hugeint& other )
    {
        return cmp( *this, other ) > 0;
    }

    bool
    operator==( const hugeint& other )
    {
        return cmp( *this, other ) == 0;
    }

    bool
    operator!=( const hugeint& other )
    {
        return cmp( *this, other ) != 0;
    }

    std::vector< int_t > v;
};

typedef hugeint< 3 > hugeint_t;

hugeint_t operator"" _huge( const char* s, size_t len )
{
    return hugeint_t( s, len );
}

hugeint_t operator"" _huge( int_t i )
{
    return hugeint_t( i );
}

namespace
{
class keep_flags
{
public:
    keep_flags( std::ostream& s )
        : m_ff( s.flags( ) )
        , m_s( s ){};
    ~keep_flags( )
    {
        m_s.flags( m_ff );
    };

private:
    std::ios_base::fmtflags m_ff;
    std::ostream& m_s;
};
}

template < int N >
std::ostream&
operator<<( std::ostream& os, const hugeint< N >& x )
{
    os << *x.v.rbegin( );
    keep_flags kf( os );
    for ( auto it = x.v.rbegin( ) + 1; it != x.v.rend( ); ++it )
    {
        os << std::setw( N ) << std::setfill( '0' ) << *it;
    }
    os << '[' << x.v.size( ) << ']';
    return os;
}
}

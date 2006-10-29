/** -*- C++ -*-
*/

#ifdef HAVE_GC
#include <gc/gc_cpp.h>
#include <gc/gc_allocator.h>
#endif

#include <vector>

#ifndef WIBBLE_SHARED_H
#define WIBBLE_SHARED_H

namespace wibble {

template< typename T >
struct SharedVector :
#ifdef HAVE_GC
    gc, std::vector< T, gc_allocator< T > >
#else
    std::vector< T >
#endif
{
};

template< typename T >
T &shared() {
#ifdef HAVE_GC
    return *(new (GC) T());
#else // leak memory
    return *(new T());
#endif
}

}

#endif
// kate: indent-width 4; replace-tabs on; tab-width 4; space-indent on;
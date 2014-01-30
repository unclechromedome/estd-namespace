#ifndef DEFAULT_T_H
#define DEFAULT_T_H

namespace Estd {

// default_t is just a "dummy" or "tag" type used for ADL (pp 395-396).
// When used as a parameter in functions, it causes the Estd namespace
// to be searched for the function names.

struct default_t { };

}	// namespace Estd

#endif	// DEFAULT_T_H

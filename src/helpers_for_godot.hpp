#if !HELPERS_FOR_GODOT_HPP
#define HELPERS_FOR_GODOT_HPP 
#include "godot_cpp/core/class_db.hpp"

#define BIND_METHOD_NO_ARGS(class, method)/********************************** */\
    ::godot::ClassDB::bind_method( ::godot::D_METHOD( #method ), &class::method);

#endif //UTIL_FOR_GODOT_HPP
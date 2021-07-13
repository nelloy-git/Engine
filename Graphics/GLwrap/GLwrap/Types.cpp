#include "GLwrap/Types.h"

#include "MagicEnum.h"

using namespace GLwrap;

constexpr char *toString(DrawMode mode){
    constexpr auto type_name = magic_enum::enum_type_name<DrawMode>();
    auto name = magic_enum::enum_name(mode);
    
    return 
}
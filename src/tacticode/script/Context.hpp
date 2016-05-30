#pragma once

#include "wrapper.hpp"

#include "v8/include/v8.h"

namespace tacticode{
namespace script{

class Context : Wrapper<Handle<v8::Context> >{

};

}//script
}//tacticode
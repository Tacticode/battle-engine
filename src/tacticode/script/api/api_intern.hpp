#pragma once

/* *******************************************************************
 * This is a nested module to regroupe all api calls
 * ******************************************************************/

namespace tacticode{
namespace script{
namespace api{

}//api
}//script
}//tacticode

//Array already natively supported under Array namespace
/* *******************************************************************
 * var a = [1, 2]
 * a.forEach(...)
 * ******************************************************************/
//Math already natively supported under Math namespace
/* *******************************************************************
 * Math.round
 * ******************************************************************/       

/* *******************************************************************
 * dependency
 * ******************************************************************/         
#include "tacticode/script/Context.hpp"

#include "ApiCollection.hpp"
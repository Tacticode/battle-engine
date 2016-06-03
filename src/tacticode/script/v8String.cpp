#include "v8String.hpp"

namespace tacticode{
namespace script{

v8String::v8String(std::string const& str) {
	_resource = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), str.c_str(),
				v8::NewStringType::kNormal).ToLocalChecked();
}

v8String::~v8String() {

}

}//script
}//tacticode
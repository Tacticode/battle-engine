#include "v8String.hpp"

namespace tacticode{
namespace script{

v8String::v8String(std::string const& str) {
	_resource = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), str.c_str(),
				v8::NewStringType::kNormal).ToLocalChecked();
}

v8String::~v8String() {

}

v8::Handle<v8::String> v8String::fromString(std::string const& str) {
	return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), str.c_str(),
				v8::NewStringType::kNormal).ToLocalChecked();
}

std::string v8String::toString(v8::Handle<v8::String> v8str) {
	v8::String::Utf8Value utf8value(v8str);
  std::string str(*utf8value);
  return str;
}

}//script
}//tacticode
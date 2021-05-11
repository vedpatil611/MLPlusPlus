#pragma once

#include <memory>

template<typename T>
using Rc = std::shared_ptr<T>;

template<typename T>
using Scope = std::unique_ptr<T>;

#define PROPERTY(x, y) if(x != nullptr) x -> y

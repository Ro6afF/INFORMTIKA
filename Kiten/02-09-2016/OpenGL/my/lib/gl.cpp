#include "gfw.hpp"
namespace gfw{

GLCacheEntry::~GLCacheEntry(){}

GLCacheEntry *&GLContext::cache_get(const std::type_info &key){
	return cache_entries[key];
}

GLCacheEntry *GLContext::cache_pop(const std::type_info &key){
	auto it=cache_entries.find(key);
	if(it==cache_entries.end()) return nullptr;
	GLCacheEntry *res=it->second;
	cache_entries.erase(it);
	return res;
}

}

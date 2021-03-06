#pragma once

#ifdef OPENMIND_MATH_USE_LEVELDB_CACHE
#include <leveldb/db.h>
#else
namespace leveldb{
class DB;
}
#endif
#include <future>
#include <memory>
#include <string>

#include <Variable.h>

namespace omnn::math {
    
    class Cache
    {
    public:
        using path_str_t = std::string;
        using CheckCacheResult = std::pair<bool,Valuable>;

        class Cached : public std::future<CheckCacheResult> {
            using base = std::future<CheckCacheResult>;
        public:
            using base::base;
            Cached(base&& b);
            operator bool();
            operator Valuable();
            bool NotInCache();
        };
        
    private:
        leveldb::DB* db = nullptr;
        path_str_t path;
        
        void DbOpen();
        
    protected:
        std::string Value(const std::string& key);
        
    public:
        Cache(const path_str_t& path);
        ~Cache();

        Cached AsyncFetch(const Valuable& v, bool itIsOptimized = false);
        CheckCacheResult GetOne(const std::string& key, const Valuable::va_names_t& vaNames, bool itIsOptimized = false);

        bool Set(const std::string& key, const std::string& v);
        void AsyncSet(std::string&& key, std::string&& v);
    };
}

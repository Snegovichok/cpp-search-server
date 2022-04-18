#include <cstdlib>
#include <future>
#include <map>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <execution>

using namespace std::string_literals;

template <typename Key, typename Value>
class ConcurrentMap {
public:
    static_assert(std::is_integral_v<Key>, "ConcurrentMap supports only integer keys"s);

    struct Access {
        Access(std::mutex& mutex_value, Value& v) : mutex_(mutex_value), ref_to_value(v) {
        }

        ~Access() {
            mutex_.unlock();
        }

        std::mutex& mutex_;
        Value& ref_to_value;
    };

    explicit ConcurrentMap(size_t bucket_count) :
        buckets_(bucket_count),
        mutexes_(bucket_count) {}

    Access operator[](const Key& key) {
        size_t index = static_cast<uint64_t>(key) % buckets_.size();
        mutexes_[index].lock();

        return Access(mutexes_[index], buckets_[index][key]);
    }

    std::map<Key, Value> BuildOrdinaryMap()
    {
        std::map<Key, Value> result;
        for (std::size_t idx = 0; idx < buckets_.size(); ++idx) {
            std::lock_guard<std::mutex> guard(mutexes_[idx]);

            for (auto const& [k, v] : buckets_[idx]) {
                result[k] = v;
            }
        }

        return result;
    }
private:
    std::vector<std::map<Key, Value>> buckets_;
    std::vector<std::mutex> mutexes_;
};
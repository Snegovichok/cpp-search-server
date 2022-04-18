#include <vector>

#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server) : search_server_(search_server) {
}

int RequestQueue::GetNoResultRequests() const {
    return requests_.size() - request_older;
}

void RequestQueue::AddRequest(int results_num) {
    // новый запрос - новая секунда
    ++current_time_;
    // удаляем все результаты поиска, которые устарели
    if (current_time_ > sec_in_day_) {
        requests_.pop_front();
        --current_time_;
        ++request_older;
    }

    requests_.push_back(results_num);
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    return AddFindRequest(raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
        return document_status == status;
        });
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
}
#pragma once

#include <deque>
#include <vector>
#include <string>

#include "search_server.h"
#include "document.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);

    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);

    int GetNoResultRequests() const;
private:
    struct QueryResult {
        QueryResult(const int result) : results_(result) {
        }
        int results_;
    };

    void AddRequest(int results_num);

    std::deque<QueryResult> requests_;
    const static int sec_in_day_ = 1440;
    SearchServer search_server_;
    int current_time_ = 0;
    int request_older = 1;
};


template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
    auto matched_documents = search_server_.FindTopDocuments(raw_query, document_predicate);
    AddRequest(matched_documents.size());
    return matched_documents;
}
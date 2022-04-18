#include "process_queries.h"

#include <execution>

using namespace std;

vector<vector<Document>> ProcessQueries(
    const SearchServer& search_server,
    const vector<string>& queries) {

    vector<vector<Document>> documents(queries.size());

    transform(
        execution::par,
        queries.begin(),
        queries.end(),
        documents.begin(),
        [&search_server](const auto& str) {
            return search_server.FindTopDocuments(str);
        });

    return documents;
}

vector<Document> ProcessQueriesJoined(const SearchServer& search_server, const vector<string>& queries) {
    vector<Document> documents;
    for (const auto& local_documents : ProcessQueries(search_server, queries)) {
        documents.insert(documents.end(), local_documents.begin(), local_documents.end());
    }
    return documents;
}
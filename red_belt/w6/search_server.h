#pragma once

#include <istream>
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include <future>

#include "synchronized.h"


using namespace std;

class InvertedIndex {
public:
    InvertedIndex() = default;
    InvertedIndex(istream &document_input);

    vector<size_t> Lookup(const string &word) const;

    const string &GetDocument(size_t id) const {
        return docs[id];
    }

    const vector<string> &GetDocuments() const {
        return docs;
    }

private:
    map<string, vector<size_t>> index;
    vector<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;

    explicit SearchServer(istream &document_input) : index(InvertedIndex(document_input)) {
    }

    void UpdateDocumentBase(istream &document_input);

    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    Synchronized<InvertedIndex> index;
    vector<future<void>> async_tasks;
};

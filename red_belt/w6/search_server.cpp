#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

vector<string> SplitIntoWords(const string &line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(move(current_document));
    }

    index = move(new_index);
}

void SearchServer::AddQueriesStream(
        istream &query_input, ostream &search_results_output
) {
    auto docs_size = index.GetDocuments().size();
    vector<std::size_t> docid_count(docs_size);
    // compare   -l > -r
    vector<int64_t> docids(docs_size);

    for (string current_query; getline(query_input, current_query);) {
        vector<string> words;

        words = SplitIntoWords(current_query);

        docid_count.assign(docid_count.size(), 0);
        for (const auto &word : words) {
            for (const size_t docid : index.Lookup(word)) {
                docid_count[docid]++;
            }
        }

        std::iota(docids.begin(), docids.end(), 0);
        // TODO partial_sort
        sort(
                begin(docids),
                end(docids),
                [&docid_count](int64_t lhs, int64_t rhs) {
                    return make_pair(docid_count[lhs], -lhs) > make_pair(docid_count[rhs], -rhs);
                }
        );

        search_results_output << current_query << ':';
        for (const auto &docid : Head(docids, 5)) {
            const auto &hitcount = docid_count[docid];
            if (!hitcount) continue; // break; ?
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }
}

void InvertedIndex::Add(const string &document) {
    docs.push_back(document);

    const size_t docid = docs.size() - 1;
    for (const auto &word : SplitIntoWords(document)) {
        index[word].push_back(docid);
    }
}

vector<size_t> InvertedIndex::Lookup(const string &word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}

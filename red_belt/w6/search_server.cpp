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

void update_doc_base(istream &document_input, Synchronized<InvertedIndex> &index_handle) {
    InvertedIndex new_index(document_input);

    swap(index_handle.GetAccess().ref_to_value, new_index);
}

void process_searches(istream &query_input, ostream &search_results_output,
                      Synchronized<InvertedIndex>& index_handle)
{
    vector<std::size_t> docid_count;
    vector<int64_t> docids;

    for (string current_query; getline(query_input, current_query);) {
        vector<string> words;

        words = SplitIntoWords(current_query);
        {
            auto access = index_handle.GetAccess();
            auto docs_size = access.ref_to_value.GetDocuments().size();
            docid_count.resize(docs_size);
            docids.resize(docs_size);
            auto& index = access.ref_to_value;

            docid_count.assign(docid_count.size(), 0);
            for (const auto &word : words) {
                for (const size_t docid : index.Lookup(word)) {
                    docid_count[docid]++;
                }
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


void SearchServer::UpdateDocumentBase(istream &document_input) {
    async_tasks.push_back(async(update_doc_base, ref(document_input), ref(index)));
}

void SearchServer::AddQueriesStream(
        istream &query_input, ostream &search_results_output
)
{
    async_tasks.push_back(async(process_searches, ref(query_input), ref(search_results_output), ref(index)));
}



InvertedIndex::InvertedIndex(istream &document_input) {
    for (string document; getline(document_input, document);) {
        docs.push_back(document);

        const size_t docid = docs.size() - 1;
        for (const auto &word : SplitIntoWords(document)) {
            index[word].push_back(docid);
        }
    }
}

vector<size_t> InvertedIndex::Lookup(const string &word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}

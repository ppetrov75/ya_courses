#include "../test_runner.h"

#include <vector>
#include <algorithm>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template<typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template<typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    // Напишите реализацию функции, не копируя объекты типа Token
    vector<Sentence<Token>> ret;

    while (!tokens.empty()) {
        auto it = std::find_if(tokens.begin(), tokens.end(), [](Token t) { return t.IsEndSentencePunctuation(); });
        if (it != tokens.end())
            do {
                it = std::next(it);
            } while (it != tokens.end() && it->IsEndSentencePunctuation());

        Sentence<Token> snt;
        std::move(tokens.begin(), it, std::back_inserter(snt));
        ret.push_back(std::move(snt));

        tokens.erase(tokens.begin(), it);
    }

    return ret;
}

struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }

    bool operator==(const TestToken &other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }

    TestToken(const TestToken& other) = default;
    TestToken(TestToken&&) = default;
    TestToken& operator=(TestToken &&) = default;

    TestToken& operator=(const TestToken &other) = delete;
};

ostream &operator<<(ostream &stream, const TestToken &token) {
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"},
                                                  {"into"},
                                                  {"sentences"},
                                                  {"!"}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                        })
    );

    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"},
                                                  {"into"},
                                                  {"sentences"},
                                                  {"!", true}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                        })
    );

    ASSERT_EQUAL(
            SplitIntoSentences(vector<TestToken>({{"Split"},
                                                  {"into"},
                                                  {"sentences"},
                                                  {"!", true},
                                                  {"!", true},
                                                  {"Without"},
                                                  {"copies"},
                                                  {".", true}})),
            vector<Sentence<TestToken>>({
                                                {{"Split"},   {"into"},   {"sentences"}, {"!", true}, {"!", true}},
                                                {{"Without"}, {"copies"}, {".", true}},
                                        })
    );
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}

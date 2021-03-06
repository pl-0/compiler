#pragma once
#include <istream>

#include "Lexicon.h"

using std::istream;

class Scanner {
public:
    constexpr static auto Eof = std::char_traits<char>::eof();

    Scanner(istream& stream, ScannerInfo&& scannerInfo);

    void addSkipToken(CodeTokenType tokenType)
    {
        skipTokens.insert(tokenType);
    }

    // The behaviour when eof
    // please see the comment in definition
    CodeToken read();

    bool isFinish()
    {
        return finish;
    }
private:
    istream& inputStream;

    int currentRow = 1;

    bool finish = false;

    unique_ptr<DFAModel::TransformTable> transformTable;
    unique_ptr<DFAModel::AcceptTable> acceptTable;
    unique_ptr<unordered_map<int, CodeTokenType>> acceptStateToTokenMap;

    unordered_set<CodeTokenType> skipTokens;
};
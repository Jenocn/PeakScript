// #pragma once

// #include "Sentence.h"

// namespace peak::interpreter {
// class SentenceExpression;
// class SentenceFor : public Sentence {
// public:
// 	SentenceFor(std::shared_ptr<Sentence> sentence, std::shared_ptr<SentenceExpression> condition);
// 	virtual ExecuteResult Execute(std::shared_ptr<Space> space);

// private:
// 	std::shared_ptr<SentenceExpression> _condition{nullptr};
// 	std::shared_ptr<Sentence> _sentence{nullptr};
// 	std::string _indexParam;
// };
// } // namespace peak::interpreter
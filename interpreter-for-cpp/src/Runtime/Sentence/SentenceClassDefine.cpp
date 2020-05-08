#include "SentenceClassDefine.h"
#include "../ClassTemplate.h"

using namespace peak::interpreter;

SentenceClassDefine::SentenceClassDefine(const std::string& className, const std::string& parentName, const std::list<std::shared_ptr<Sentence>>& sentenceOfPrivate, const std::list<std::shared_ptr<Sentence>>& sentenceOfPublic)
	: _className(className), _parentName(parentName), _sentenceOfPrivate(sentenceOfPrivate), _sentenceOfPublic(sentenceOfPublic) {
}
ExecuteResult SentenceClassDefine::Execute(std::shared_ptr<Space> space) {
	if (_className.empty()) {
		return ExecuteResult::Failed;
	}

	std::shared_ptr<ClassTemplate> parentClassTemplate{nullptr};
	if (!_parentName.empty()) {
		parentClassTemplate = space->FindClassTemplate(_parentName);
		if (!parentClassTemplate) {
			return ExecuteResult::Failed;
		}
	}

	auto spaceOfPrivate = std::shared_ptr<Space>(new Space(SpaceType::None));
	auto spaceOfPublic = std::shared_ptr<Space>(new Space(SpaceType::None));

	for (auto sentence : _sentenceOfPrivate) {
		if (!IsSuccess(sentence->Execute(spaceOfPrivate))) {
			return ExecuteResult::Failed;
		}
	}
	for (auto sentence : _sentenceOfPublic) {
		if (!IsSuccess(sentence->Execute(spaceOfPublic))) {
			return ExecuteResult::Failed;
		}
	}

	auto classTemplate = std::shared_ptr<ClassTemplate>(new ClassTemplate(_className, parentClassTemplate, spaceOfPrivate, spaceOfPublic));

	if (!space->AddClassTemplate(classTemplate)) {
		return ExecuteResult::Failed;
	}
	
	return ExecuteResult::Successed;
}
/*
	PeakScript: https://github.com/Jenocn/PeakScript
	By Jenocn: https://jenocn.github.io
*/

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace peak::interpreter {
class Sentence;
class Value;
class Space;
class SentenceExpression;
class Method {
public:
	Method(const std::string& name);
	const std::string& GetName() const;

	void SetSentenceBody(std::shared_ptr<Sentence> sentence);
	void SetParameters(const std::vector<std::string>& args);
	template <typename TV, typename... TArgs>
	void SetParameters(const TV& arg, TArgs... args) {
		_PushParameter(arg);
		SetParameters(args...);
	}

	std::shared_ptr<Value> Execute(std::shared_ptr<Space> space);
	std::shared_ptr<Value> Execute(std::shared_ptr<Space> space, const std::vector<std::shared_ptr<Value>>& args);

	template <typename TV, typename... TArgs>
	std::shared_ptr<Value> Execute(std::shared_ptr<Space> space, TV arg0, TArgs... args) {
		_PushArg(arg0);
		Execute(space, args...);
	}

private:
	void _PushParameter(const std::string& arg);
	void _PushArg(std::shared_ptr<Value> arg);

private:
	std::string _name;
	std::vector<std::string> _parameters;
	std::shared_ptr<Sentence> _sentence;
	std::vector<std::shared_ptr<Value>> _args;
};
} // namespace peak::interpreter
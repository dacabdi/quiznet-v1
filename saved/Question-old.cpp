#include "Question.h"

Question::Question(const std::string& str)
{
    init(str);
}

Question::Question(std::stringstream& ss)
{
    init(ss);
}

Question::Question(std::vector<std::string> tags,
                   std::string question,
                   std::map<const char, Choice> choices)
{
    init(tags, question, choices);
}

void Question::init(const std::string& str)
{
    std::stringstream ss(str);
    init(ss);
}

void Question::init(std::stringstream& ss)
{
    // temp fields
    std::vector<std::string> tags = deserializeTag(ss);
    std::string question = deserializeQuestion(ss);
    std::map<const char, Choice> choices = deserializeChoices(ss);

    init(tags, question, choices);
}

void Question::init(std::vector<std::string> tags,
                    std::string question,
                    std::map<const char, Choice> choices)
{
    
    validate(choices);

    // if it validated, it is safe to set
    _tags = tags;
    _question = question;
    _choices = choices;
}

void Question::validate(std::map<const char,Choice> choices)
{
    if (choices.size() < 2)
        throw std::invalid_argument(
            "Cannot create question with less than 2 choices.");
    
    char choiceId = 'a';
    for(std::map<const char, Choice>::const_iterator it = choices.begin();
        it != choices.end(); ++it)
        if((*it).first != choiceId)
            throw std::invalid_argument(
                "Choices are non consecutive or do not start wit 'a'");
        else
            choiceId++;
}

std::vector<std::string> Question::deserializeTag(std::stringstream& ss) const
{
    std::string buffer;
    std::getline(ss, buffer);
    return deserializeTag(buffer);   
}

std::vector<std::string> Question::deserializeTag(
    const std::string& s) const
{
    return utils::split(s);   
}

std::string Question::deserializeQuestion(std::stringstream& ss) const
{
    std::string buffer;
    std::string line;
    std::stringstream ssbuff();

    // if the first line is '.', no question, malformed message? TODO ASK!
    std::getline(ss, line);
    if(line == ".")
        throw std::invalid_argument("Empty question."); 
    
    buffer.append(line);
    std::getline(ss, line);
    
    while(line != ".")
    {
        buffer.append("\n");
        buffer.append(line);
        std::getline(ss, line);
    }
    
    return deserializeQuestion(buffer);
}

std::string Question::deserializeQuestion(
    const std::string& question) const
{
    // allows for more complex formatting if needed
    return question;
}

std::map<const char, Choice> Question::deserializeChoices(
    std::stringstream& ss) const
{
    std::map<const char, Choice> _choices;
    std::string buffer;
    bool firstPeriod = false, secondPeriod = false;
    
    while(!secondPeriod)
    {
        std::getline(ss, buffer);
        
        if (buffer == "." && !firstPeriod)
            firstPeriod = true;
        else if (buffer == "." && firstPeriod)
            secondPeriod = true;
        else
        {
            firstPeriod = false;
            
            Choice _choice(buffer);
            char _id = _choice.getId();
            _choices.emplace(_id, _choice);
        }
    }

    return _choices;
}

std::map<const char, Choice> Question::deserializeChoices(
    const std::string& s) const
{
    std::stringstream ss(s);
    return deserializeChoices(ss);
}

std::vector<std::string> Question::getTags(void) const
{
    return _tags;
}

std::string Question::getQuestion(void) const
{
    return _question;
}

std::map<const char, Choice> Question::getAllChoices(void) const
{
    return _choices;
}

Choice Question::getChoiceById(char id) const
{
    return _choices.at(id);
}

std::string Question::serializeTags(const std::vector<std::string>& tags) const
{
    std::stringstream ss;
    std::vector<std::string>::const_iterator it = tags.begin();
    
    // consider no tags
    if (it != tags.end())
    {
        // take in the first one without preceding comma
        ss << *it;
        ++it;
        
        // do the remaining with preceding commas
        for(; it != tags.end(); ++it)
        {
            // TODO should strip spaces? and then fix this
            ss << "," << *it;
        }
    }
    
    return ss.str();
}

std::string Question::serializeQuestion(const std::string& question) const
{
    return question;
}

std::string Question::serializeChoices(const std::map<const char, Choice>& choices) const
{
    std::stringstream ss;
    ss << "." << std::endl;

    for (const std::pair<const char, Choice>& kv : choices) 
    {
        const Choice& _choice = kv.second;
        ss << _choice.serialize()
           << std::endl << "." << std::endl;
    }

    ss << ".";

    return ss.str();        
}

std::string Question::serialize(void) const
{
    std::stringstream ss;

    ss << serializeTags(_tags) << std::endl;
    ss << serializeQuestion(_question) << std::endl;
    ss << serializeChoices(_choices) << std::endl;
    
    return ss.str();
}

std::ostream& operator<<(std::ostream &os, const Question& question)
{
    os << question.serialize();
    return os;
}
/*
bool Question::operator==(const Question& ref) const
{
    return (
           this->tags == tags; 
        && this->text == ref.text
        && this->
    )
}

bool Question::operator!=(const Question& ref) const
{
    return !operator==(ref);
}
*/